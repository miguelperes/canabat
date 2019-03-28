#ifndef INTROSCREEN_H
#define INTROSCREEN_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Game.h"


class IntroScreen
{
public:

    IntroScreen();

    void reset();
    void destroy();

    void processEvent(ALLEGRO_EVENT& event);
    void update(void);
    void draw(void);
    void loop(void);

    int getState() {return state;}
    void setState(int _state) {state = _state;}

    bool checkClose() {return close;}
    void setQuit(bool _quit) {quit = _quit;}

private:
    int state;
    int screen;
    bool quit;
    bool close;

    ALLEGRO_BITMAP* title;
    ALLEGRO_BITMAP* info;
    ALLEGRO_SAMPLE* song;
    ALLEGRO_SAMPLE_INSTANCE* songInstance;
    Game game;


};

#endif // INTROSCREEN_H
