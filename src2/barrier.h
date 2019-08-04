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
    bool start;

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
void InitBarrier(void);

//SAUDE DA BARRERIA
void lifeBarrier(void);

//ALTERANDO SPRITE DA BARREIRA
void update_explosion_barrier(void);

//DESENHANDO A BARREIRA
void drawBarrier(void);

//COLISAO COM O TIRO DO ALIEN
void colisionAlien(void);

//COLISAO COM O TIRO DO PLAYER
void colisionPlayer(void);


#endif // BARRIER_H_INCLUDED
