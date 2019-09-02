#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdio.h>

// Comprimento da tela
#define SCREEN_WIDTH 1280
// Altura da tela
#define SCREEN_HEIGHT 720
// Taxa de atualização da tela
#define FPS 60

// Margem entre a nave do jogador e a parte inferior da tela
#define PLAYER_BOTTOM_MARGIN 6

// Velocidade do movimento da nave do jogador
#define PLAYER_SPEED 4

// Velocidade de disparo do jogador
#define PLAYER_FIRING_SPEED 3
// Velocidade do laser do jogador
#define PLAYER_LASER_SPEED 6
// Quantidade máxima de disparos jogador
#define PLAYER_MAX_LASER_COUNT 10


// Ativa ou desativa mensagens de debug
#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINT(str, vars...) printf(str, ## vars)
#else
    #define DEBUG_PRINT(str, vars...)
#endif

// Teclas disponíveis ao jogador
enum keys {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    ESC,
    ENTER
};

// Imagens do jogo
typedef struct {
    ALLEGRO_BITMAP *bitmap;
    float width;
    float height;
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
} Sprite;

// Posição dos lasers das naves
typedef struct {
    float pos_x;
    float pos_y;
} Laser;

//struct com as variaveis de audio:
typedef struct{
    //UI:
    ALLEGRO_SAMPLE *changing_option;
    ALLEGRO_SAMPLE *selecting_option;
    ALLEGRO_SAMPLE *back_option;
    ALLEGRO_SAMPLE *victory_song;
    ALLEGRO_SAMPLE *defeat_song;
    ALLEGRO_SAMPLE *esc_midgame;
    ALLEGRO_AUDIO_STREAM *UI_background;
    //in-game:
    ALLEGRO_SAMPLE *player_shot;
    ALLEGRO_SAMPLE *player_explosion;
    ALLEGRO_SAMPLE *barrier_collision;
    ALLEGRO_SAMPLE *barrier_explosion;
    ALLEGRO_SAMPLE *alien_shot;
    ALLEGRO_SAMPLE *alien_explosion;
    ALLEGRO_AUDIO_STREAM *ingame_background;
}audio;

// Armazena as informações do estado atual do jogo
typedef struct {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    int current_screen;
    bool draw;
    // Timer responsável por atualizar a tela do jogo
    ALLEGRO_TIMER *screen_timer;
    // Indica se o jogo está rodando
    bool running;
    // Array indicando os botões pressionados pelo jogador
    bool *keys_pressed;
    // Ponteiro de controle da fonte do score
    ALLEGRO_FONT *font_score;
    //variavel de audio:
    audio Audio;
} GameState;


bool init_game_state(GameState *game);
void free_game_state_resources(GameState *game);

#endif
