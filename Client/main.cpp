#include <iostream>

#include "allegro5/allegro.h"

#include "GameShared/socket.hpp"
#include "GameShared/packet.hpp"

#include "client.hpp"

int main(int argc, char** argv)
{
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;

    if (!al_init())
    {
        std::cout << "Failed to initialize allegro!" <<  std::endl;
        return -1;
    }

    display = al_create_display(640, 480);
    if (!display)
    {
        std::cout << "Failed to create display!" <<  std::endl;
        return -1;
    }

    al_install_keyboard();
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));


    al_set_window_position(display, 100, 100);


	InitializeSockets();

	unsigned short listen_port = 50000;
	Client client(Address(127, 0, 0, 1, 50000));
    //Client client(Address(104,255,231,252, 50000));

	while (!client.Init(listen_port))
    {
        std::cout << "Failed to start on port: " << listen_port++ << ". Trying next..." << std::endl;
    }

    std::cout << "Started on port: " << listen_port  << std::endl;
	client.SendConnectRequest();

	al_start_timer(timer);
	bool running = true;
	bool doRender = false;
	while (running)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                std::cout << "Send ping packet." << std::endl;;
                client.SendPacket(new PacketPing());
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            //std::cout << "\nGame Tick\n" << std::endl;

            doRender = true;

            client.TickPacketAcks();

            if (client.IsConnected())
            {
                PacketBase* packet = client.ReceivePacket();
                if (packet)
                {
                    std::cout << "Got a packet. [" << packet->GetSequence() << "]" << std::endl;
                    if (packet->GetType() == PacketBase::PACKET_PING)
                    {
                        std::cout << "Got Ping. Sending Pong." << std::endl;
                        client.SendPacket(new PacketPong());
                    }
                    else if (packet->GetType() == PacketBase::PACKET_PONG)
                    {
                        std::cout << "Got Pong." << std::endl;
                    }

                    delete packet;
                }
            }
            else
            {
                client.GetConnectResponse();
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }

        if (doRender && al_is_event_queue_empty(event_queue))
        {
            doRender = false;

            //std::cout << "\nDoing Render.\n" << std::endl;

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_flip_display();
        }

    }

    client.Disconnect();

    std::cout << "Getting remaining packets." << std::endl;

    PacketBase* packet = client.ReceivePacket();
    while (packet)
    {
        if (packet->GetType() == PacketBase::PACKET_PING)
        {
            std::cout << "Got Ping." << std::endl;
        }
        else if (packet->GetType() == PacketBase::PACKET_PONG)
        {
            std::cout << "Got Pong." << std::endl;
        }

        delete packet;
        packet = client.ReceivePacket();
    }

	ShutdownSockets();

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}
