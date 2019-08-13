#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#include "main.h"

//INICIALIZANDO BARREIRA
void InitBarrier(void)
{
    for(int i = 0; i<NUM_BARRIERS; ++i){
        bar[i].life_up = 15;
        bar[i].life_down = 15;
        bar[i].live = true;
        bar[i].x = 175 + i * 250;
        bar[i].y = 550;
        bar[i].framewidth = 115;
        bar[i].frameheight = 71;

        bar[i].exp_bar.totalframes = 6;
        bar[i].exp_bar.currentframe = 0;
        bar[i].exp_bar.framedelay = 15;
        bar[i].exp_bar.framecounter = 0;
        bar[i].exp_bar.start_exp = false;
    }
}

//SAUDE DA BARRERIA
void lifeBarrier(void)
{
    for(int i = 0; i <NUM_BARRIERS; ++i)
    {
        if(bar[i].live){
            if(bar[i].life_up < 1 && bar[i].life_down < 1)
            {
                bar[i].live = false;
                bar[i].exp_bar.start_exp = true;
            }
        }

    }
}

//EXPLODINDO BARREIRA
void update_explosion_barrier(void)
{

    for(int i = 0; i< NUM_BARRIERS; ++i){
        if(bar[i].exp_bar.start_exp){
            if(++bar[i].exp_bar.framecounter >= bar[i].exp_bar.framedelay){
                if(++bar[i].exp_bar.currentframe >= bar[i].exp_bar.totalframes){
                    bar[i].exp_bar.start_exp = false;
                }

                bar[i].exp_bar.framecounter = 0;
            }
        }
    }
}

void draw_explosion_barrier(void)
{
    for(int i=0; i< NUM_BARRIERS; ++i){
        if(bar[i].exp_bar.start_exp){
            al_draw_bitmap_region(img_exp_bar, bar[i].exp_bar.currentframe * bar[i].framewidth, 0, bar[i].framewidth, bar[i].frameheight, bar[i].x, bar[i].y, 0);
             al_convert_mask_to_alpha(img_exp_bar, al_map_rgb(255,255,255));
        }
    }
}

//REDESENHANDO A BARREIRA
void drawBarrier(void)
{
    for(int i=0; i<NUM_BARRIERS; ++i){

        if(bar[i].live){
            if(bar[i].life_up >= 8 && bar[i].life_down >=8){
                    al_draw_bitmap(img_bar[0], bar[i].x, bar[i].y, 0);
                    al_convert_mask_to_alpha(img_bar[0], al_map_rgb(0,0,0));
            }
            else if(bar[i].life_up >= 8 && bar[i].life_down < 8){
                al_draw_bitmap(img_bar[1], bar[i].x, bar[i].y, 0);
                al_convert_mask_to_alpha(img_bar[1], al_map_rgb(0,0,0));
            }
            else if(bar[i].life_up <=8 && bar[i].life_down >=8){
                al_draw_bitmap(img_bar[2], bar[i].x, bar[i].y, 0);
                al_convert_mask_to_alpha(img_bar[2], al_map_rgb(0,0,0));
            }
            else if(bar[i].life_up < 8 && bar[i].life_down <8){
                al_draw_bitmap(img_bar[3], bar[i].x, bar[i].y, 0);
                al_convert_mask_to_alpha(img_bar[3], al_map_rgb(0,0,0));
            }
        }
    }
}

//COLISAO COM O TIRO DO ALIEN
void colisionAlien(void)
{
    for(int i=0; i<NUM_BARRIERS; ++i){
        if(bar[i].live)
        {
           for(int j=0; j< NUM_aBULLETS ; ++j)
           {
               if(aBullet[j].live){
                    if(aBullet[j].x <= bar[i].x + bar[i].framewidth -5 &&
                       aBullet[j].x + aBullet[j].width >= bar[i].x + 5 &&
                       aBullet[j].y <= bar[i].y + bar[i].frameheight -55 &&
                       aBullet[j].y + aBullet[j].height >= bar[i].y + 16)
                       {
                            bar[i].life_up--;
                            aBullet[j].live = false;
                       }
               }
           }
        }
    }
}

//COLISAO COM O TIRO DO PLAYER
void colisionPlayer(void)
{
    for(int i=0; i <NUM_BARRIERS; ++i){
        if(bar[i].live)
        {
           for(int j=0; j<NUM_BULLETS; ++j)
           {
               if(bullets[j].live){
                    if(bullets[j].x <= bar[i].x + bar[i].framewidth -5 &&
                       bullets[j].x + bullets[j].width >= bar[i].x + 5 &&
                       bullets[j].y <= bar[i].y + bar[i].frameheight - 60 &&
                       bullets[j].y + bullets[j].height >= bar[i].y)
                       {
                            bar[i].life_down--;
                            bullets[j].live = false;
                       }
               }
           }
        }
    }
}
