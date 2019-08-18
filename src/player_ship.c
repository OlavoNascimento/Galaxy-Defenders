#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "game_state.h"
#include "player_ship.h"


// Carrega as informações do disparo do jogador
bool init_player_laser(PlayerShip *ps) {
    // Carrega a imagem do laser do jogador
    ps->lasers.sprite.bitmap = al_load_bitmap("assets/images/player_laser.png");
    if(ps->lasers.sprite.bitmap == NULL) {
        fprintf(stderr, "Failed to load player laser sprite!\n");
        return false;
    }
    ps->lasers.sprite.width = al_get_bitmap_width(ps->lasers.sprite.bitmap);
    ps->lasers.sprite.height = al_get_bitmap_height(ps->lasers.sprite.bitmap);

    // Número de disparos ainda dentro da tela
    ps->lasers.alive = 0;
    // Array contendo os disparos aida dentro da tela
    ps->lasers.fired = (Laser*) malloc(sizeof(Laser) * PLAYER_MAX_LASER_COUNT);
    return true;
}

// Carrega as informações da nave do jogador
bool init_player_ship(PlayerShip *ps) {
    // Carrega a imagem da nave do jogador
    ps->sprite.bitmap = al_load_bitmap("assets/images/player_ship.png");
    if(ps->sprite.bitmap == NULL) {
        fprintf(stderr, "Failed to load player ship sprite!\n");
        return false;
    }
    ps->sprite.width = al_get_bitmap_width(ps->sprite.bitmap);
    ps->sprite.height = al_get_bitmap_height(ps->sprite.bitmap);

    ps->lives = 3;
    // Posiciona o jogador no centro da tela
    ps->pos_x = (SCREEN_WIDTH/2) - (ps->sprite.width/2);
    // Posiciona o jogador no canto inferior da tela
    ps->pos_y = SCREEN_HEIGHT - ps->sprite.height - PLAYER_BOTTOM_MARGIN;

    // Carrega os dados dos lasers do jogador
    if(!init_player_laser(ps))
        return false;
    return true;
}

// Adiciona um disparo ativo ao array de disparos do jogador
void add_player_laser_fired(PlayerShip *ps) {
    // Centraliza o sprite do laser com o sprite da nave
    ps->lasers.fired[ps->lasers.alive].pos_x = ps->pos_x + (ps->sprite.width / 2) -
        (ps->lasers.sprite.width / 2);
    // Posiciona o sprite do laser em frente a nave
    ps->lasers.fired[ps->lasers.alive].pos_y = ps->pos_y - ps->sprite.height -
        PLAYER_BOTTOM_MARGIN;
    ps->lasers.alive++;
}

// Remove o primeiro elemento do array de disparos do jogador
// sobrescrevendo o elemento atual com o próximo
void remove_player_laser_fired(PlayerShip *ps, int laser_pos) {
    for(int i = laser_pos; i < ps->lasers.alive; i++)
        ps->lasers.fired[i] = ps->lasers.fired[i+1];
    ps->lasers.alive--;
}

// Desenha os disparos do jogador em suas posições atuais
void draw_player_lasers(PlayerShip *ps) {
    for(int i = 0; i < ps->lasers.alive; i++) {
        al_draw_bitmap(ps->lasers.sprite.bitmap,
               ps->lasers.fired[i].pos_x, ps->lasers.fired[i].pos_y,
                       0);
        al_convert_mask_to_alpha(ps->lasers.sprite.bitmap, al_map_rgb(0,0,0));
    }
}

// Desenha a nave do jogador na posição atual
void draw_player_ship(PlayerShip *ps) {
    al_draw_bitmap(ps->sprite.bitmap, ps->pos_x, ps->pos_y, 0);
    al_convert_mask_to_alpha(ps->sprite.bitmap, al_map_rgb(0,0,0));
}

void free_player_resources(PlayerShip *player) {
    al_destroy_bitmap(player->sprite.bitmap);
    al_destroy_bitmap(player->lasers.sprite.bitmap);
    free(player->lasers.fired);
    player->lasers.fired = NULL;
}