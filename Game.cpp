#include "Game.h"
#include "Allegro.h"
#include "Globais.h"

#include <cstdio>
#include <stdlib.h>

#include <allegro5/allegro_primitives.h>


float Game::GAME_SPEED(-3);

int scoreCounter = 0;
int speedCounter = 0;
int scoreMultiplier = 1;

Game::Game()
{
    imagemFundo1 = al_load_bitmap("images/background.png");
    imagemFundo2 = al_load_bitmap("images/background2.png");
    batSinal = al_load_bitmap("images/batsignal.png");

    al_reserve_samples(1);
    song = al_load_sample("sounds/playingTheme.ogg");

    state = PLAY;
    quit = false;
    close = false;
}

void Game::init()
{
    srand(time(NULL));

    fonte = al_load_font("batfonte.ttf", 20, 0);

    al_play_sample(song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    Game::GAME_SPEED = VEL_INICIAL;
    speedCounter = 0;
    score = 0;
    scoreMultiplier = 1;
    scoreCounter = 0;

    fundo.init(imagemFundo1, 0, 0, -0.5);
    fundo2.init(imagemFundo2, 0, 240, -2);

   player.init();

    plat1.init(0, 650, 250);
    plat2.init(plat1.getX() + plat1.getBoundX() + (rand()%150)+30, 350, plat1.getBoundY() + ((rand()%40)+40));
    plat3.init(plat2.getX() + plat2.getBoundX() + ((rand()%150)+30)+10, 450, plat2.getBoundY() - ((rand()%40)+40));
    plat4.init(plat3.getX() + plat3.getBoundX() + ((rand()%150)+30)-15, 230, plat3.getBoundY() + ((rand()%40)+40));

    plataformas[0] = plat1;
    plataformas[1] = plat2;
    plataformas[2] = plat3;
    plataformas[3] = plat4;

    block.init(0,0);   /*(plat3.getX() + 30, HEIGHT - plat3.getBoundY());*/

}

void Game::destroy()
{
    al_destroy_bitmap(imagemFundo1);
    al_destroy_bitmap(imagemFundo2);
    al_destroy_bitmap(batSinal);

    player.destroy();
    block.destroy();

     for(int i = 0; i < 4; i++)
    {
        plataformas[i].destroy();
    }
}


void Game::processEvent(ALLEGRO_EVENT& event)
{
    //GET USER INPUT
    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            if(player.getVelY() == 0)
              {
                //al_play_sample_instance(jumpInstance);
                player.setJumping(true);
                player.setJumpHold(true);
                player.setJumpTime(al_get_time()); //=== CAPTURA QUANDO O PULO FOI DADO
                player.jump();
              }
        }
    }

    if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            player.setJumpHold(false);
        }
    }
}

void Game::update(void)
{
    //UPDATE GAME LOGIC

    fundo.update();
    fundo2.update();

    player.update();
    block.update();

    //player.checkFall();

    for(int i = 0; i < 4; i++)
    {
        plataformas[i].update();
        player.checkCollision(plataformas[i]);

        if(plataformas[i].getX() + plataformas[i].getBoundX() <= 0)  //Checa se precisa dar respawn em alguma plataforma
        {
            if(i == 0)
                plataformas[i].respawn(plataformas[3]);
            else
            {
                plataformas[i].respawn(plataformas[i-1]);
                if(i == 2)
                {
                    block.respawn(plataformas[2]);
                }
            }
        }
    }


    if( player.checkCollision(block) )
    {
        block.setAlive(false);

        if(Game::GAME_SPEED <= -3 && Game::GAME_SPEED >= -6)
            player.setScore(player.getScore() - 5);

        if(Game::GAME_SPEED <= -6 && Game::GAME_SPEED >= -10)
            player.setScore(player.getScore() - 15);

        if(Game::GAME_SPEED <= -10 && Game::GAME_SPEED >= -15)
            player.setScore(player.getScore() - 25);

        if(Game::GAME_SPEED < -15)
            player.setScore(player.getScore() - 30);


        if(Game::GAME_SPEED + 0.5 > VEL_INICIAL)
            Game::GAME_SPEED = VEL_INICIAL;
        else
            Game::GAME_SPEED += 0.25;
    }

    if(player.getJumpHold())
    {
        if(al_get_time() - player.getJumpTime() <= 1) //=== LIMITE DE TEMPO PARA EXTRA
        {
            player.longJump();
        }
    }

    if(++scoreCounter == 50)
    {
        player.setScore(player.getScore()+ 1*scoreMultiplier);
        scoreCounter = 0;
        score = player.getScore();
    }

    if(++speedCounter == 200)
    {
        Game::GAME_SPEED -= 0.5;
        speedCounter = 0;
    }

    if(Game::GAME_SPEED <= -3 && Game::GAME_SPEED >= -6)
    {
        player.setFrameDelay(4);
        scoreMultiplier = 2;
    }

    if(Game::GAME_SPEED <= -6 && Game::GAME_SPEED >= -10)
    {
        player.setFrameDelay(3);
        scoreMultiplier = 3;
    }
    if(Game::GAME_SPEED <= -10 && Game::GAME_SPEED >= -15)
    {
        player.setFrameDelay(2);
        scoreMultiplier = 4;
    }

    if(Game::GAME_SPEED < -15)
        scoreMultiplier = 5;

    if( player.getY() + player.getBoundY() > HEIGHT || player.getX() + player.getBoundX() < 0)
    {
        state = LOST;
        quit = true;
    }
}

void Game::draw(void)
{
    //DRAW GAME STATE
    fundo.draw();
    fundo2.draw();
    al_draw_scaled_bitmap(batSinal, 0, 0, al_get_bitmap_width(batSinal), al_get_bitmap_height(batSinal), WIDTH - 150, 0 + 50, 100, 50, 0);
    block.draw();

    for(int i = 0; i < 4; i++)
    {
        plataformas[i].draw();
    }


    player.draw();

    al_draw_textf(fonte, al_map_rgb(255,255,255), 0, 0, 0, "Score: %d", player.getScore());

}

void Game::loop(void)
 {
    bool refresh = true;
    //bool quit = false;
    ALLEGRO_EVENT event;


    while(!quit)
    {
        al_wait_for_event(Allegro::event_queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            refresh = true;
            update(); // Update game logic
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            close = true;
            quit = true;
            break;
        default:
            processEvent(event); // Get user input
            break;
        }

        if(refresh && al_is_event_queue_empty(Allegro::event_queue))
        {
            refresh = false;
            draw(); // Draw game state

            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }
    al_stop_samples();
    al_destroy_font(fonte);

}
