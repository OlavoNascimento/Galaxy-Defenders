#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

#include "main.h"

//definindo o numero de barreiras
#define NUM_BARRIERS 4

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

}explosion_bar;


typedef struct
{
    //BARREIRA 01
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

}barrier;


//INICIALIZANDO BARREIRA
void InitBarrier();

//SAUDE DA BARRERIA
void lifeBarrier();

//DESENHANDO A BARREIRA
void drawBarrier();

//COLISAO COM O TIRO DO ALIEN
void colisionAlien();

//COLISAO COM O TIRO DO PLAYER
void colisionPlayer();

//DESENHANDO SPRITE DA EXPLOSAO
void draw_explosion_barrier();

//ALTERANDO ANIMACOES DO SPRITE
void update_explosion_barrier();


#endif // BARRIER_H_INCLUDED
