#ifndef MAIN_H
#define MAIN_H

#include <allegro5/allegro5.h>

// Comprimento da tela
#define SCREEN_WIDTH 900
// Altura da tela
#define SCREEN_HEIGHT 650
// Taxa de atualização da tela 
#define FPS 60

// Velocidade do movimento da nave do jogador
#define PLAYER_SPEED 4 

// Ativa ou desativa mensagens de debug
#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT(str, vars...) printf(str, ## vars)
#else
    #define DEBUG_PRINT(str, vars...)
#endif

typedef struct {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    bool draw;
} GameState;

#endif