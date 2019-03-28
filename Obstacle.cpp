#include "Obstacle.h"
#include "Game.h"
#include "Globais.h"

#include <cstdio>


Obstacle::Obstacle()
{

}

void Obstacle::init(float _x, float _y)
{
    srand(time(NULL));
    image = al_load_bitmap("images/obstacle.png");
    al_convert_mask_to_alpha(image, al_map_rgb(0,0,0));
    GameObject::init(_x, _y, Game::GAME_SPEED, 0, al_get_bitmap_width(image)/*20*/, al_get_bitmap_height(image)/*45*/, true);

    alive = true;
}

void Obstacle::destroy()
{
    al_destroy_bitmap(image);
}

void Obstacle::update()
{

    if(alive == true)
    {
        GameObject::update();
        velX = Game::GAME_SPEED;
    }

    else
    {
        GameObject::update();
        velX = Game::GAME_SPEED;
        setVelY(getVelY() + GRAVITY);
    }
}

void Obstacle::draw()
{
    al_draw_bitmap(image, x, (y - boundY), 0);
}

void Obstacle::respawn(Plataform plat)
{
        alive = true;
        int random = (rand()%50)+150;
        int chance = rand()%3;
        //printf("chance: %d\n", chance);

        if(chance == 0)
        {
            x = (plat.getX() + plat.getBoundX()) - random;
            y = plat.getY();
            setVelY(0);
        }
}
