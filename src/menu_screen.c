#include <stdbool.h>

#include "game_state.h"
#include "menu_screen.h"
#include "events.h"


// Inicializa as informações do menu do jogo
bool init_game_menu(GameMenu *menu) {
    menu->background.bitmap = al_load_bitmap("assets/images/menu_background.png");
    if(menu->background.bitmap == NULL) {
        fprintf(stderr, "Failed to load menu background!\n");
        return false;
    }
    menu->background.height = al_get_bitmap_height(menu->background.bitmap);
    menu->background.width = al_get_bitmap_width(menu->background.bitmap);

    menu->font = al_load_font("assets/fonts/Roboto-Regular.ttf", 36, 0);
    if(menu->font == NULL) {
        fprintf(stderr, "Error loading menu font!\n");
        return false;
    }

    // Opção selecionada atualmente no menu
    menu->selection = GAME_SCREEN;

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

    al_draw_scaled_bitmap(menu->background.bitmap,
                          0, 0,
                          menu->background.width, menu->background.height,
                          0, 0,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          0);
    // Posição da primeira opção
    int pos_y = SCREEN_HEIGHT / 2;

    const char options[3][12] = {"Iniciar", "Pontuação", "Sair"};
    for(int i=0; i<3; i++) {
        ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);

        // Colore a opção selecionada
        if(i == menu->selection)
            color = al_map_rgb(0, 0, 127);

        al_draw_text(menu->font,
                    color,
                    0, pos_y,
                    0,
                    options[i]);
        // Espaçamento entre as opções
        pos_y += OPTIONS_SPACING;
    }

    al_flip_display();
}

// Altera a opção selecionada no menu
void wait_menu_selection(GameMenu *menu, GameState *game) {
    update_menu_screen(menu);
    DEBUG_PRINT("Menu draw finished...\n");

    bool option_selected = false;
    while(!option_selected) {
        ALLEGRO_EVENT event;
        al_wait_for_event(game->event_queue, &event);
        process_events(game, &event);

        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            if(game->keys_pressed[DOWN])
                if(menu->selection < EXIT_SCREEN) {
                    menu->selection++;
                    update_menu_screen(menu);
                }
            if(game->keys_pressed[UP])
                if(menu->selection > GAME_SCREEN) {
                    menu->selection--;
                    update_menu_screen(menu);
                }

            if(game->keys_pressed[SPACE]) {
                game->current_screen = menu->selection;
                option_selected = true;

                // Sai do jogo ao escolher a opção "sair"
                if(game->current_screen == EXIT_SCREEN)
                    game->running = false;

                // Reseta o estado de todas as teclas
                for(int i=0; i<ESC; i++)
                    game->keys_pressed[i] = false;
            }

            // Sai do jogo ao pressionar ESC
            if(game->keys_pressed[ESC]) {
                game->running = false;
                option_selected = true;
            }
        }
    }
}

// Libera os recursos alocados pelo programa
void free_menu_resources(GameMenu *menu) {
    al_destroy_bitmap(menu->background.bitmap);
    al_destroy_font(menu->font);
    al_destroy_bitmap((*menu).Esc_menu.esc_img_1);
    al_destroy_bitmap((*menu).Esc_menu.esc_img_2);
    al_destroy_bitmap((*menu).Endgame_menu.victory_img_1);
    al_destroy_bitmap((*menu).Endgame_menu.victory_img_2);
    al_destroy_bitmap((*menu).Endgame_menu.defeat_img_1);
    al_destroy_bitmap((*menu).Endgame_menu.defeat_img_2);
}
