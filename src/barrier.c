#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#include "enemies.h"
#include "barrier.h"
#include "player_ship.h"

//Inicializando dados das barreiras
void InitBarrier(main_barrier *Pbarr)
{
    for(int i = 0; i<NUM_BARRIERS; ++i){
        Pbarr->main_bar[i].life_up = 15;
        Pbarr->main_bar[i].life_down = 15;
        Pbarr->main_bar[i].live = true;
        Pbarr->main_bar[i].x = 170 + i * 265;
        Pbarr->main_bar[i].y = HEIGHT_BARRIER;
        Pbarr->main_bar[i].framewidth = 115;
        Pbarr->main_bar[i].frameheight = 71;
        Pbarr->main_bar[i].exp_bar.totalframes = 6;
        Pbarr->main_bar[i].exp_bar.currentframe = 0;
        Pbarr->main_bar[i].exp_bar.framedelay = 7;
        Pbarr->main_bar[i].exp_bar.framecounter = 0;
        Pbarr->main_bar[i].exp_bar.framewidth = 175;
        Pbarr->main_bar[i].exp_bar.frameheight = 116;
        Pbarr->main_bar[i].exp_bar.x = Pbarr->main_bar[i].x - 37;
        Pbarr->main_bar[i].exp_bar.y = HEIGHT_BARRIER - 20;
        Pbarr->main_bar[i].exp_bar.start_exp = false;

        //Funcao de carregamento de imagens
        init_barrier_resources(Pbarr);
    }
}

//Saude de barreira
void lifeBarrier(main_barrier *Pbarr)
{
    for(int i = 0; i <NUM_BARRIERS; ++i)
    {
        if(Pbarr->main_bar[i].live){
            if(Pbarr->main_bar[i].life_up < 1 || Pbarr->main_bar[i].life_down < 1)
            {
                Pbarr->main_bar[i].live = false;
                Pbarr->main_bar[i].exp_bar.start_exp = true;
            }
        }

    }
}

//Alteracao de sprites da explosao 
void update_explosion_barrier(main_barrier *Pbarr)
{

    for(int i = 0; i< NUM_BARRIERS; ++i){
        if(Pbarr->main_bar[i].exp_bar.start_exp){
            if(++Pbarr->main_bar[i].exp_bar.framecounter >= Pbarr->main_bar[i].exp_bar.framedelay){
                if(++Pbarr->main_bar[i].exp_bar.currentframe >= Pbarr->main_bar[i].exp_bar.totalframes){
                    Pbarr->main_bar[i].exp_bar.start_exp = false;
                }

                Pbarr->main_bar[i].exp_bar.framecounter = 0;
            }
        }
    }
}

//Desenha as barreiras na tela
void draw_explosion_barrier(main_barrier *Pbarr)
{
    for(int i=0; i< NUM_BARRIERS; ++i){
        if(Pbarr->main_bar[i].exp_bar.start_exp){
            al_draw_bitmap_region(Pbarr->img_exp_bar, Pbarr->main_bar[i].exp_bar.currentframe * Pbarr->main_bar[i].exp_bar.framewidth, 0, Pbarr->main_bar[i].exp_bar.framewidth, Pbarr->main_bar[i].exp_bar.frameheight, Pbarr->main_bar[i].exp_bar.x, Pbarr->main_bar[i].exp_bar.y, 0);
             al_convert_mask_to_alpha(Pbarr->img_exp_bar, al_map_rgb(255,255,255));
        }
    }
}

//Redesenha a barreira de outra forma quando necessario
void drawBarrier(main_barrier *Pbarr)
{
    for(int i=0; i<NUM_BARRIERS; ++i){

        if(Pbarr->main_bar[i].live){
            if(Pbarr->main_bar[i].life_up >= 8 && Pbarr->main_bar[i].life_down >=8){
                    al_draw_scaled_bitmap(Pbarr->img_bar[0],
                                          0, 0,
                                          Pbarr->main_bar[i].framewidth, Pbarr->main_bar[i].frameheight,
                                          Pbarr->main_bar[i].x, Pbarr->main_bar[i].y,
                                          115,71,
                                          0);
                    al_convert_mask_to_alpha(Pbarr->img_bar[0], al_map_rgb(0,0,0));
            }
            else if(Pbarr->main_bar[i].life_up >= 8 && Pbarr->main_bar[i].life_down < 8){
                    al_draw_scaled_bitmap(Pbarr->img_bar[1],
                                          0, 0,
                                          Pbarr->main_bar[i].framewidth, Pbarr->main_bar[i].frameheight,
                                          Pbarr->main_bar[i].x, Pbarr->main_bar[i].y,
                                          115, 71,
                                          0);
                al_convert_mask_to_alpha(Pbarr->img_bar[1], al_map_rgb(0,0,0));
            }
            else if(Pbarr->main_bar[i].life_up <=8 && Pbarr->main_bar[i].life_down >=8){
                    al_draw_scaled_bitmap(Pbarr->img_bar[2],
                                          0, 0,
                                          Pbarr->main_bar[i].framewidth, Pbarr->main_bar[i].frameheight,
                                          Pbarr->main_bar[i].x, Pbarr->main_bar[i].y,
                                          115, 71,
                                          0);
                al_convert_mask_to_alpha(Pbarr->img_bar[2], al_map_rgb(0,0,0));
            }
            else if(Pbarr->main_bar[i].life_up < 8 && Pbarr->main_bar[i].life_down <8){
                    al_draw_scaled_bitmap(Pbarr->img_bar[3],
                                          0, 0,
                                          Pbarr->main_bar[i].framewidth, Pbarr->main_bar[i].frameheight,
                                          Pbarr->main_bar[i].x, Pbarr->main_bar[i].y,
                                          115, 71,
                                          0);
                al_convert_mask_to_alpha(Pbarr->img_bar[3], al_map_rgb(0,0,0));
            }
        }
    }
}

