#include "IntroScreen.h"
#include "Allegro.h"
#include "Globais.h"

#include <cstdio>

IntroScreen::IntroScreen()
{
    title = al_load_bitmap("images/introScreen.png");
    info = al_load_bitmap("images/infoScreen.png");

    song = al_load_sample("sounds/Theme.ogg");
    songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

    state = MENU;
    screen = MAIN;
    quit = false;
    close = false;
}

void IntroScreen::reset()
{
    al_play_sample_instance(songInstance);
    state = MENU;
    screen = MAIN;
    quit = false;
}

void IntroScreen::destroy()
{
    al_destroy_bitmap(title);
    al_destroy_bitmap(info);
    al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
}

void IntroScreen::processEvent(ALLEGRO_EVENT& event)
{
    //GET USER INPUT

    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            state = PLAY;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_M)
        {
            screen = INFRM;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
        {
            screen = MAIN;
        }
    }
}


void IntroScreen::update(void)
{
    //UPDATE GAME LOGIC

    if(state == PLAY)
    {
        quit = true;
    }

}

void IntroScreen::draw(void)
{
    if(screen == MAIN)
        al_draw_bitmap(title, 0, 0, 0);
    else if (screen == INFRM)
        al_draw_bitmap(info, 0, 0, 0);

}

void IntroScreen::loop(void)
 {
    bool refresh = true;
    ALLEGRO_EVENT event;


    while(!quit)
    {
        al_wait_for_event(Allegro::event_queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            refresh = true;
            update(); // Update game logic
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            close = true;
            quit = true;
            break;
        default:
            processEvent(event); // Get user input
            break;
        }

        if(refresh && al_is_event_queue_empty(Allegro::event_queue))
        {
            refresh = false;
            draw(); // Draw game state

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }

    al_stop_sample_instance(songInstance);


}
