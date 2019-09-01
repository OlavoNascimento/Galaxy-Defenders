#include <stdbool.h>

#include "game_state.h"
#include "menu_screen.h"

bool create_display(GameState *game){
    //criando uma janela com a resolucao do desktop do usuario (fullscreen):
    ALLEGRO_MONITOR_INFO info;

    int res_x, res_y;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_get_monitor_info(0, &info);

    res_x = info.x2 - info.x1;
    res_y = info.y2 - info.y1;


    game->display = al_create_display(res_x, res_y);
    if(!game->display){
        fprintf(stderr, "Error: could not create display.\n");
        return false;
    }

    //redimensionando o jogo para se encaixar na resolucao do desktop do usuario:

    float red_x = res_x/(float)SCREEN_WIDTH;
    float red_y = res_y/(float)SCREEN_HEIGHT;

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, red_x, red_y);
    al_use_transform(&transform);

    return true;

}

// Inicia o estado inicia do jogo
bool init_game_state(GameState *game) {
    // Cria a fila de eventos
    game->event_queue = al_create_event_queue();
    if(!game->event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        return false;
    }

    game->font_score = al_load_font("assets/fonts/FrenteH1-Regular.ttf", 40, 0);
    if(!game->font_score){
        fprintf(stderr, "Failed to create font score!\n");
        return false;
    }

    // Cria a tela do jogo
    if(!create_display(game)) {
        fprintf(stderr, "Failed to create display!\n");
        return false;
    }

    // Cria o evento responsavel por atualizar a tela
    game->screen_timer = al_create_timer(1.0 / FPS);
    if(!game->screen_timer) {
        fprintf(stderr, "Failed to create timer!\n");
        return false;
    }

    // Adiciona eventos do display a fila de eventos
    al_register_event_source(game->event_queue, al_get_keyboard_event_source());
    // Adiciona eventos do teclado a fila de eventos
    al_register_event_source(game->event_queue, al_get_display_event_source(game->display));
    // Adiciona eventos do 6imer que atualiza a tela a fila de eventos
    al_register_event_source(game->event_queue, al_get_timer_event_source(game->screen_timer));

    game->draw = true;

    game->running = true;

    game->current_screen = MENU_SCREEN;

    // Inicializa o array das teclas como não pressionadas
    game->keys_pressed = (bool*) calloc(sizeof(bool) * 7, 7);
    if(game->keys_pressed == NULL) {
        fprintf(stderr, "Failed to allocate memory for keys array!\n");
        return false;
    }

    //carregamento do audio pra dentro do programa;
        //UI:
    (*game).Audio.changing_option = al_load_sample("audio/UI/changing_option.wav");
    if(!(*game).Audio.changing_option){
        fprintf(stderr, "Failed to load changing_option audio!");
        return false;
    }

    (*game).Audio.selecting_option = al_load_sample("audio/UI/selecting_option.ogg");
    if(!(*game).Audio.selecting_option){
        fprintf(stderr, "Failed to load selecting_option audio!");
        return false;
    }

    (*game).Audio.back_option = al_load_sample("audio/UI/back_option.wav");
    if(!(*game).Audio.back_option){
        fprintf(stderr, "Failed to load back_option audio!");
        return false;
    }

    (*game).Audio.victory_song = al_load_sample("audio/UI/victory_song.ogg");
    if(!(*game).Audio.victory_song){
        fprintf(stderr, "Failed to load victory_song audio!");
        return false;
    }

    (*game).Audio.defeat_song = al_load_sample("audio/UI/defeat_song.ogg");
    if(!(*game).Audio.defeat_song){
        fprintf(stderr, "Failed to load defeat_song audio!");
        return false;
    }

    (*game).Audio.esc_midgame = al_load_sample("audio/UI/esc_midgame.wav");
    if(!(*game).Audio.esc_midgame){
        fprintf(stderr, "Failed to load esc_midgame audio!");
        return false;
    }

    (*game).Audio.UI_background = al_load_audio_stream("audio/UI/UI_background.ogg", 4, 1024);
    if(!(*game).Audio.UI_background){
        fprintf(stderr, "Failed to load UI_background audio!");
        return false;
    }


        //in-game:
    (*game).Audio.player_shot = al_load_sample("audio/in_game/player_shot.ogg");
    if(!(*game).Audio.player_shot){
        fprintf(stderr, "Failed to load player_shot audio!");
        return false;
    }

    (*game).Audio.player_explosion = al_load_sample("audio/in_game/player_explosion.ogg");
    if(!(*game).Audio.player_explosion){
        fprintf(stderr, "Failed to load player_explosion audio!");
        return false;
    }

    (*game).Audio.barrier_collision = al_load_sample("audio/in_game/barrier_collision.wav");
    if(!(*game).Audio.barrier_collision){
        fprintf(stderr, "Failed to load barrier_collision audio!");
        return false;
    }

    (*game).Audio.barrier_explosion = al_load_sample("audio/in_game/barrier_explosion.wav");
    if(!(*game).Audio.barrier_explosion){
        fprintf(stderr, "Failed to load barrier_explosion  audio!");
        return false;
    }

    (*game).Audio.alien_shot = al_load_sample("audio/in_game/alien_shot.wav");
    if(!(*game).Audio.alien_shot){
        fprintf(stderr, "Failed to load alien_shot audio!");
        return false;
    }

    (*game).Audio.alien_explosion = al_load_sample("audio/in_game/alien_explosion.wav");
    if(!(*game).Audio.alien_explosion){
        fprintf(stderr, "Failed to load alien_explosion audio!");
        return false;
    }

    (*game).Audio.ingame_background = al_load_audio_stream("audio/in_game/ingame_background.ogg", 4, 1024);
    if(!(*game).Audio.ingame_background){
        fprintf(stderr, "Failed to load ingame_background audio!");
        return false;
    }

    //aloca 10 espaços na memoria para efeitos sonoros(poderemos, entao, tocar até 10 efeitos sonoros de uma vez):
    al_reserve_samples(10);

    //liga as duas audio streams(audios longos) ao mixer:
    al_attach_audio_stream_to_mixer((*game).Audio.UI_background, al_get_default_mixer());
    al_attach_audio_stream_to_mixer((*game).Audio.ingame_background, al_get_default_mixer());

    //define que o modo de reproduçao dos audios longos sera o de 'loop':
    al_set_audio_stream_playmode((*game).Audio.UI_background, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playmode((*game).Audio.ingame_background, ALLEGRO_PLAYMODE_LOOP);

    //define que o modo de reproduçao inicial dos audios longos é 'desligado':
    al_set_audio_stream_playing((*game).Audio.UI_background, false);
    al_set_audio_stream_playing((*game).Audio.ingame_background, false);

    return true;
}


// Libera os recursos alocados pelo programa
void free_game_state_resources(GameState *game) {
    free(game->keys_pressed);
    game->keys_pressed = NULL;
    al_destroy_timer(game->screen_timer);
    al_destroy_event_queue(game->event_queue);
    al_destroy_display(game->display);
    al_destroy_font(game->font_score);
    //audio resources:
    al_destroy_sample((*game).Audio.changing_option);
    al_destroy_sample((*game).Audio.selecting_option);
    al_destroy_sample((*game).Audio.back_option);
    al_destroy_sample((*game).Audio.victory_song);
    al_destroy_sample((*game).Audio.defeat_song);
    al_destroy_sample((*game).Audio.esc_midgame);
    al_destroy_audio_stream((*game).Audio.UI_background);
    al_destroy_sample((*game).Audio.player_shot);
    al_destroy_sample((*game).Audio.player_explosion);
    al_destroy_sample((*game).Audio.barrier_collision);
    al_destroy_sample((*game).Audio.barrier_explosion);
    al_destroy_sample((*game).Audio.alien_shot);
    al_destroy_sample((*game).Audio.alien_explosion);
    al_destroy_audio_stream((*game).Audio.ingame_background);

}
