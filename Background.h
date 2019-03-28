#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"

class Background : public GameObject
{
public:
    Background();

    void init(ALLEGRO_BITMAP* backgroundImage, float x, float y, float velX);
    void update();
    void draw();

protected:
private:
};

#endif // BACKGROUND_H
