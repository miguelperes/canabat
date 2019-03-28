#ifndef PLATAFORM_H
#define PLATAFORM_H

#include "GameObject.h"


class Plataform : public GameObject
{
public:
    Plataform();

    void destroy();
    void init(float x, int bx, int by);

    void update();
    void draw();

    void respawn(Plataform other);


protected:
private:

    ALLEGRO_BITMAP* image1;
    ALLEGRO_BITMAP* image2;
    ALLEGRO_BITMAP* image3;
    ALLEGRO_BITMAP* image4;
    ALLEGRO_BITMAP* image5;

};

#endif // PLATAFORM_H
