#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"
#include "Plataform.h"


class Obstacle : public GameObject
{
public:
    Obstacle();
    void init(float x, float y);
    void destroy();

    void update();
    void draw();
    void respawn(Plataform plat);

    void jump();

    void setAlive(bool _alive) {alive = _alive;}

    bool alive;

protected:
private:

    //bool alive;
};

#endif // OBSTACLE_H
