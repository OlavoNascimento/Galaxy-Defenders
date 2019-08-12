#include "game_state.h"
#include "player_ship.h"
#include "events.h"
#include "menu_screen.h"


// Controla o movimento do jogador
void process_player_movement(GameState *game, PlayerShip *player) {
    if(game->keys_pressed[UP]) {
        // Impede que a nave ultrapasse as barreiras
        if(player->pos_y - PLAYER_SPEED > SCREEN_HEIGHT/1.3) {
            player->pos_y -= PLAYER_SPEED;
            game->draw = true;
        }
    }
    if(game->keys_pressed[DOWN]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_y + PLAYER_SPEED <= SCREEN_HEIGHT - player->sprite.height) {
            player->pos_y += PLAYER_SPEED;
            game->draw = true;
        }
    }
    if(game->keys_pressed[LEFT]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_x - PLAYER_SPEED >= 0) {
            player->pos_x -= PLAYER_SPEED;
            game->draw = true;
        }
    }
    if(game->keys_pressed[RIGHT]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_x + PLAYER_SPEED < SCREEN_WIDTH - player->sprite.width)  {
            player->pos_x += PLAYER_SPEED;
            game->draw = true;
        }
    }

    if(player->lasers.alive > 0)  {
        // Atualiza a posição dos lasers do jogador
        // removendo-os caso necessário
        for(int i=0; i<player->lasers.alive; i++) 
            player->lasers.fired[i].pos_y -= PLAYER_LASER_SPEED;

        // Remove o primeiro disparo do array caso ele tenha saido da tela
        if(player->lasers.fired[0].pos_y < 0)
            remove_player_laser_fired(player);

        game->draw = true;
    }
}

// Controla os disparos do jogador
void process_player_firing(GameState *game, PlayerShip *player) {
    bool fire = false;
    if(player->lasers.alive > 0 && player->lasers.alive < PLAYER_MAX_LASER_COUNT) {
        int last_laser = player->lasers.alive - 1;
        int dist_laser = player->pos_y - player->lasers.fired[last_laser].pos_y;
        if(dist_laser > SCREEN_HEIGHT / PLAYER_FIRING_SPEED) {
            fire = true;
        }
    } else if(player->lasers.alive == 0) {
        fire = true;
    }
    // Caso espaço esteja pressionado e o ultimo disparo do jogador 
    // tenha uma distância mínima, adiciona um novo disparo  
    if(game->keys_pressed[SPACE] && fire) {
        add_player_laser_fired(player);
        game->draw = true;
    } 
}

// Atualiza a tela do jogo
void update_game_screen(PlayerShip *player) {
    // DEBUG_PRINT("Updating game screen!\n");
    al_clear_to_color(al_map_rgb(0, 0, 0));

    draw_player_ship(player);
    draw_player_lasers(player);

    al_flip_display();
}


// Modifica a posição dos sprites na tela
void process_player_events(GameState *game, PlayerShip *player) {
    ALLEGRO_EVENT event;
    al_wait_for_event(game->event_queue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER) {
        process_player_movement(game, player);
        process_player_firing(game, player);
    } else {
        process_events(game, &event);
        if(game->keys_pressed[ESC]) {
            player->alive = false;
            game->current_screen = MENU_SCREEN;
        }
    }

    if(game->draw && al_is_event_queue_empty(game->event_queue)) {
        game->draw = false;
        update_game_screen(player);
    }
}