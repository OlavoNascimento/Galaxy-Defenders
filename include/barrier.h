#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

#include "enemies.h"
#include "player_ship.h"

//definindo valores de constantes das barreiras
#define NUM_BARRIERS 4          //Numero de barreiras do jogo
#define HEIGHT_BARRIER 580      //Altura padrão da barreira na tela
#define HALF_LIFE_BARRIERS 5    //Meia vida das barreiras (quando elas mudam de forma) 
#define TOTAL_LIFE_BARRIERS 10  //Total de vida das barreiras

//struct com as informações das barreiras e explosão:

//Struct contendo informacoes da explosao da barreira
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

//Struct contendo informacoes da barreira
typedef struct
{
    int life_up;
    int life_down;
    bool live;
    int framewidth;
    int frameheight;
    float x;
    float y;
    explosion_bar exp_bar;
}barrier;

//Struct contendo informacoes das outras structs e algumas informacoes a mais
typedef struct
{
    ALLEGRO_BITMAP *img_bar[4];
    ALLEGRO_BITMAP *img_exp_bar;
    barrier main_bar[NUM_BARRIERS];
}main_barrier;


//Inicializando dados da barreira
void InitBarrier(main_barrier *Pbarr);

//Vida da barreira
void lifeBarrier(main_barrier *Pbarr);

//Desenhando a barreira na tela
void drawBarrier(main_barrier *Pbarr);

//Deteccao de colisao entre o tiro do alien e a barrreira
void colision_Alien_shot_barrier(main_barrier *Pbarr, enemies *p_enemies);

//Deteccao de colisao entre o tiro do player e a barreira
void colision_Player_shot_barrier(PlayerShip *player, main_barrier *Pbarr);

//Desenhando animacao da explosao na barreira
void draw_explosion_barrier(main_barrier *Pbarr);

//Alteracao de sprite da barreira
void update_explosion_barrier(main_barrier *Pbarr);

//Liberando recursos usados no programa
void free_barrier_resources(main_barrier *Pbarr);

//Inicia as imagens que vao ser usadas na barreira
bool init_barrier_resources(main_barrier *Pbarr);

#endif // BARRIER_H_INCLUDED
