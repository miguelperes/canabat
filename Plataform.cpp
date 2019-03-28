#include "Plataform.h"
#include "Globais.h"
#include "Game.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


#include <cstdio>



Plataform::Plataform()
{
    srand(time(NULL));
}

void Plataform::init(float _x, int _boundX, int _boundY)
{
    GameObject::init(_x, HEIGHT - _boundY, Game::GAME_SPEED, 0, _boundX, _boundY, true);

    srand(time(NULL));
    image = al_load_bitmap("images/building.png");
}


void Plataform::destroy()
{
    al_destroy_bitmap(image);
}

void Plataform::update()
{
    GameObject::update();
    velX = Game::GAME_SPEED;
}

void Plataform::draw()
{
    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, boundX, boundY, 0 );
}

void Plataform::respawn(Plataform other)
{
    int multiplier;
    int random = rand()%2;

    if (random == 0)
        multiplier = 1;
    else
        multiplier = -1;



    if(x + boundX <= 0)
    {
        x = other.getX() + other.getBoundX() + (rand()%150)+75;
        boundX = (rand()%400) + 200;

        if(other.getBoundY() < 200)
        {
            boundY = (rand()%20)+200;
        }

        else if(other.getBoundY() > 515)
        {
            boundY = 480;
        }

        else
        {
            boundY = other.getBoundY() + ((rand()%40)+40) * multiplier;
        }

        y = HEIGHT - boundY;
    }

    //printf("altura: %d\n", boundY);
    //printf("largura: %d\n\n", boundX);

}







