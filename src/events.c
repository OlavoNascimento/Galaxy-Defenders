#include <allegro5/allegro5.h>

#include "main.h"
#include "player_ship.h"


// Atualiza o estado do jogo de acordo com a tecla
// pressionanda pelo jogador
void process_key_down_event(ALLEGRO_EVENT *event, GameState *game, PlayerShip *player) {
    switch(event->keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            // Caso a tecla ESC seja pressionada
            // marca o jogo como finalizado
            player->alive = false;
            break;
        case ALLEGRO_KEY_UP:
            // Marca a seta pra cima como pressionada
            game->keys_pressed[UP] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            // Marca a seta pra baixo como pressionada
            game->keys_pressed[DOWN] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            // Marca a seta esquerda como pressionada
            game->keys_pressed[LEFT] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            // Marca a seta direita como pressionada
            game->keys_pressed[RIGHT] = true;
            break;
        case ALLEGRO_KEY_SPACE:
            game->keys_pressed[SPACE] = true;
            break;
    }
}

// Marca as teclas de ação do jogador como soltas
void process_key_up_event(ALLEGRO_EVENT *event, GameState *game, PlayerShip *player) {
    switch(event->keyboard.keycode) {
        case ALLEGRO_KEY_UP:
            game->keys_pressed[UP] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            game->keys_pressed[DOWN] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            game->keys_pressed[LEFT] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            game->keys_pressed[RIGHT] = false;
            break;
        case ALLEGRO_KEY_SPACE:
            game->keys_pressed[SPACE] = false;
            break;
    }
}

// Modifica a posição dos sprites na tela
void process_timer_event(GameState *game, PlayerShip *player) {
    // Move o jogador para cima
    if(game->keys_pressed[UP]) {
        // Impede que a nave suba mais alto que as barreiras
        if(player->pos_y - PLAYER_SPEED > SCREEN_HEIGHT/1.3) {
            player->pos_y -= PLAYER_SPEED;
            game->draw = true;
        }
    }
    // Move o jogador para baixo
    if(game->keys_pressed[DOWN]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_y + PLAYER_SPEED <= SCREEN_HEIGHT - player->sprite.height) {
            player->pos_y += PLAYER_SPEED;
            game->draw = true;
        }
    }
    // Move o jogador para esquerda
    if(game->keys_pressed[LEFT]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_x - PLAYER_SPEED >= 0) {
            player->pos_x -= PLAYER_SPEED;
            game->draw = true;
        }
    }
    // Move o jogador para direta
    if(game->keys_pressed[RIGHT]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_x + PLAYER_SPEED < SCREEN_WIDTH - player->sprite.width) {
            player->pos_x += PLAYER_SPEED;
            game->draw = true;
        }
    }
    int last_laser = player->lasers.alive - 1;
    int dist_laser = player->pos_y - player->lasers.fired[last_laser].pos_y;
    // Caso espaço esteja pressionado e o ultimo disparo do jogador 
    // tenha uma distância mínima, adiciona um novo disparo  
    if(game->keys_pressed[SPACE] && 
       dist_laser > (SCREEN_HEIGHT / PLAYER_FIRING_SPEED)) {
        add_player_laser_fired(player);
    }
    // Atualiza a posição dos disparos do jogador
    if(player->lasers.alive > 0) {
        update_player_lasers_positions(player);
        game->draw = true;
    }
}

// Atualiza a tela do jogo
void update_display(PlayerShip *player) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    draw_player_ship(player);
    draw_player_lasers(player);
    al_flip_display();
}

// Atualiza as informações do jogo e do jogador 
// de acordo com o evento 
void process_events(GameState *game, PlayerShip *player, ALLEGRO_EVENT *event) {
    switch(event->type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            process_key_down_event(event, game, player);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            process_key_up_event(event, game, player);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // Caso o evento seja o clique para fechar a janela
            // marca o jogo como finalizado
            player->alive = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            // Se o evento for causado pelo timer responsável
            // por atualizar a tela, modifica a posição dos sprites na tela
            process_timer_event(game, player);
            break;
    }
    // Atualiza a tela caso necessário
    if(game->draw) {
        game->draw = false;
        update_display(player);
    }
}
