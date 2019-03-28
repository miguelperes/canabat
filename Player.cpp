#include "Player.h"
#include "Globais.h"
#include "Game.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <cstdio>


Player::Player()
{
    imageFall = al_load_bitmap("images/falling.png");
    imageJump = al_load_bitmap("images/jump.png");
    imageRun = al_load_bitmap("images/player.png");
    image = NULL;
}


void Player::init()
{
    GameObject::init(100, 0, 0, 0, 57, 45, true);


    jumping = false;
    jumpHold = false;
    jumpTime = 0;
    colliding = false;

    score = 0;
    changeAnimation(FALL);

    maxFrame = 9;
    currentFrame = 0;
    frameCount = 0;
    frameDelay = 5;
    frameWidth = 57;
    frameHeight = 45;
}

void Player::destroy()
{
    al_destroy_bitmap(image);
    //al_destroy_bitmap(imageFall);
    //al_destroy_bitmap(imageJump);
    //al_destroy_bitmap(imageRun);
}


void Player::update()
{
    GameObject::update();
    setVelY(getVelY() + GRAVITY);
}

void Player::draw()
{
    if(state == JUMP)
    {
        al_draw_bitmap(image, x, y, 0);
        jumping = false;
    }

    if(state == RUN)
    {
        if(++frameCount >= frameDelay)
        {
            if(++currentFrame >= maxFrame)
                currentFrame = 0;

            frameCount = 0;
        }

    al_draw_bitmap_region(image, currentFrame * frameWidth, 0, frameWidth, frameHeight, x, y, 0);
    }

    if(state == FALL)
    {
        al_draw_bitmap(image, x, y, 0);

    }
}

void Player::checkCollision(Plataform plat)
{
    if( (y + boundY >= plat.getY()) && (x + boundX >= plat.getX()) && (x <= plat.getX() + plat.getBoundX()) )
    {
        if( (y + boundY) - plat.getY() < (x + boundX) - plat.getX() )
        {
            if(!jumping)
            {
                changeAnimation(RUN);
                setVelY(0);
                setY(plat.getY() - boundY);
            }
        }
        else
        {
            setVelX(Game::GAME_SPEED * 1);
            changeAnimation(FALL);
        }
    }
}

bool Player::checkCollision(Obstacle block)
{
    if( (y + boundY >= block.getY()) && (x + boundX >= block.getX()) && (x <= block.getX() + block.getBoundX()) )
    {
       /* block.setAlive(false);
        block.setVelY(-5);
        //printf("BLOCK COLL: %d\n", (int)block.getCollidable());
        //printf("HIT\n");*/
        return true;
    }
    else
        return false;
}

void Player::jump()
{
    setVelY(-5);
    changeAnimation(JUMP);
}

void Player::longJump()
{
    setVelY(getVelY() - 0.125);
}

void Player::changeAnimation(int newState)
{
    if(newState == JUMP)
    {
        state = JUMP;
        image = imageJump;
        al_convert_mask_to_alpha(image, al_map_rgb(4,85,65));

        boundX = al_get_bitmap_width(image);
        boundY = al_get_bitmap_height(image);
    }

    if(newState == RUN)
    {
        state = RUN;

        image = imageRun;
        al_convert_mask_to_alpha(image, al_map_rgb(4,85,65));

        boundX = frameWidth;
        boundY = frameHeight;
    }

    if(newState == FALL)
    {
        state = FALL;

        image = imageFall;
        al_convert_mask_to_alpha(image, al_map_rgb(4,85,65));
    }
}

void Player::checkFall()
{
        if(velY != 0 && state != JUMP)
        {
            changeAnimation(FALL);
        }
}
