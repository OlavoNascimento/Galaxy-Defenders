#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include <stdbool.h>
#include <allegro5/allegro5.h>

typedef struct {
    ALLEGRO_BITMAP *bitmap;
    float width;
    float height;
} Sprite;

typedef struct {
    Sprite sprite;
    int alive;
    Laser *fired;
} PlayerLasers;

typedef struct {
    Sprite sprite;
    float pos_x;
    float pos_y;
    bool alive;
    PlayerLasers lasers;
} PlayerShip;

bool load_player_laser_sprite(PlayerShip *ps);
bool init_player_laser(PlayerShip *ps);
bool init_player_ship(PlayerShip *ps);

void add_player_laser_fired(PlayerShip *ps);
void remove_player_laser_fired(PlayerShip *ps);
void update_player_lasers_positions(PlayerShip *ps);

void draw_player_lasers(PlayerShip *ps);
void draw_player_ship(PlayerShip *ps);

#endif