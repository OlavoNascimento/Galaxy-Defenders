#include <stdbool.h>

#include "game_state.h"
#include "menu_screen.h"
#include "events.h"


// Inicializa as informações do menu do jogo
bool init_game_menu(GameMenu *menu) {
    menu->backgrounds[GAME_SCREEN].bitmap = al_load_bitmap("assets/images/menu_01_dc.jpg");
    menu->backgrounds[TUTORIAL_SCREEN].bitmap = al_load_bitmap("assets/images/menu_02_dc.jpg");
    menu->backgrounds[EXIT_SCREEN].bitmap = al_load_bitmap("assets/images/menu_03_dc.jpg");

    for(int i=0; i<=EXIT_SCREEN; i++) {
        if(menu->backgrounds[i].bitmap == NULL) {
            fprintf(stderr, "Failed to load menu %d background!\n", i);
            return false;
        }
        menu->backgrounds[i].height = al_get_bitmap_height(menu->backgrounds[i].bitmap);
        menu->backgrounds[i].width = al_get_bitmap_width(menu->backgrounds[i].bitmap);
    }

    // Opção selecionada inicialmente no menu
    menu->selection = TUTORIAL_SCREEN;

    //imagens do esc menu:
        (*menu).Esc_menu.esc_img_1 = al_load_bitmap("assets/images/esc_img_1.png");
        if(!(*menu).Esc_menu.esc_img_1){
            fprintf(stderr, "Failed to load esc_img_1 !\n");
            return false;
        }

        (*menu).Esc_menu.esc_img_2 = al_load_bitmap("assets/images/esc_img_2.png");
        if(!(*menu).Esc_menu.esc_img_2){
            fprintf(stderr, "Failed to load esc_img_2 !\n");
            return false;
        }
    //}

    //imagens do end-game menu:
        (*menu).Endgame_menu.victory_img_1 = al_load_bitmap("assets/images/victory_img_1.jpg");
        if(!(*menu).Endgame_menu.victory_img_1){
            fprintf(stderr, "Failed to load victory_img_1 !\n");
            return false;
        }

        (*menu).Endgame_menu.victory_img_2 = al_load_bitmap("assets/images/victory_img_2.jpg");
        if(!(*menu).Endgame_menu.victory_img_2){
            fprintf(stderr, "Failed to load victory_img_2 !\n");
            return false;
        }

        (*menu).Endgame_menu.defeat_img_1 = al_load_bitmap("assets/images/defeat_img_1.jpg");
        if(!(*menu).Endgame_menu.defeat_img_1){
            fprintf(stderr, "Failed to load defeat_img_1 !\n");
            return false;
        }

        (*menu).Endgame_menu.defeat_img_2 = al_load_bitmap("assets/images/defeat_img_2.jpg");
        if(!(*menu).Endgame_menu.defeat_img_2){
            fprintf(stderr, "Failed to load defeat_img_2 !\n");
            return false;
        }
    //}

    (*menu).Endgame_menu.start_v = false;  //indica quando a tela de vitoria deve aparecer;
    (*menu).Endgame_menu.start_d = false;  //indica quando a tela de derrota deve aparecer;
    (*menu).Endgame_menu.ignore_main_menu = false;

    return true;
}

// Redesenha a tela de menu e atualiza a opção selecionada
void update_menu_screen(GameMenu *menu) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_scaled_bitmap(menu->backgrounds[menu->selection].bitmap,
                          0, 0,
                          menu->backgrounds[menu->selection].width,
                          menu->backgrounds[menu->selection].height,
                          0, 0,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          0);
    al_flip_display();
}

// Altera a opção selecionada no menu
void wait_menu_selection(GameMenu *menu, GameState *game) {
    //toca o audio de fundo do menu:
    al_set_audio_stream_playing((*game).Audio.UI_background, true);

    update_menu_screen(menu);
    DEBUG_PRINT("Menu draw finished...\n");

    bool option_selected = false;
    while(!option_selected) {
        ALLEGRO_EVENT event;
        al_wait_for_event(game->event_queue, &event);
        process_events(game, &event);

        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(game->keys_pressed[DOWN] && menu->selection < EXIT_SCREEN) {
                menu->selection++;
                update_menu_screen(menu);
                al_play_sample((*game).Audio.changing_option, 1.5, -1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            if(game->keys_pressed[UP] && menu->selection > GAME_SCREEN) {
                menu->selection--;
                update_menu_screen(menu);
                al_play_sample((*game).Audio.changing_option, 1.5, -1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }

            if(game->keys_pressed[ENTER]) {
                game->current_screen = menu->selection;
                option_selected = true;
                al_play_sample((*game).Audio.selecting_option, 1.5, -1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                // Sai do jogo ao escolher a opção "sair"
                if(game->current_screen == EXIT_SCREEN)
                    game->running = false;

                // Reseta o estado de todas as teclas
                for(int i=0; i<=ESC; i++)
                    game->keys_pressed[i] = false;
            }

            // Sai do jogo ao pressionar ESC
            if(game->keys_pressed[ESC]) {
                game->running = false;
                option_selected = true;
                al_play_sample((*game).Audio.back_option, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }
}

// Libera os recursos alocados pelo programa
void free_menu_resources(GameMenu *menu) {
    for(int i=0; i<=EXIT_SCREEN; i++)
        al_destroy_bitmap(menu->backgrounds[i].bitmap);
    al_destroy_bitmap((*menu).Esc_menu.esc_img_1);
    al_destroy_bitmap((*menu).Esc_menu.esc_img_2);
    al_destroy_bitmap((*menu).Endgame_menu.victory_img_1);
    al_destroy_bitmap((*menu).Endgame_menu.victory_img_2);
    al_destroy_bitmap((*menu).Endgame_menu.defeat_img_1);
    al_destroy_bitmap((*menu).Endgame_menu.defeat_img_2);
}
