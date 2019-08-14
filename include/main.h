#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <allegro5/allegro.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "barrier.h"
#include "events.h"
#include "player_ship.h"
#include "enemies.h"
#include "alien_explosion.h"

//variaveis basicas do programa:
// ALLEGRO_BITMAP *ship;
// ALLEGRO_BITMAP *bimg;

ALLEGRO_BITMAP *alien1img;
ALLEGRO_BITMAP *alien2img;
ALLEGRO_BITMAP *alien3img;
ALLEGRO_BITMAP *exp_img;
ALLEGRO_BITMAP *alien_bullet_img;

ALLEGRO_BITMAP *img_bar[4];
ALLEGRO_BITMAP *img_exp_bar;


//objetos do programa:
// spaceship Pship;
// bullet bullets[5];

enemy alien1[NUM_ALIEN];
enemy alien2[2][NUM_ALIEN];
enemy alien3[2][NUM_ALIEN];

barrier bar[NUM_BARRIERS];

void free_basic_resources();

#endif // MAIN_H_INCLUDED
