#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include "game_state.h"
#include "menu_screen.h"
#include "game_screen.h"
#include "events.h"
#include "player_ship.h"
#include "enemies.h"
#include "main.h"


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

    al_init_font_addon();

    if(!al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize Allegro ttf addon!");
        return false;
    }
    return true;
}

/*
void free_basic_resources(){
    //liberando os recursos usados no programa:
    al_destroy_bitmap(img_exp_bar);
    al_destroy_bitmap(alien1img);
    al_destroy_bitmap(alien2img);
    al_destroy_bitmap(alien3img);
    al_destroy_bitmap(exp_img);
    al_destroy_bitmap(alien_bullet_img);

    for(int i=0; i<NUM_BARRIERS; i++){
            al_destroy_bitmap(img_bar[i]);
    }
}*/

/*
bool init_basic_resources(void){
    //imagem das barreiras:
    img_bar[0] = al_load_bitmap("assets/images/barrier00.png");
    img_bar[1] = al_load_bitmap("assets/images/barrierdown.png");
    img_bar[2] = al_load_bitmap("assets/images/barrierup.png");
    img_bar[3] = al_load_bitmap("assets/images/barrier01.png");

    for(int i=0; i<NUM_BARRIERS; i++)
    {
        if(!img_bar[i]){
            fprintf(stderr, "Error: could not load barrier image.\n");
            free_basic_resources();
        }
    }

    //imagem da explosao da barreira
    img_exp_bar = al_load_bitmap("assets/images/img_exp_bar.jpg");
    if(!img_exp_bar){
        fprintf(stderr, "Error: could not load explosion barrier image.\n");
        free_basic_resources();
        return 1;
    }
    al_convert_mask_to_alpha(img_exp_bar, al_map_rgb(255,255,255));

    return true;
}*/

int main() {
    if(!allegro_init())
        return 1;

    //if(!init_basic_resources())
        //return 1;

    // Cria e carrega as informações do jogo
    GameState game;
    if(!init_game_state(&game))
        return 1;
    DEBUG_PRINT("Loaded game state...\n");

    GameMenu menu;
    if(!init_game_menu(&menu))
        return 1;

    // Inicia o timer que atualiza a tela
    al_start_timer(game.screen_timer);

    while(game.running) {
        DEBUG_PRINT("Loaded game menu...\n");
        wait_menu_selection(&menu, &game);
        DEBUG_PRINT("Game menu exited...\n");

        if(game.current_screen == GAME_SCREEN) {

            //barreiras:
            //InitBarrier();

            //inicializa os inimigos:
            enemies Enemies;
            if(!InitEnemies(&Enemies))
                return 1;

            // Cria e carrega a nave do jogador
            PlayerShip player_ship;
            if(!init_player_ship(&player_ship))
                return 1;
            DEBUG_PRINT("Loaded player ship...\n");
            DEBUG_PRINT("Current lifes %d...\n", player_ship.lives);

            while(player_ship.lives > 0)
                process_game_events(&game, &player_ship, &Enemies);
            free_player_resources(&player_ship);
            free_enemies_resources(&Enemies);
        }
    }

    DEBUG_PRINT("Stopping game...\n");
    free_menu_resources(&menu);
    free_game_state_resources(&game);
    //free_basic_resources();

    return 0;
}
