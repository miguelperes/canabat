#ifndef MASTER_H
#define MASTER_H

#include <allegro5/allegro.h>
#include "IntroScreen.h"
#include "Game.h"
#include "OverScreen.h"

class Master
{
public:

    Master();

    void init();

    void processEvent(ALLEGRO_EVENT& event);
    void update(void);
    void draw(void);
    void loop(void);



private:


    int state;
    bool quit;

    IntroScreen gameMenu;
    Game gamePlay;
    OverScreen gameOver;



};


#endif // MASTER_H
