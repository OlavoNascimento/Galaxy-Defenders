#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "game_state.h"
#include "tutorial_screen.h"
#include "menu_screen.h"
#include "game_screen.h"
#include "events.h"
#include "player_ship.h"
#include "enemies.h"
#include "barrier.h"


//Inicia todas os recursos do Allegro necessários:
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

    if(!al_install_audio()){
        fprintf(stderr, "Failed to install audio subsystem!");
        return false;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "Failed to initialize acodec addon!");
        return false;
    }

     return true;
}

int main() {
    if(!allegro_init())
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

    // Esconde o cursor do mouse:
    al_hide_mouse_cursor(game.display);


    while(game.running) {
        //If usado para permitir a funcionalidade da opcao 'jogar novamente' do end-game menu
        if(!menu.Endgame_menu.ignore_main_menu){
            DEBUG_PRINT("Loaded game menu...\n");
            wait_menu_selection(&menu, &game);
            DEBUG_PRINT("Game menu exited...\n");
        }

        menu.Endgame_menu.ignore_main_menu = false;

        if(game.current_screen == GAME_SCREEN) {
            //desliga o audio de fundo do menu:
            al_set_audio_stream_playing(game.Audio.UI_background, false);

            //Ponteiro e init da barreira
            main_barrier bar;
            InitBarrier(&bar);

            enemies Enemies;
            if(!InitEnemies(&Enemies))
                return 1;

            // Cria e carrega a nave do jogador
            PlayerShip player_ship;
            if(!init_player_ship(&player_ship))
                return 1;
            DEBUG_PRINT("Loaded player ship...\n");
            DEBUG_PRINT("Current lifes %d...\n", player_ship.lives);

            //toca o audio de fundo do jogo:
            al_set_audio_stream_playing(game.Audio.ingame_background, true);

            while(player_ship.lives > 0)
                process_game_events(&game, &menu, &player_ship, &Enemies, &bar);

            free_player_resources(&player_ship);
            free_enemies_resources(&Enemies);
            free_barrier_resources(&bar);
        } else if(game.current_screen == TUTORIAL_SCREEN) {
            draw_tutorial_screen(&game);
        }
    }

    DEBUG_PRINT("Stopping game...\n");
    free_menu_resources(&menu);
    free_game_state_resources(&game);

    return 0;
}
