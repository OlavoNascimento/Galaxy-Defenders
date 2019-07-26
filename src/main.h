#ifndef MAIN_H
#define MAIN_H

#include <allegro5/allegro5.h>
#include <stdio.h>

// Comprimento da tela
#define SCREEN_WIDTH 1366
// Altura da tela
#define SCREEN_HEIGHT 766
// Taxa de atualização da tela 
#define FPS 60

// Margem entre a nave do jogador e a parte inferior da tela
#define PLAYER_BOTTOM_MARGIN 6

// Velocidade do movimento da nave do jogador
#define PLAYER_SPEED 4 
// Velocidade de disparo do jogador
#define PLAYER_FIRING_SPEED 4
// Velocidade do laser do jogador
#define PLAYER_LASER_SPEED 4 

// Ativa ou desativa mensagens de debug
#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT(str, vars...) printf(str, ## vars)
#else
    #define DEBUG_PRINT(str, vars...)
#endif

// Teclas de movimento do jogador
enum keys {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};

// Posição dos lasers das naves
typedef struct {
    float pos_x;
    float pos_y;
} Laser;

// Armazena as informações do estado atual do jogo
typedef struct {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    // Timer responsável por atualizar a tela do jogo
    ALLEGRO_TIMER *screen_timer;
    // Indica se a tela deve ser atualizada
    bool draw;
    // Array indicando os botões pressionados pelo jogador
    bool *keys_pressed;
} GameState;

#endif
