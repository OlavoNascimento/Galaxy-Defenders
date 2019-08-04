#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <allegro5/allegro.h>
#include <stdbool.h>

#include "events.h"
#include "player_ship.h"
#include "enemies.h"
#include "alien_explosion.h"
#include "barrier.h"

//resolu�ao da tela:
#define gDISPLAYw 1280

#define gDISPLAYh 720

//taxa de atualiza�ao da tela(frames per second):
#define FPS 60


//variaveis basicas do programa:
ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *eventQ;
ALLEGRO_BITMAP *ship;
ALLEGRO_BITMAP *bimg;
ALLEGRO_BITMAP *alien1img;
ALLEGRO_BITMAP *alien2img;
ALLEGRO_BITMAP *alien3img;
ALLEGRO_BITMAP *exp_img;
ALLEGRO_BITMAP *img_bar[NUM_BARRIERS];


//objetos do programa:
spaceship Pship;
bullet bullets[5];
enemy alien1[NUM_ALIEN];
enemy alien2[2][NUM_ALIEN];
enemy alien3[2][NUM_ALIEN];
barrier bar[NUM_BARRIERS];


//variavel usada para atualizar a tela(redesenhar objetos):
 bool redraw;

//variavel usada para sair do loop principal do jogo:
 bool exitl;

#endif // MAIN_H_INCLUDED
