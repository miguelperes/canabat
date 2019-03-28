#include "allegro.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void Allegro::initialize(const int width, const int height)
{
    al_init();

    al_install_keyboard();
    al_install_mouse();

    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(8);

    construct(width, height);
}

void Allegro::shutdown(void)
{
    destruct();

    if(al_is_audio_installed()) al_uninstall_audio();

    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();

    if(al_is_keyboard_installed()) al_uninstall_keyboard();
    if(al_is_mouse_installed()) al_uninstall_mouse();

    if(al_is_system_installed()) al_uninstall_system();
}

void Allegro::construct(const int width, const int height)
{
    display = al_create_display(width, height);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

void Allegro::destruct(void)
{
    if(display != NULL) al_destroy_display(display);
    if(timer != NULL) al_destroy_timer(timer);
    if(event_queue != NULL) al_destroy_event_queue(event_queue);

    display = NULL;
    timer = NULL;
    event_queue = NULL;
}

const float Allegro::FPS = 60.0;
ALLEGRO_DISPLAY* Allegro::display = NULL;
ALLEGRO_TIMER* Allegro::timer = NULL;
ALLEGRO_EVENT_QUEUE* Allegro::event_queue = NULL;
