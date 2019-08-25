#include <allegro5/allegro5.h>

#include "game_state.h"


// Atualiza o estado do jogo de acordo com a teclaa
// pressionanda pelo jogador
void process_key_down_event(ALLEGRO_EVENT *event, GameState *game) {
    switch(event->keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            game->keys_pressed[ESC] = true;
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
void process_key_up_event(ALLEGRO_EVENT *event, GameState *game) {
    switch(event->keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:
            game->keys_pressed[ESC] = false;
            break;
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

// Atualiza as informações do jogo e do jogador 
// de acordo com o evento 
void process_events(GameState *game, ALLEGRO_EVENT *event) {
    switch(event->type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            process_key_down_event(event, game);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            process_key_up_event(event, game);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // Caso o evento seja o clique para fechar a janela
            // marca o jogo como finalizado
            game->running = false;
            break;
    }
}