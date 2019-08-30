#include <stdbool.h>

#include "game_state.h"
#include "menu_screen.h"
#include "events.h"


// Desenha o fundo da tela de tutorial
void draw_tutorial_screen(GameState *game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    Sprite bg;
    bg.bitmap = al_load_bitmap("assets/images/tela_de_tutorial.jpg");
    if(bg.bitmap == NULL)
        fprintf(stderr, "Error loading tutorial background image!\n");

    bg.width = al_get_bitmap_width(bg.bitmap);
    bg.height = al_get_bitmap_height(bg.bitmap);

    al_draw_scaled_bitmap(bg.bitmap,
                          0, 0,
                          bg.width,
                          bg.height,
                          0, 0,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          0);
    al_flip_display();
    DEBUG_PRINT("Tutorial screen draw finished!\n");

    while(!game->keys_pressed[ESC]) {
        ALLEGRO_EVENT event;
        al_wait_for_event(game->event_queue, &event);
        process_events(game, &event);
    }
    DEBUG_PRINT("Exiting tutorial screen!\n");

    game->current_screen = MENU_SCREEN;
    al_destroy_bitmap(bg.bitmap);
}
