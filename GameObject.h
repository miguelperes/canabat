#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <allegro5/allegro.h>
#include <cstdio>

class GameObject
{
public:
    GameObject();
    void init(float x, float y, float velX, float velY, int boundX, int boundY, bool collidable);

    void virtual update();
    void virtual draw();


    // === Getters e setters - ir criando conforme necessário ===
    float getX() {return x;}
    float getY() {return y;}
    void setX(float x) {GameObject::x = x;}
    void setY(float y) {GameObject::y = y;}

    float getVelX() {return velX;}
    float getVelY() {return velY;}
    void setVelX(const float velX) {GameObject::velX = velX;}
    void setVelY(float velY) {GameObject::velY = velY;}

    int getBoundX() {return boundX;}
    int getBoundY() {return boundY;}
    void setBoundX(int bx) {GameObject::boundX = bx;}
    void setBoundY(int by) {GameObject::boundY = by;}

    bool getCollidable() {return collidable;}
    void setCollidable(bool _collidable) {collidable = _collidable;}

protected:
    float x;
    float y;

    float velX;
    float velY;

    int boundX;
    int boundY;

    int maxFrame;
    int currentFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;

    bool collidable;
    ALLEGRO_BITMAP* image;


private:
};

#endif // GAMEOBJECT_H
