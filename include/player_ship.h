#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include <stdbool.h>

#include "game_state.h"

typedef struct {
    Sprite sprite;
    int alive;
    Laser *fired;
} PlayerLasers;

typedef struct {
    Sprite sprite;
    Sprite lives_sprite;
    float pos_x;
    float pos_y;
    int lives;
    PlayerLasers lasers;
} PlayerShip;

bool init_player_laser(PlayerShip *player);
bool init_player_ship(PlayerShip *player);

void add_player_laser_fired(PlayerShip *player);
void remove_player_laser_fired(PlayerShip *player, int laser_pos);
void update_player_lasers(PlayerShip *player);

void draw_player_lasers(PlayerShip *player);
void draw_player_ship(PlayerShip *player);
void draw_player_lives(PlayerShip *player);

void free_player_resources(PlayerShip *player);

#endif