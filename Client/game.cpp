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
    al_init_primitives_addon();
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	// Initialize client stuff
    unsigned short listen_port = 50000;
	this->client = new Client(Address(127, 0, 0, 1, 50000));
	////this->client = new Client(Address(104,255,231,252, 50000));

	while (!this->client->Init(listen_port)) { ++listen_port; }
	std::cout << "Started listening on port: " << listen_port << std::endl;


	// Initialize game state stuff
    this->state = new GameStateInit(this);
    this->state->Enter();
}

void Game::Run()
{
    this->is_running = true;
    bool needs_render = false;

    al_start_timer(this->timer);
    while(this->is_running)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            needs_render = true;

            this->client->TickPacketAcks();

            this->state->Tick();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            this->is_running = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {

            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {

        }


        if (needs_render && al_is_event_queue_empty(this->event_queue))
        {
            needs_render = false;

            this->state->Render();

            if (this->display)
            {
                al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));
            }

        }
    }
}
