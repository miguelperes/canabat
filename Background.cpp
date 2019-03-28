#include "Background.h"
#include "Globais.h"

Background::Background()
{
}

void Background::init(ALLEGRO_BITMAP* backgroundImage, float _x, float _y, float _velX)
{
    GameObject::init(_x, _y, _velX, 0, 0, 0, false);
    image = backgroundImage;
    frameWidth = al_get_bitmap_width(image);
}

void Background::update()
{
    GameObject::update();

    if(x + frameWidth <=0)
        x = 0;
}

void Background::draw()
{
    al_draw_bitmap(image, x, y, 0);

    if(x + frameWidth < WIDTH)
        al_draw_bitmap(image, x + frameWidth, y, 0);
}

