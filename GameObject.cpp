#include "GameObject.h"

//#include <cstdio>

GameObject::GameObject()
{
    x = 0;
    y = 0;

    velX = 0;
    velY = 0;

    boundX = 0;
    boundY = 0;

    maxFrame = 0;
    currentFrame = 0;
    frameCount = 0;
    frameDelay = 0;
    frameWidth = 0;
    frameHeight = 0;

    collidable = false;
    image = NULL;
}

void GameObject::init(float x, float y, float velX, float velY, int boundX, int boundY, bool collidable)
{
    GameObject::x = x;
    GameObject::y = y;

    GameObject::velX = velX;
    GameObject::velY = velY;

    GameObject::boundX = boundX;
    GameObject::boundY = boundY;

    GameObject::collidable = collidable;
}

void GameObject::update()
{
    x += velX;
    y += velY;
}

void GameObject::draw()
{

}
