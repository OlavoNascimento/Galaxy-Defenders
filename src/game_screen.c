#include "game_state.h"
#include "player_ship.h"
#include "events.h"
#include "menu_screen.h"
#include "main.h"


void detect_bullet_collision_player(PlayerShip *player) {
    for(int i=0; i<NUM_aBULLETS; i++) {
        if(aBullet[i].live) {
            if(aBullet[i].y + aBullet[i].height >= player->pos_y &&
               aBullet[i].y <= player->pos_y + player->sprite.height &&
               aBullet[i].x + aBullet[i].width >= player->pos_x &&
               aBullet[i].x <= player->pos_x + player->sprite.width) {
                player->lives--;
                aBullet[i].live = false;
                DEBUG_PRINT("Collision! Current lifes: %d...\n", player->lives);
            }
        }
    }

}

// Controla o movimento do jogador
void process_player_movement(GameState *game, PlayerShip *player) {
    if(game->keys_pressed[UP]) {
        // Impede que a nave ultrapasse as barreiras
        if(player->pos_y - PLAYER_SPEED > SCREEN_HEIGHT/1.3) {
            player->pos_y -= PLAYER_SPEED;
            game->draw = true;
        }
    }
    if(game->keys_pressed[DOWN]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_y + PLAYER_SPEED <= SCREEN_HEIGHT - player->sprite.height) {
            player->pos_y += PLAYER_SPEED;
            game->draw = true;
        }
    }
    if(game->keys_pressed[LEFT]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_x - PLAYER_SPEED >= 0) {
            player->pos_x -= PLAYER_SPEED;
            game->draw = true;
        }
    }
    if(game->keys_pressed[RIGHT]) {
        // Impede que a nave do jogador saia da tela
        if(player->pos_x + PLAYER_SPEED < SCREEN_WIDTH - player->sprite.width)  {
            player->pos_x += PLAYER_SPEED;
            game->draw = true;
        }
    }

    if(player->lasers.alive > 0)  {
        // Atualiza a posição dos lasers do jogador
        // removendo-os caso necessário
        for(int i=0; i<player->lasers.alive; i++) 
            player->lasers.fired[i].pos_y -= PLAYER_LASER_SPEED;

        // Remove o primeiro disparo do array caso ele tenha saido da tela
        if(player->lasers.fired[0].pos_y < 0)
            remove_player_laser_fired(player, 0);

        game->draw = true;
    }
}

// Controla os disparos do jogador
void process_player_firing(GameState *game, PlayerShip *player) {
    bool fire = false;
    if(player->lasers.alive > 0 && player->lasers.alive < PLAYER_MAX_LASER_COUNT) {
        int last_laser = player->lasers.alive - 1;
        int dist_laser = player->pos_y - player->lasers.fired[last_laser].pos_y;
        if(dist_laser > SCREEN_HEIGHT / PLAYER_FIRING_SPEED) {
            fire = true;
        }
    } else if(player->lasers.alive == 0) {
        fire = true;
    }
    // Caso espaço esteja pressionado e o ultimo disparo do jogador 
    // tenha uma distância mínima, adiciona um novo disparo  
    if(game->keys_pressed[SPACE] && fire) {
        add_player_laser_fired(player);
        game->draw = true;
    } 
}

// Atualiza a tela do jogo
void update_game_screen(PlayerShip *player) {
    // DEBUG_PRINT("Updating game screen!\n");
    al_clear_to_color(al_map_rgb(0, 0, 0));

    draw_player_ship(player);
    draw_player_lasers(player);

    drawBarrier();
    draw_explosion_barrier();


    draw_alien1(alien1img, alien1, NUM_ALIEN);
    draw_alien2(alien2img, alien2, 2);
    draw_alien3(alien3img, alien3, 2);

    draw_explosion_alien1();
    draw_explosion_alien2();
    draw_explosion_alien3();

    draw_aBullet();

    al_flip_display();
}


// Modifica a posição dos sprites na tela
void process_game_events(GameState *game, PlayerShip *player) {
    ALLEGRO_EVENT event;
    al_wait_for_event(game->event_queue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER) {
        process_player_movement(game, player);
        process_player_firing(game, player);

        detect_bullet_collision_player(player);
        //colisao dos aliens com balas{

            //verificando se houve a colisao entre as balas e os inimigos. Se sim, apaga o inimigo e a bala.
            detectBulletCollision_alien1(alien1, NUM_ALIEN, player);

            detectBulletCollision_alien2(alien2, 2, player);

            detectBulletCollision_alien3(alien3, 2, player);

            //colisionPlayer();

            update_explosion_alien1();

            update_explosion_alien2();

            update_explosion_alien3();

        //}

        //colisoes da barreira

            colisionAlien();

            colisionPlayer(player);


            lifeBarrier();

            update_explosion_barrier();


        //Movimento dos aliens{

            //limitando o movimento horizontal dos aliens e movimentando-os verticalmente:
            limitXmoveY_alien1(alien1, NUM_ALIEN);

            limitXmoveY_alien2(alien2, 2);

            limitXmoveY_alien3(alien3, 2);


            //movimentando os aliens horizontalmente:
            moveX_alien1(alien1, NUM_ALIEN);

            moveX_alien2(alien2, 2);

            moveX_alien3(alien3, 2);


            //atualizando os sprites dos inimigos constantemente:
            updateSprite_alien1(alien1, NUM_ALIEN);

            updateSprite_alien2(alien2, 2);

            updateSprite_alien3(alien3, 2);
        //}


        //Disparo dos aliens{

            //delay para impedir que os aliens disparem muito rapido(a cada estouro do timer):
            if(++alien_shot_delay >= 50){

                choose_shooter_alien();

                fire_aBullet();

                alien_shot_delay = 0;
            }

            update_aBullet();

        //}
        game->draw = true;
    } else {
        process_events(game, &event);
        if(game->keys_pressed[ESC]) {
            player->lives = 0;
            game->current_screen = MENU_SCREEN;
        }
    }

    if(game->draw && al_is_event_queue_empty(game->event_queue)) {
        game->draw = false;
        update_game_screen(player);
    }
}