//Detecta colisao entre o tiro do Alien e a barreira
void colision_Alien_shot_barrier(main_barrier *Pbarr, enemies *p_enemies)
{
    for(int i=0; i<NUM_BARRIERS; ++i){
        if(Pbarr->main_bar[i].live)
        {
           for(int j=0; j< NUM_aBULLETS ; ++j)
           {
               if(p_enemies->alienShots.aBullet[j].live){
                    if(p_enemies->alienShots.aBullet[j].x <= Pbarr->main_bar[i].x + Pbarr->main_bar[i].framewidth &&
                       p_enemies->alienShots.aBullet[j].x + p_enemies->alienShots.aBullet[j].width >= Pbarr->main_bar[i].x + 5 &&
                       p_enemies->alienShots.aBullet[j].y <= Pbarr->main_bar[i].y + Pbarr->main_bar[i].frameheight -46 &&
                       p_enemies->alienShots.aBullet[j].y + p_enemies->alienShots.aBullet[j].height >= Pbarr->main_bar[i].y + 16)
                       {
                            Pbarr->main_bar[i].life_up--;
                            p_enemies->alienShots.aBullet[j].live = false;
                       }
               }
           }
        }
    }
}

//Detecta colisao entre o tiro do player e a barreira
void colision_Player_shot_barrier(PlayerShip *player, main_barrier *Pbarr)
{
    for(int i=0; i <NUM_BARRIERS; ++i){
        if(Pbarr->main_bar[i].live)
        {
           for(int j=0; j<player->lasers.alive; ++j)
           {
                if(player->lasers.fired[j].pos_x <= Pbarr->main_bar[i].x + Pbarr->main_bar[i].framewidth - 1 &&
                    player->lasers.fired[j].pos_x + player->lasers.sprite.width >= Pbarr->main_bar[i].x  &&
                    player->lasers.fired[j].pos_y <= Pbarr->main_bar[i].y + 10 &&
                    player->lasers.fired[j].pos_y + player->lasers.sprite.height >= Pbarr->main_bar[i].y)
                    {
                        Pbarr->main_bar[i].life_down--;
                        remove_player_laser_fired(player, j);
                    }
           }
        }
    }
}

//Carrega as imagens que vao ser usadas na barreira 
bool init_barrier_resources(main_barrier *Pbarr){
    //imagem das barreiras:
    Pbarr->img_bar[0] = al_load_bitmap("assets/images/barrier00.png");
    Pbarr->img_bar[1] = al_load_bitmap("assets/images/barrierdown.png");
    Pbarr->img_bar[2] = al_load_bitmap("assets/images/barrierup.png");
    Pbarr->img_bar[3] = al_load_bitmap("assets/images/barrier01.png");

    //Mensagem de erro caso não consiga carregar as imagens da barreira
    for(int i=0; i<NUM_BARRIERS; i++)
    {
        if(!Pbarr->img_bar[i]){
            fprintf(stderr, "Error: could not load barrier image.\n");
        }
    }

    //Mensagem de erro caso não consiga carregar o sprite de explosao
    Pbarr->img_exp_bar = al_load_bitmap("assets/images/img_exp_bar.jpg");
    if(!Pbarr->img_exp_bar){
        fprintf(stderr, "Error: could not load explosion barrier image.\n");
        return 1;
    }
    al_convert_mask_to_alpha(Pbarr->img_exp_bar, al_map_rgb(255,255,255));

    return true;
}

//Libera os recursos usado pela barreira 
void free_barrier_resources(main_barrier *Pbarr){
    //liberando os recursos usados no programa:
    al_destroy_bitmap(Pbarr->img_exp_bar);

    for(int i=0; i<NUM_BARRIERS; i++){
            al_destroy_bitmap(Pbarr->img_bar[i]);
    }
}
