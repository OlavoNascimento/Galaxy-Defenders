#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

#include "enemies.h"
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


}barrier;

typedef struct
{
    ALLEGRO_BITMAP *img_bar[4];
    ALLEGRO_BITMAP *img_exp_bar;
    barrier main_bar[NUM_BARRIERS];

}main_barrier;

//INICIALIZANDO BARREIRA
void InitBarrier(main_barrier *Pbarr);

//SAUDE DA BARRERIA
void lifeBarrier(main_barrier *Pbarr);

//DESENHANDO A BARREIRA
void drawBarrier(main_barrier *Pbarr);

//COLISAO COM O TIRO DO ALIEN COM A BARREIRA
void colision_Alien_shot_barrier(main_barrier *Pbarr);

//COLISAO COM O TIRO DO PLAYER
void colision_Player_shot_barrier(PlayerShip *player, main_barrier *Pbarr);

//DESENHANDO SPRITE DA EXPLOSAO
void draw_explosion_barrier(main_barrier *Pbarr);

//ALTERANDO ANIMACOES DO SPRITE
void update_explosion_barrier(main_barrier *Pbarr);

//LIBERAR RECURSOS USADOS NO PROGRAMA
void free_barrier_resources(main_barrier *Pbarr);

//INICIAR IMAGENS DAS BARREIRAS E DA EXPLOSAO
bool init_barrier_resources(main_barrier *Pbarr);

#endif // BARRIER_H_INCLUDED
