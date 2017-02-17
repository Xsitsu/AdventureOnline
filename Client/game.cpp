#include "game.hpp"

Game::Game() : display(NULL), event_queue(NULL), timer(NULL), state(NULL), client(NULL)
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


	FontService::Instance()->LoadFonts();

	// Initialize game state stuff
    this->state = new GameStateInit(this);
    this->state->Enter();
}

void Game::Run()
{
    this->is_running = true;
    bool needs_render = false;

    float game_time = 0;
    int frame_counter = 0;
    int game_fps = 0;

    al_start_timer(this->timer);
    while(this->is_running)
    {
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
			}

            this->client->TickPacketAcks();

            this->state->Tick();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            this->is_running = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (!GuiSelectionService::Instance()->TextBoxHasFocus())
            {
                this->state->HandleKeyDown(ev.keyboard);
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
                al_draw_textf(FontService::Instance()->GetFont(), al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", game_fps);

                al_wait_for_vsync();
                al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));
            }

        }
    }
}

void Game::PushScreen(GuiScreen* screen)
{
    this->screen_stack.push_back(screen);
}

void Game::PopScreen()
{
    if (this->screen_stack.empty()) return;

    GuiScreen* screen = this->screen_stack.back();
    this->screen_stack.pop_back();
    delete screen;
}

void Game::DrawScreens()
{
    screen_iter iter = this->screen_stack.begin();
    for (iter; iter != this->screen_stack.end(); ++iter)
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
