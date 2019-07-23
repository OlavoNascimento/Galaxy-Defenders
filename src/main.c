#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "main.h"
#include "events.h"
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

// Inicia o estado inicia do jogo
// retorna true caso o jogo seja iniado com sucesso
bool init_game_state(GameState *game) {
    // Cria a tela do jogo
    game->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!game->display) {
        fprintf(stderr, "Failed to create display!\n");
        return false;
    }

    // Cria o evento responsavel por atualizar a tela
    game->screen_timer = al_create_timer(1.0 / FPS);
    if(!game->screen_timer) {
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
    // Adiciona eventos do timer que atualiza a tela a fila de eventos
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->screen_timer));

    // Boolean usado para saber quando atualizar a tela
    game->draw = true;

    // Inicializa o array das teclas pressionadas com 
    // seta esquerda e direita sendo falso(0)
    game->keys_pressed = (bool*) calloc(sizeof(bool) * 2, 2);
    if(game->keys_pressed == NULL) {
        fprintf(stderr, "Failed to allocate memory for keys array!\n");
        return false;
    }

    return true;
}

// Libera os recursos alocados pelo programa
void free_resources(GameState *game, PlayerShip *player) {
    al_destroy_bitmap(player->sprite.bitmap);
    al_destroy_bitmap(player->lasers.sprite.bitmap);
    free(player->lasers.fired);
    player->lasers.fired = NULL;
    al_destroy_timer(game->screen_timer);
    al_destroy_event_queue(game->event_queue);
    al_destroy_display(game->display);
}


int main() {
    // Inicia o Allegro
    if(!allegro_init())
        return 1;

    // Cria e carrega as informações do jogo
    GameState game;
    if(!init_game_state(&game))
        return 1;
    DEBUG_PRINT("Loaded game state...\n");

    // Cria e carrega a nave do jogador
    PlayerShip player_ship;
    if(!init_player_ship(&player_ship))
        return 1;
    DEBUG_PRINT("Loaded player ship...\n");

    // Inicia o timer que atualiza a tela
    al_start_timer(game.screen_timer);
 
    while(player_ship.alive) {
        ALLEGRO_EVENT event;
        // Espera um novo evento ser adicionado a fila
        al_wait_for_event(game.event_queue, &event);
        process_events(&game, &player_ship, &event);
    }

    DEBUG_PRINT("Stopping game...\n");
    free_resources(&game, &player_ship);
    return 0;
}

