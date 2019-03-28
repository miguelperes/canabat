#include "JumpAnimation.h"

JumpAnimation::JumpAnimation()
{
    image = al_load_bitmap("images/jumpSheet.png");
    al_convert_mask_to_alpha(image, al_map_rgb(4,85,65));

    maxFrame = 10;
    currentFrame = 0;
    frameCount = 0;
    frameDelay = 4;
    frameWidth = 48;
    frameHeight = 61;
}

void JumpAnimation::update()
{

}

void JumpAnimation::draw()
{
    if(++frameCount >= frameDelay)
    {
        if(++currentFrame >= maxFrame)
            currentFrame = maxFrame;

        frameCount = 0;
    }

    al_draw_bitmap_region(image, currentFrame * frameWidth, 0, frameWidth, frameHeight, x, y, 0);

}

