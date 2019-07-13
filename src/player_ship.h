#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include <stdbool.h>
#include <allegro5/allegro5.h>

typedef struct {
    ALLEGRO_BITMAP *sprite;
    float pos_x;
    float pos_y;
    bool alive;
} PlayerShip;

void load_player_ship(PlayerShip *ps);
void draw_player_ship(PlayerShip *ps);

#endif