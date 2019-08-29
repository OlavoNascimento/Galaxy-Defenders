#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "game_state.h"
#include "player_ship.h"
#include "barrier.h"
#include "enemies.h"


// Carrega as informações do disparo do jogador
bool init_player_laser(PlayerShip *player) {
    // Carrega a imagem do laser do jogador
    player->lasers.sprite.bitmap = al_load_bitmap("assets/images/player_laser.png");
    if(player->lasers.sprite.bitmap == NULL) {
        fprintf(stderr, "Failed to load player laser sprite!\n");
        return false;
    }
    player->lasers.sprite.width = al_get_bitmap_width(player->lasers.sprite.bitmap);
    player->lasers.sprite.height = al_get_bitmap_height(player->lasers.sprite.bitmap);

    // Número de disparos ainda dentro da tela
    player->lasers.alive = 0;
    // Array contendo os disparos aida dentro da tela
    player->lasers.fired = (Laser*) malloc(sizeof(Laser) * PLAYER_MAX_LASER_COUNT);
    return true;
}

// Carrega as informações da nave do jogador
bool init_player_ship(PlayerShip *player) {
    // Carrega a imagem da nave do jogador
    player->sprite.bitmap = al_load_bitmap("assets/images/player_ship.png");
    if(player->sprite.bitmap == NULL) {
        fprintf(stderr, "Failed to load player ship sprite!\n");
        return false;
    }
    player->sprite.width = al_get_bitmap_width(player->sprite.bitmap);
    player->sprite.height = al_get_bitmap_height(player->sprite.bitmap);

    player->lives = 3;
    player->cont_score = 0;

    player->lives_sprite.bitmap = al_load_bitmap("assets/images/player_lives.png");
    if(player->lives_sprite.bitmap == NULL) {
        fprintf(stderr, "Failed to load player lives sprite!\n");
        return false;
    }
    player->lives_sprite.width = al_get_bitmap_width(player->lives_sprite.bitmap);
    player->lives_sprite.height = al_get_bitmap_height(player->lives_sprite.bitmap);

    // Posiciona o jogador no centro da tela
    player->pos_x = (SCREEN_WIDTH/2) - (player->sprite.width/2);
    // Posiciona o jogador no canto inferior da tela
    player->pos_y = SCREEN_HEIGHT - player->sprite.height - PLAYER_BOTTOM_MARGIN;

    // Carrega os dados dos lasers do jogador
    if(!init_player_laser(player))
        return false;
    return true;
}

// Adiciona um disparo ativo ao array de disparos do jogador
void add_player_laser_fired(PlayerShip *player) {
    // Centraliza o sprite do laser com o sprite da nave
    player->lasers.fired[player->lasers.alive].pos_x = player->pos_x + (player->sprite.width / 2) -
        (player->lasers.sprite.width / 2);
    // Posiciona o sprite do laser em frente a nave
    player->lasers.fired[player->lasers.alive].pos_y = player->pos_y - player->sprite.height -
        PLAYER_BOTTOM_MARGIN;
    player->lasers.alive++;
}

// Remove o primeiro elemento do array de disparos do jogador
// sobrescrevendo o elemento atual com o próximo
void remove_player_laser_fired(PlayerShip *player, int laser_pos) {
    DEBUG_PRINT("Removing laser %d\n", laser_pos);
    for(int i=laser_pos; i < player->lasers.alive - 1; i++)
        player->lasers.fired[i] = player->lasers.fired[i+1];
    player->lasers.alive--;
}

// Remove o primeiro elemento do array de disparos do jogador
// sobrescrevendo o elemento atual com o próximo
void update_player_lasers(PlayerShip *player) {
    if(player->lasers.alive > 0)  {
        // Atualiza a posição dos lasers do jogador
        // removendo-os caso necessário
        for(int i=0; i<player->lasers.alive; i++)
            player->lasers.fired[i].pos_y -= PLAYER_LASER_SPEED;

        // Remove o primeiro disparo do array caso ele tenha saido da tela
        if(player->lasers.fired[0].pos_y < 0)
            remove_player_laser_fired(player, 0);
    }
}

// Desenha os disparos do jogador em suas posições atuais
void draw_player_lasers(PlayerShip *player) {
    for(int i = 0; i < player->lasers.alive; i++) {
        al_draw_bitmap(player->lasers.sprite.bitmap,
               player->lasers.fired[i].pos_x, player->lasers.fired[i].pos_y,
                       0);
    }
}

// Desenha a nave do jogador na posição atual
void draw_player_ship(PlayerShip *player) {
    al_draw_bitmap(player->sprite.bitmap, player->pos_x, player->pos_y, 0);
}

// Desenha a nave do jogador na posição atual
void draw_player_lives(PlayerShip *player) {
    int pos_x = 426;
    for(int i=0; i<player->lives; i++) {
        al_draw_bitmap(player->lives_sprite.bitmap, pos_x, 15, 0);
        pos_x += player->lives_sprite.width + 4;
    }
}

void free_player_resources(PlayerShip *player) {
    al_destroy_bitmap(player->sprite.bitmap);
    al_destroy_bitmap(player->lasers.sprite.bitmap);
    free(player->lasers.fired);
    player->lasers.fired = NULL;
}
