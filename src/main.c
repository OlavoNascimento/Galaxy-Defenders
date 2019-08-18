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
    if(!al_init_font_addon()) {
        fprintf(stderr, "Failed to initialize Allegro font addon!");
        return false;
    }
    if(!al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize Allegro ttf addon!");
        return false;
    }
    return true;
}

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
}

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


    //imagem dos aliens da 1 fileira:
    alien1img = al_load_bitmap("assets/images/alien1.png");
    if(!alien1img){
        fprintf(stderr, "Error: could not load alien1 image.\n");
        free_basic_resources();
        return false;
    }
    al_convert_mask_to_alpha(alien1img, al_map_rgb(0, 0 ,0));

    //imagem dos aliens da 2 e 3 fileira:
    alien2img = al_load_bitmap("assets/images/alien2.png");
    if(!alien2img){
        fprintf(stderr, "Error: could not load alien2 image.\n");
        free_basic_resources();
        return false;
    }
    al_convert_mask_to_alpha(alien2img, al_map_rgb(0, 0 ,0));

    //imagem dos aliens da 4 e 5 fileira:
    alien3img = al_load_bitmap("assets/images/alien3.png");
    if(!alien3img){
        fprintf(stderr, "Error: could not load alien3 bitmap");
        free_basic_resources();
        return false;
    }
    al_convert_mask_to_alpha(alien3img, al_map_rgb(0, 0 ,0));

    //imagem da explosao dos aliens:
    exp_img = al_load_bitmap("assets/images/exp.png");
    if(!exp_img){
        fprintf(stderr, "Error: could not load explosion bitmap");
        free_basic_resources();
        return false;
    }
    al_convert_mask_to_alpha(exp_img, al_map_rgb(0, 0 , 0));

    //imagem da bala dos aliens:
    alien_bullet_img = al_load_bitmap("assets/images/alienshot.png");
    if(!alien_bullet_img){
        fprintf(stderr, "Error: could not load alien bullet bitmap");
        free_basic_resources();
        return false;
    }
    al_convert_mask_to_alpha(alien_bullet_img, al_map_rgb(0, 0 , 0));

    return true;
}

int main() {
    if(!allegro_init())
        return 1;

    if(!init_basic_resources())
        return 1;

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
            //inicializando objetos do programa{
                //barreiras:
                InitBarrier();

                //inimigos 1 linha:
                InitAlien1(alien1, NUM_ALIEN);

                //inimigos 2 e 3 linha:
                InitAlien2(alien2, 2);

                //inimigos 4 e 5 linha:
                InitAlien3(alien3, 2);

                //tiro dos aliens:
                Init_aBullet();

            //}

            // Cria e carrega a nave do jogador
            PlayerShip player_ship;
            if(!init_player_ship(&player_ship))
                return 1;
            DEBUG_PRINT("Loaded player ship...\n");
            DEBUG_PRINT("Current lifes %d...\n", player_ship.lives);

            while(player_ship.lives > 0) 
                process_game_events(&game, &player_ship);
            free_player_resources(&player_ship);
        }
    }

    DEBUG_PRINT("Stopping game...\n");
    free_menu_resources(&menu);
    free_game_state_resources(&game);
    free_basic_resources();

    return 0;
}