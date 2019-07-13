#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "main.h"
#include "player_ship.h"

// Carrega as informações da nave do jogador
void load_player_ship(PlayerShip *ps) {
    ps->sprite = al_load_bitmap("assets/player_ship.png");
    if(ps->sprite == NULL) {
        fprintf(stderr, "Failed to load player ship sprite!\n");
    }
    ps->alive = true;
    // Posiciona o jogador no centro da tela
    ps->pos_x = (SCREEN_WIDTH/2) - (al_get_bitmap_width(ps->sprite)/2);
    // Posiciona o jogador no canto inferior da tela
    ps->pos_y = SCREEN_HEIGHT - al_get_bitmap_height(ps->sprite) - 6;
}

// Desenha a nave do jogador na posição atual
void draw_player_ship(PlayerShip *ps) {
    al_draw_bitmap(ps->sprite, ps->pos_x, ps->pos_y, 0);
}