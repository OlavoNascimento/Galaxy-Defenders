#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED
/*
#include "main.h"
#include "player_ship.h"

//definindo o numero de barreiras
#define NUM_BARRIERS 4
#define HEIGHT_BARRIER 580

//struct com as informa��es das barreiras e explosão:

typedef struct
{
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
    int framewidth;
    int frameheight;
    int y;
    int x;
    bool start_exp;
    ALLEGRO_BITMAP *img_exp_bar;

}explosion_bar;


typedef struct
{
    int life_up;
    int life_down;
    bool live;
    float position_x;
    float position_y;
    int framewidth;
    int frameheight;
    float x;
    float y;
    explosion_bar exp_bar;
    ALLEGRO_BITMAP *img_bar[4];

}barrier;

//INICIALIZANDO BARREIRA
void InitBarrier(barrier *Pbarr)

//SAUDE DA BARRERIA
void lifeBarrier(barrier *Pbarr);

//DESENHANDO A BARREIRA
void drawBarrier(barrier *Pbarr);

//COLISAO COM O TIRO DO ALIEN
void colisionAlien();

//COLISAO COM O TIRO DO PLAYER
void colisionPlayer(PlayerShip *player);

//DESENHANDO SPRITE DA EXPLOSAO
void draw_explosion_barrier(barrier *Pbar);

//ALTERANDO ANIMACOES DO SPRITE
void update_explosion_barrier(barrier *Pbar);

*/
#endif // BARRIER_H_INCLUDED
