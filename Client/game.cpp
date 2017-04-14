#include "game.hpp"
#include "gamestateserverconnect.hpp"
#include "gamestatequit.hpp"

#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#include <chrono>
#include <sstream>

#include "bitmapservice.hpp"
#include "GameUtil/resourcefile.hpp"
#include "GameUtil/resource.hpp"

Game* Game::instance = NULL;

Game::Game() : display(NULL), event_queue(NULL), timer(NULL), state(NULL),
client(NULL), current_map(nullptr), current_character(nullptr)
{

}

Game::~Game()
{
    //al_destroy_display(this->display);
	//al_destroy_timer(this->timer);
	//al_destroy_event_queue(this->event_queue);
}

void Game::ChangeState(GameStateBase* state)
{
#ifdef _DEBUG
    std::cout << "Exiting state: " << this->state->GetStateName() << std::endl;
#endif // _DEBUG
    this->state->Exit();
    delete this->state;
    this->state = state;
#ifdef _DEBUG
    std::cout << "Entering state: " << this->state->GetStateName() << std::endl;
#endif // _DEBUG
    this->state->Enter();
}


void Game::Init()
{
    // Initialize Allegro stuff.
    if (!al_init())
    {
        std::cout << "Failed to initialize allegro!" <<  std::endl;
        throw "break";
    }

    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());


	// Initialize client stuff
    unsigned short listen_port = 50000;
	this->client = new Client(Address(127, 0, 0, 1, 50000));
	////this->client = new Client(Address(104,255,231,252, 50000));

	while (!this->client->Init(listen_port)) { ++listen_port; }
	std::cout << "Started listening on port: " << listen_port << std::endl;

	ALLEGRO_FONT* debug_font = al_load_font("C:/Windows/Fonts/arial.ttf", 18, 0);
	FontService::Instance()->RegisterFont("debug", debug_font);

	// Initialize game state stuff
    this->state = new GameStateServerConnect(this);
    this->state->Enter();
}

void Game::Run()
{
    this->is_running = true;
    bool needs_render = false;

    bool show_debug_menu = false;

    float game_time = 0;
    int frame_counter = 0;
    int game_fps = 0;

    std::list<int> ping_calcs;
    double ping = 0;
    uint64_t ping_send_time;

    al_start_timer(this->timer);
    while(this->is_running)
    {
        while (!this->game_event_queue.empty())
        {
            GameEventBase* event = this->game_event_queue.front();
            this->game_event_queue.pop_front();

            event->HandleEvent();
            delete event;
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            needs_render = true;

            frame_counter++;
            if(al_current_time() - game_time >= 1)
			{
				game_time = al_current_time();
				game_fps = frame_counter;
				frame_counter = 0;

                ping = 0;
                std::list<int>::iterator iter;
                for (iter = ping_calcs.begin(); iter != ping_calcs.end(); ++iter)
                {
                    ping += *iter;
                }

                ping /= ping_calcs.size();
                ping_calcs.clear();
			}

			if (this->client->IsConnected())
            {
                bool did_timeout = this->client->CheckForTimeout();
                if (did_timeout)
                {
                    this->client->DoDisconnect();
                    al_show_native_message_box(this->display, "Connection Error",
                                               "Lost Connection To Server",
                                               "The connection to the server was lost. The game will now shut down.",
                                               0, ALLEGRO_MESSAGEBOX_ERROR);

                    this->ChangeState(new GameStateQuit(this));
                }
                else
                {
                    PacketBase* packet = this->client->ReceivePacket();
                    if (packet)
                    {
                        if (packet->GetType() == PacketBase::PACKET_PONG)
                        {
                            uint64_t tick;
                            tick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

                            ping_calcs.push_back(tick - ping_send_time);
                        }
                        else
                        {
                            this->state->HandlePacket(packet);
                        }
                    }
                    delete packet;

                    if (frame_counter % 3 == 0)
                    {
                        PacketPing* packet = new PacketPing();
                        packet->SetNeedsAck(false);
                        this->client->SendPacket(packet);

                        ping_send_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

                    }
                }
            }

            this->client->TickPacketAcks();

            this->state->Tick();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            this->ChangeState(new GameStateQuit(this));
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (!GuiSelectionService::Instance()->TextBoxHasFocus())
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_F5)
                {
                    show_debug_menu = !show_debug_menu;
                }
                else
                {
                    this->state->HandleKeyDown(ev.keyboard);
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (!GuiSelectionService::Instance()->TextBoxHasFocus())
            {
                this->state->HandleKeyUp(ev.keyboard);
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            this->state->HandleMouseMove(ev.mouse);
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            this->state->HandleMouseDown(ev.mouse);
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            this->state->HandleMouseUp(ev.mouse);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            GuiSelectionService::Instance()->HandleKeyboardTyping(ev.keyboard);
        }


        if (needs_render && al_is_event_queue_empty(this->event_queue))
        {
            needs_render = false;

            this->state->Render();

            if (this->display)
            {
                if (show_debug_menu)
                {
                    ALLEGRO_FONT* font = FontService::Instance()->GetFont("debug");
                    ALLEGRO_COLOR color = al_map_rgb(255, 0, 255);
                    al_draw_textf(font, color, 5, 5, 0, "FPS: %i", game_fps);
                    al_draw_textf(font, color, 5, 5 + font->height, 0, "Ping: %i", (int)ping);
                    al_draw_textf(font, color, 5, 5 + font->height * 2, 0, "GameState: %s", this->state->GetStateName().c_str());
                }

                al_wait_for_vsync();
                al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));
            }

        }
    }
}

