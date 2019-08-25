#ifndef GAME_MENU_H 
#define GAME_MENU_H 

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "game_state.h"
#include "player_ship.h"

#define OPTIONS_SPACING 60

enum menu_options {
    GAME_SCREEN,
    SCORE_SCREEN,
    EXIT_SCREEN,
    MENU_SCREEN,
};

typedef struct {
    int current_esc_bitmap;
    bool back_option_selected;
    ALLEGRO_BITMAP *esc_img_1;
    ALLEGRO_BITMAP *esc_img_2;
}esc_menu;


typedef struct {
    Sprite background;
    int selection;
    ALLEGRO_FONT *font;
    esc_menu Esc_menu;
} GameMenu;



bool init_game_menu(GameMenu *menu);
void draw_menu(GameMenu *menu);
void wait_menu_selection(GameMenu *menu, GameState *game);
void free_menu_resources(GameMenu *menu);

#endif