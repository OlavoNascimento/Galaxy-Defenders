#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "game_state.h"
#include "player_ship.h"
#include "enemies.h"

void detect_bullet_colision_player(PlayerShip *player, enemies *p_enemies);
void process_player_movement(GameState *game, PlayerShip *player);
void process_player_firing(GameState *game, PlayerShip *player);
void process_game_events(GameState *game, PlayerShip *player, enemies *p_enemies);

#endif
