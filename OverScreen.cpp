#include "OverScreen.h"
#include "Allegro.h"

#include "Globais.h"
#include <cstdio>

OverScreen::OverScreen()
{
    endTitle = al_load_bitmap("images/gameOver.png");

    song = al_load_sample("sounds/endTheme.ogg");
    songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

    state = LOST;
    quit = false;
    close = false;
}

void OverScreen::reset(int score)
{
    al_play_sample_instance(songInstance);
    font = al_load_font("batfonte.ttf", 60, 0);
    fontSmall = al_load_font("batfonte.ttf", 30, 0);
    newScore = score;
    highScoreCalc();
    distance = 0;
}

void OverScreen::destroy()
{
    al_destroy_bitmap(endTitle);
    al_destroy_sample(song);
    al_destroy_sample_instance(songInstance);
}

void OverScreen::highScoreCalc()
{
    scores.sort();

    if(scores.size() <= 4)
    {
        scores.push_back(newScore);
        scores.sort();
    }

    else
    {
        scores.pop_front();
        scores.push_back(newScore);
        scores.sort();
    }
    scores.reverse();
}

void OverScreen::processEvent(ALLEGRO_EVENT& event)
{
    //GET USER INPUT

    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            state = PLAY;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
        {
            state = MENU;
        }
    }
}


void OverScreen::update(void)
{
    //UPDATE GAME LOGIC

    if(state == PLAY || state == MENU)
    {
        quit = true;
    }
}

void OverScreen::draw(void)
{
    al_draw_bitmap(endTitle, 0, 0, 0);
    al_draw_textf(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Score: %d", newScore);
    al_draw_text(fontSmall, al_map_rgb(255,0,0), 0, HEIGHT/2 - 40, ALLEGRO_ALIGN_LEFT, "top 5");

   for(iter = scores.begin(), distance = 0; iter != scores.end(); ++iter, distance += 30)
   {
       al_draw_textf(fontSmall, al_map_rgb(255,255,255), 0, HEIGHT/2 + distance, ALLEGRO_ALIGN_LEFT, "# %d", (*iter));
   }



}

void OverScreen::loop(void)
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
    al_destroy_font(font);
    al_destroy_font(fontSmall);
    return;
}
