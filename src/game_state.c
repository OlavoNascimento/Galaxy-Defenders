#include <stdbool.h>

#include "game_state.h"
#include "menu_screen.h"

// Inicia o estado inicia do jogo
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
    // Adiciona eventos do 6imer que atualiza a tela a fila de eventos
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->screen_timer));

    game->draw = true;

    game->running = true;

    game->current_screen = MENU_SCREEN;

    // Inicializa o array das teclas como não pressionadas
    game->keys_pressed = (bool*) calloc(sizeof(bool) * 6, 6);
    if(game->keys_pressed == NULL) {
        fprintf(stderr, "Failed to allocate memory for keys array!\n");
        return false;
    }

    return true;
}


// Libera os recursos alocados pelo programa
void free_game_state_resources(GameState *game) {
    free(game->keys_pressed);
    game->keys_pressed = NULL;
    al_destroy_timer(game->screen_timer);
    al_destroy_event_queue(game->event_queue);
    al_destroy_display(game->display);
}