void Game::Cleanup()
{
    this->client->Cleanup();
}

void Game::PushScreen(GuiScreen* screen)
{
    this->screen_stack.push_back(screen);
    GuiSelectionService::Instance()->HandleScreenPush();
}

void Game::PopScreen()
{
    if (this->screen_stack.empty()) return;

    GuiScreen* screen = this->screen_stack.back();
    this->screen_stack.pop_back();
    delete screen;

    GuiSelectionService::Instance()->HandleScreenPop();
}

void Game::DrawScreens()
{
    screen_iter iter;
    for (iter = this->screen_stack.begin(); iter != this->screen_stack.end(); ++iter)
    {
        GuiScreen* screen = *iter;
        screen->Draw();
    }
}

GuiScreen* Game::GetCurrentScreen()
{
    if (this->screen_stack.empty()) return NULL;
    return this->screen_stack.back();
}

void Game::RegisterEventToQueue(GameEventBase* event)
{
    this->game_event_queue.push_back(event);
}

void Game::LoginAsCharacter(Character* character)
{
    PacketCharacterLogin* packet = new PacketCharacterLogin();
    packet->SetCharacterId(character->GetCharacterId());
    this->SendPacket(packet);

    this->current_character = character;
}

std::vector<Character*> Game::GetCharacterList() const
{
    return this->character_list;
}

void Game::ClearCharacterList()
{
    while (!this->character_list.empty())
    {
        delete this->character_list.back();
        this->character_list.pop_back();
    }
}

void Game::LoadResourceFile(std::string fname, std::string regname, ALLEGRO_COLOR mask_color)
{
    std::list<Resource*> rlist;
    ResourceFile rfile;

    rfile.Open(fname);
    rlist = rfile.Read();
    rfile.Close();

    int c = 0;
    while (!rlist.empty())
    {
        Resource* resource = rlist.front();
        rlist.pop_front();

        uint32_t width = resource->GetWidth();
        uint32_t height = resource->GetHeight();

        ALLEGRO_BITMAP* bitmap = al_create_bitmap(width, height);
        al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

        al_set_target_bitmap(bitmap);

        for (uint32_t w = 0; w < width; w++)
        {
            for (uint32_t h = 0; h < height; h++)
            {
                Pixel pixel = resource->GetPixel(w, h);
                al_put_pixel(w,  h, al_map_rgba(pixel.r, pixel.g, pixel.b, pixel.a));
            }
        }

        al_unlock_bitmap(bitmap);
        delete resource;

        std::stringstream ss;
        ss << regname << c;

        al_convert_mask_to_alpha(bitmap, mask_color);
        BitmapService::Instance()->RegisterBitmap(ss.str(), bitmap);

        c++;
    }
}
