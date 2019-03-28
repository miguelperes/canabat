#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "GameObject.h"
#include "Plataform.h"
#include "Obstacle.h"

class Player : public GameObject
{
public:
    Player();

    void init();
    void destroy();

    void update();
    void draw();
    void checkCollision(Plataform plat);
    bool checkCollision(Obstacle block);

    void changeAnimation(int newState);
    void checkFall();

    void jump();
    void longJump();

    // === GETTERS E SETTERS

    bool getJumpHold() {return jumpHold;}
    float getJumpTime() {return jumpTime;}
    bool getColliding() {return colliding;}

    void setJumping(bool _jumping) {jumping = _jumping;}
    void setJumpHold(bool _jumpHold) {jumpHold = _jumpHold;}
    void setColliding(bool _colliding) {colliding = _colliding;}
    void setJumpTime(float n) {jumpTime = n;}
    void setFrameDelay(float _frameDelay) {frameDelay = _frameDelay;}

    void setScore(int _score) {score = _score;}
    int getScore() {return score;}

private:

    ALLEGRO_BITMAP* imageFall;
    ALLEGRO_BITMAP* imageJump;
    ALLEGRO_BITMAP* imageRun;

    int score;
    int state;

    bool jumping;
    bool jumpHold;
    float jumpTime;
    bool colliding;
};

#endif // PLAYER_H
