#include "Master.h"
#include "Allegro.h"

#include "Globais.h"

Master::Master()
{
    state = MENU;
}

void Master::init()
{

}

void Master::processEvent(ALLEGRO_EVENT& event)
{
    //GET USER INPUT
}


void Master::update(void)
{
    //UPDATE GAME LOGIC

    if(state == MENU)
    {
        gameMenu.reset();
        gameMenu.loop();
        state = gameMenu.getState();
    }


    if(state == PLAY)
    {
        gamePlay.init();
        gamePlay.loop();
        state = gamePlay.getState();
        gamePlay.setState(PLAY);
        gamePlay.setQuit(false);
    }


    if(state == LOST)
    {
        gameOver.reset(gamePlay.getScore());
        gameOver.loop();
        state = gameOver.getState();
        gameOver.setState(LOST);
        gameOver.setQuit(false);
    }


    if(gameMenu.checkClose() == true || gamePlay.checkClose() == true || gameOver.checkClose() == true)
    {
        quit = true;
    }

}

void Master::draw(void)
{

}

void Master::loop(void)
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
    gamePlay.destroy();
    gameMenu.destroy();
    gameOver.destroy();

    return;
}
