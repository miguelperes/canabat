#ifndef ALLEGRO_H
#define ALLEGRO_H


#include <allegro5/allegro.h>

class Allegro
{
public:
    static void initialize(const int width, const int height);
    static void shutdown(void);

    static const float FPS;

    static ALLEGRO_DISPLAY* display;
    static ALLEGRO_TIMER* timer;
    static ALLEGRO_EVENT_QUEUE* event_queue;

private:
    static void construct(const int width, const int height);
    static void destruct(void);
};

#endif // ALLEGRO_H
