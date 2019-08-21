#ifndef ALIEN_EXPLOSION_H_INCLUDED
#define ALIEN_EXPLOSION_H_INCLUDED

#include "enemies.h"
/*
typedef struct{
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
    int framewidth;
    bool start;
}explosion;
*/

void update_explosion_alien1 (enemies *p_enemies);

void draw_explosion_alien1(enemies *p_enemies);


void update_explosion_alien2(enemies *p_enemies);

void draw_explosion_alien2(enemies *p_enemies);


void update_explosion_alien3(enemies *p_enemies);

void draw_explosion_alien3(enemies *p_enemies);

#endif // ALIEN_EXPLOSION_H_INCLUDED
