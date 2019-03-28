#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Player.h"
#include "Plataform.h"
#include "Background.h"
#include "OverScreen.h"
#include "Obstacle.h"

class Game
{
public:

    Game();

    void init();
    void destroy();

    void processEvent(ALLEGRO_EVENT& event);
    void update(void);
    void draw(void);
    void loop(void);

    int getScore() {return score;}
    int getState() {return state;}
    void setState(int _state) {state = _state;}
    bool checkClose() {return close;}
    void setQuit(bool _quit) {quit = _quit;}

    static float GAME_SPEED;

private:
    int state;
    bool quit;
    bool close;
    int score;

    ALLEGRO_BITMAP* imagemFundo1;
    ALLEGRO_BITMAP* imagemFundo2;
    ALLEGRO_BITMAP* batSinal;
    ALLEGRO_FONT* fonte;
    ALLEGRO_SAMPLE* song;
    ALLEGRO_SAMPLE* jumpSound;
    ALLEGRO_SAMPLE_INSTANCE* jumpInstance;

    Plataform plataformas[4];
    Player player;

    Plataform plat1;
    Plataform plat2;
    Plataform plat3;
    Plataform plat4;

    Obstacle block;

    Background fundo;
    Background fundo2;

    OverScreen gameOver;
};


#endif // GAME_H
