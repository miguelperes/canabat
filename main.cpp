#include <iostream>

#include "Allegro.h"
#include "IntroScreen.h"
#include "Game.h"
#include "Master.h"

#include "Globais.h"


int main()
{
    Allegro::initialize(WIDTH, HEIGHT);

    {
    //Game game;
    //game.loop();
    Master master;
    master.loop();
    }


    Allegro::shutdown();

}
