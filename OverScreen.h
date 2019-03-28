#ifndef OVERSCREEN_H
#define OVERSCREEN_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>

class OverScreen
{
public:

    OverScreen();

    void reset(int score);
    void destroy();

    void processEvent(ALLEGRO_EVENT& event);
    void update(void);
    void draw(void);
    void loop(void);

    void highScoreCalc();

    int getState() {return state;}
    void setState(int _state) {state = _state;}
    bool checkClose() {return close;}
    void setQuit(bool _quit) {quit = _quit;}


private:
    ALLEGRO_BITMAP* endTitle;
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* fontSmall;
    ALLEGRO_SAMPLE* song;
    ALLEGRO_SAMPLE_INSTANCE* songInstance;

    int newScore;
    std::list<int> scores;
    std::list<int>::iterator iter;

    bool quit;
    bool close;
    int state;
    int distance;
};

#endif // OVERSCREEN_H
