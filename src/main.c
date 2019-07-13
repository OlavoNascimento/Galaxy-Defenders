#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "main.h"
#include "player_ship.h"


// Inicia todas os recursos do Allegro necessários
bool allegro_init() {
    if(!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!");
        return false;
    }
    if(!al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize Allegro image addon!");
        return false;
    }
    if(!al_install_keyboard()) {
        fprintf(stderr, "Failed to initialize Allegro keyboard addon!");
        return false;
    }
    return true;
}

bool load_game_state(GameState *game) {
    // Cria a tela do jogo
    game->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!game->display) {
        fprintf(stderr, "Failed to create display!\n");
        return false;
    }

    // Cria o evento responsavel por atualizar a tela
    game->timer = al_create_timer(1.0 / FPS);
    if(!game->timer) {
        fprintf(stderr, "Failed to create timer!\n");
        return false;
    }

    // Cria a fila de eventos
    game->event_queue = al_create_event_queue();
    if(!game->event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        return false;
    }
    // Adiciona eventos do display a fila de eventos
    al_register_event_source(game->event_queue, al_get_keyboard_event_source());
    // Adiciona eventos do teclado a fila de eventos
    al_register_event_source(game->event_queue, al_get_display_event_source(game->display));
    // Adiciona eventos do timer a fila de eventos
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->timer));

    // Boolean usado para saber quando atualizar a tela
    game->draw = true;

    return true;
}

// Atualiza a tela do jogo
void update_display(PlayerShip *player) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    draw_player_ship(player);
    al_flip_display();
}

// Recebe o estado do teclado e processa as ações correspondentes
// a cada tecla pressionada
void process_keypress(ALLEGRO_KEYBOARD_STATE *keyboard_state, PlayerShip *player) {
    // Caso a seta esquerda seja pressionada
    if(al_key_down(keyboard_state, ALLEGRO_KEY_LEFT)) {
        // Impede que a nave saia da tela
        if(player->pos_x - PLAYER_SPEED >= 0) {
            player->pos_x -= PLAYER_SPEED;
        }
    } 
    // Caso a seta direta seja pressionada
    if (al_key_down(keyboard_state, ALLEGRO_KEY_RIGHT)) {
        // Impede que a nave saia da tela
        if(player->pos_x + PLAYER_SPEED < SCREEN_WIDTH - al_get_bitmap_width(player->sprite)) {
            player->pos_x += PLAYER_SPEED;
        }
    }
}

// Atualiza as informações do jogo e do jogador 
// de acordo com o evento 
void process_events(GameState *game, PlayerShip *player, ALLEGRO_EVENT event) {
    switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            // Caso a tecla ESC seja pressionada
            // Marca o jogo como finalizado
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                player->alive = false;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // Caso o evento seja o clique para fechar a janela
            // Marca o jogo como finalizado
            DEBUG_PRINT("Clique para fechar a janela registrado...\n");
            player->alive = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            // Se o evento for causado pelo timer checa o teclado
            // agindo de acordo com a tecla pressionada
            al_get_keyboard_state(&game->keyboard_state);
            process_keypress(&game->keyboard_state, player);

            // Marca que a tela deve ser atualiza
            game->draw = true;
            break;
    }

    if(game->draw) {
        game->draw = false;
        update_display(player);
    }
}

// Libera os recursos alocados pelo programa
void free_resources(GameState *game, PlayerShip *player) {
    al_destroy_bitmap(player->sprite);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->event_queue);
    al_destroy_display(game->display);
}


int main() {
    // Inicia o Allegro
    if(!allegro_init()) {
        return 1;
    }

    // Cria e carrega as informações do jogo
    GameState game;
    if(!load_game_state(&game)) {
        return 1;
    }
    DEBUG_PRINT("Loaded game state...\n");

    // Cria e carrega a nave do jogador
    PlayerShip player_ship;
    load_player_ship(&player_ship);
    DEBUG_PRINT("Loaded player player...\n");

    // Inicia o timer
    al_start_timer(game.timer);
 
    while(player_ship.alive) {
        ALLEGRO_EVENT event;
        // Espera um novo evento ser adicionado a fila
        al_wait_for_event(game.event_queue, &event);
        process_events(&game, &player_ship, event);
    }

    DEBUG_PRINT("Stopping game...\n");
    free_resources(&game, &player_ship);
    return 0;
}

