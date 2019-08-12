#ifndef GAME_MENU_H 
#define GAME_MENU_H 

#include <allegro5/allegro_font.h>

#include "game_state.h"
#include "player_ship.h"

#define OPTIONS_SPACING 60

enum menu_options {
    GAME_SCREEN,
    SCORE_SCREEN,
    EXIT_SCREEN,
    MENU_SCREEN
};

typedef struct {
    Sprite background;
    int selection;
    ALLEGRO_FONT *font;
} GameMenu;

bool init_game_menu(GameMenu *menu);
void draw_menu(GameMenu *menu);
void wait_menu_selection(GameMenu *menu, GameState *game);
void free_menu_resources(GameMenu *menu);

#endif