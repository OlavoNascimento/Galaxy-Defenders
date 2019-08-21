#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "enemies.h"

void InitAlien1(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i){

        (*p_enemies).alien1[i].x = 256 + i*75;
        (*p_enemies).alien1[i].y = 0;
        (*p_enemies).alien1[i].velx = 2;
        (*p_enemies).alien1[i].vely = 15;
        (*p_enemies).alien1[i].live = true;
        (*p_enemies).alien1[i].sprite.totalframes = 2;
        (*p_enemies).alien1[i].sprite.currentframe = 0;
        (*p_enemies).alien1[i].sprite.framedelay = 50;
        (*p_enemies).alien1[i].sprite.framecounter = 0;
        (*p_enemies).alien1[i].sprite.width = 65;
        (*p_enemies).alien1[i].sprite.height = 52;

        (*p_enemies).alien1[i].exp.totalframes = 7;
        (*p_enemies).alien1[i].exp.currentframe = 0;
        (*p_enemies).alien1[i].exp.framedelay = 5;
        (*p_enemies).alien1[i].exp.framecounter = 0;
        (*p_enemies).alien1[i].exp.framewidth = 65;
        (*p_enemies).alien1[i].exp.start = false;

    }

}

void InitAlien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){

            (*p_enemies).alien2[i][j].x = 256 + j*75;
            (*p_enemies).alien2[i][j].y = (i+1)*62;
            (*p_enemies).alien2[i][j].velx = 2;
            (*p_enemies).alien2[i][j].vely = 7.5;
            (*p_enemies).alien2[i][j].live = true;
            (*p_enemies).alien2[i][j].sprite.totalframes = 2;
            (*p_enemies).alien2[i][j].sprite.currentframe = 0;
            (*p_enemies).alien2[i][j].sprite.framedelay = 50;
            (*p_enemies).alien2[i][j].sprite.framecounter = 0;
            (*p_enemies).alien2[i][j].sprite.width = 65;
            (*p_enemies).alien2[i][j].sprite.height = 52;

            (*p_enemies).alien2[i][j].exp.totalframes = 7;
            (*p_enemies).alien2[i][j].exp.currentframe = 0;
            (*p_enemies).alien2[i][j].exp.framedelay = 5;
            (*p_enemies).alien2[i][j].exp.framecounter = 0;
            (*p_enemies).alien2[i][j].exp.framewidth = 65;
            (*p_enemies).alien2[i][j].exp.start = false;

        }
    }

}


void InitAlien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){

            (*p_enemies).alien3[i][j].x = 256 + j*75;
            (*p_enemies).alien3[i][j].y = (i+3)*62;
            (*p_enemies).alien3[i][j].velx = 2;
            (*p_enemies).alien3[i][j].vely = 7.5;
            (*p_enemies).alien3[i][j].live = true;
            (*p_enemies).alien3[i][j].sprite.totalframes = 2;
            (*p_enemies).alien3[i][j].sprite.currentframe = 0;
            (*p_enemies).alien3[i][j].sprite.framedelay = 50;
            (*p_enemies).alien3[i][j].sprite.framecounter = 0;
            (*p_enemies).alien3[i][j].sprite.width = 65;
            (*p_enemies).alien3[i][j].sprite.height = 52;

            (*p_enemies).alien3[i][j].exp.totalframes = 7;
            (*p_enemies).alien3[i][j].exp.currentframe = 0;
            (*p_enemies).alien3[i][j].exp.framedelay = 5;
            (*p_enemies).alien3[i][j].exp.framecounter = 0;
            (*p_enemies).alien3[i][j].exp.framewidth = 65;
            (*p_enemies).alien3[i][j].exp.start = false;

        }
    }

}





void limitXmoveY_alien1(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[9].x + (*p_enemies).alien1[9].sprite.width >= 1200){
            (*p_enemies).alien1[i].velx = -2;
            if((*p_enemies).alien1[9].y + (*p_enemies).alien1[9].sprite.height <= 245)
                (*p_enemies).alien1[i].y += (*p_enemies).alien1[i].vely;
        }

        if((*p_enemies).alien1[0].x <= 80){
            (*p_enemies).alien1[i].velx = 2;
            if((*p_enemies).alien1[0].y + (*p_enemies).alien1[i].sprite.height <= 245)
                (*p_enemies).alien1[i].y += (*p_enemies).alien1[i].vely;
        }
    }

}

void limitXmoveY_alien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien2[i][9].x + (*p_enemies).alien2[1][j].sprite.width >= 1200){
                (*p_enemies).alien2[i][j].velx = -2;
                if((*p_enemies).alien2[1][j].y + (*p_enemies).alien2[1][j].sprite.height <= 369)
                    (*p_enemies).alien2[1][j].y += (*p_enemies).alien2[i][j].vely;
                if((*p_enemies).alien2[0][j].y + (*p_enemies).alien2[0][j].sprite.height <= 307)
                    (*p_enemies).alien2[0][j].y += (*p_enemies).alien2[i][j].vely;
            }

            if((*p_enemies).alien2[i][0].x <= 80){
                (*p_enemies).alien2[i][j].velx = 2;
                if((*p_enemies).alien2[1][j].y + (*p_enemies).alien2[1][j].sprite.height <= 369)
                    (*p_enemies).alien2[1][j].y += (*p_enemies).alien2[i][j].vely;
                if((*p_enemies).alien2[0][j].y + (*p_enemies).alien2[0][j].sprite.height <= 307)
                    (*p_enemies).alien2[0][j].y += (*p_enemies).alien2[i][j].vely;
            }
        }
    }

}


void limitXmoveY_alien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien3[i][9].x + (*p_enemies).alien3[i][9].sprite.width >= 1200){
                (*p_enemies).alien3[i][j].velx = -2;
                if((*p_enemies).alien3[1][j].y + (*p_enemies).alien3[1][j].sprite.height <= 493)
                    (*p_enemies).alien3[1][j].y += (*p_enemies).alien3[i][j].vely;
                if((*p_enemies).alien3[0][j].y + (*p_enemies).alien3[0][j].sprite.height<= 431)
                    (*p_enemies).alien3[0][j].y += (*p_enemies).alien3[i][j].vely;
            }

            if((*p_enemies).alien3[i][0].x <=80){
                (*p_enemies).alien3[i][j].velx = 2;
                if((*p_enemies).alien3[1][j].y + (*p_enemies).alien3[1][j].sprite.height <= 493)
                    (*p_enemies).alien3[1][j].y += (*p_enemies).alien3[i][j].vely;
                if((*p_enemies).alien3[0][j].y + (*p_enemies).alien3[0][j].sprite.height<= 431)
                    (*p_enemies).alien3[0][j].y += (*p_enemies).alien3[i][j].vely;
            }
        }
    }

}


void moveX_alien1(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i)
        (*p_enemies).alien1[i].x += (*p_enemies).alien1[i].velx;

}


void moveX_alien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i)
        for(int j = 0; j<NUM_ALIEN; ++j)
            (*p_enemies).alien2[i][j].x += (*p_enemies).alien2[i][j].velx;

}


void moveX_alien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i)
        for(int j = 0; j<NUM_ALIEN; ++j)
            (*p_enemies).alien3[i][j].x += (*p_enemies).alien3[i][j].velx;

}


void updateSprite_alien1(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[i].live){
            if(++(*p_enemies).alien1[i].sprite.framecounter >= (*p_enemies).alien1[i].sprite.framedelay){
                if(++(*p_enemies).alien1[i].sprite.currentframe >= (*p_enemies).alien1[i].sprite.totalframes){
                    (*p_enemies).alien1[i].sprite.currentframe = 0;
                }
                (*p_enemies).alien1[i].sprite.framecounter = 0;
            }
        }
    }

}

void updateSprite_alien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien2[i][j].live){
                if(++(*p_enemies).alien2[i][j].sprite.framecounter >= (*p_enemies).alien2[i][j].sprite.framedelay){
                    if(++(*p_enemies).alien2[i][j].sprite.currentframe >= (*p_enemies).alien2[i][j].sprite.totalframes){
                        (*p_enemies).alien2[i][j].sprite.currentframe = 0;
                    }
                    (*p_enemies).alien2[i][j].sprite.framecounter = 0;
                }
            }
        }
    }

}

void updateSprite_alien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien3[i][j].live){
                if(++(*p_enemies).alien3[i][j].sprite.framecounter >= (*p_enemies).alien3[i][j].sprite.framedelay){
                    if(++(*p_enemies).alien3[i][j].sprite.currentframe >= (*p_enemies).alien3[i][j].sprite.totalframes){
                        (*p_enemies).alien3[i][j].sprite.currentframe = 0;
                    }
                    (*p_enemies).alien3[i][j].sprite.framecounter = 0;
                }
            }
        }
    }

}


void draw_alien1(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[i].live)
            al_draw_bitmap_region((*p_enemies).alien1img,
                                  (*p_enemies).alien1[i].sprite.currentframe*(*p_enemies).alien1[i].sprite.width,
                                  0,
                                  (*p_enemies).alien1[i].sprite.width,
                                  (*p_enemies).alien1[i].sprite.height,
                                  (*p_enemies).alien1[i].x,
                                  (*p_enemies).alien1[i].y,
                                   0);
    }

}

void draw_alien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien2[i][j].live)
                al_draw_bitmap_region((*p_enemies).alien2img,
                                      (*p_enemies).alien2[i][j].sprite.currentframe*(*p_enemies).alien2[i][j].sprite.width,
                                      0,
                                      (*p_enemies).alien2[i][j].sprite.width,
                                      (*p_enemies).alien2[i][j].sprite.height,
                                      (*p_enemies).alien2[i][j].x,
                                      (*p_enemies).alien2[i][j].y,
                                       0);
        }
    }

}

void draw_alien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien3[i][j].live)
                al_draw_bitmap_region((*p_enemies).alien3img,
                                      (*p_enemies).alien3[i][j].sprite.currentframe*(*p_enemies).alien3[i][j].sprite.width,
                                       0,
                                       (*p_enemies).alien3[i][j].sprite.width,
                                       (*p_enemies).alien3[i][j].sprite.height,
                                       (*p_enemies).alien3[i][j].x,
                                       (*p_enemies).alien3[i][j].y, 0);
        }
    }

}

void detectBulletCollision_alien1(enemies *p_enemies, PlayerShip *player){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[i].live){
            for(int j = 0; j<player->lasers.alive; ++j){
                if(player->lasers.fired[j].pos_x <= (*p_enemies).alien1[i].x + (*p_enemies).alien1[i].sprite.width - 2 &&
                   player->lasers.fired[j].pos_x + player->lasers.sprite.width >= (*p_enemies).alien1[i].x + 2 &&
                   player->lasers.fired[j].pos_y <= (*p_enemies).alien1[i].y + (*p_enemies).alien1[i].sprite.height - 2 &&
                   player->lasers.fired[j].pos_y + player->lasers.sprite.height >= (*p_enemies).alien1[i].y + 2){
                    remove_player_laser_fired(player, j);
                    (*p_enemies).alien1[i].live = false;
                    (*p_enemies).alien1[i].exp.start = true;
                }
            }
        }

    }
}


void detectBulletCollision_alien2(enemies *p_enemies, PlayerShip *player){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien2[i][j].live){
                for(int k = 0; k<player->lasers.alive; ++k){
                    if(player->lasers.fired[k].pos_x <= (*p_enemies).alien2[i][j].x + (*p_enemies).alien2[i][j].sprite.width - 2 &&
                       player->lasers.fired[k].pos_x + player->lasers.sprite.width >= (*p_enemies).alien2[i][j].x + 2 &&
                       player->lasers.fired[k].pos_y <= (*p_enemies).alien2[i][j].y + (*p_enemies).alien2[i][j].sprite.height - 2 &&
                       player->lasers.fired[k].pos_y + player->lasers.sprite.height >= (*p_enemies).alien2[i][j].y + 2){
                        remove_player_laser_fired(player, j);
                        (*p_enemies).alien2[i][j].live = false;
                        (*p_enemies).alien2[i][j].exp.start = true;
                    }
                }
            }
        }
    }
}

void detectBulletCollision_alien3(enemies *p_enemies, PlayerShip *player){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien3[i][j].live){
                for(int k = 0; k<player->lasers.alive; ++k){
                    if(player->lasers.fired[k].pos_x <= (*p_enemies).alien3[i][j].x + (*p_enemies).alien3[i][j].sprite.width - 2 &&
                       player->lasers.fired[k].pos_x + player->lasers.sprite.width >= (*p_enemies).alien3[i][j].x + 2 &&
                       player->lasers.fired[k].pos_y <= (*p_enemies).alien3[i][j].y + (*p_enemies).alien3[i][j].sprite.height - 2 &&
                       player->lasers.fired[k].pos_y + player->lasers.sprite.height >= (*p_enemies).alien3[i][j].y + 2){
                        remove_player_laser_fired(player, k);
                        (*p_enemies).alien3[i][j].live = false;
                        (*p_enemies).alien3[i][j].exp.start = true;
                    }
                }
            }
        }
    }
}


//escolhe um alien aleatorio para disparar(apenas os aliens que sao os ultimos de sua coluna podem ser candidatos a disparar):
void choose_shooter_alien(enemies *p_enemies){
    //devemos limpar as variaves antes de come�ar para evitar lixo:
    for(int i = 0; i<NUM_ALIEN; ++i){
        (*p_enemies).alienShots.check_array[i] = false;
        (*p_enemies).alienShots.alien_shooter[i] = NULL;
    }

    for(int i = 1; i>-1; --i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien3[i][j].live && !(*p_enemies).alienShots.check_array[j]){
                (*p_enemies).alienShots.check_array[j] = true;
                (*p_enemies).alienShots.alien_shooter[j] = &(*p_enemies).alien3[i][j]; //error
            }

        }
    }

    for(int i = 1; i>-1; --i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien2[i][j].live && !(*p_enemies).alienShots.check_array[j]){
                (*p_enemies).alienShots.check_array[j] = true;
                (*p_enemies).alienShots.alien_shooter[j] = &(*p_enemies).alien2[i][j]; //error
            }
        }
    }

    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[i].live && !(*p_enemies).alienShots.check_array[i]){
            (*p_enemies).alienShots.check_array[i] = true;
            (*p_enemies).alienShots.alien_shooter[i] = &(*p_enemies).alien1[i]; //error
        }
    }

    (*p_enemies).alienShots.all_aliens_Rdead = 0;

    for(int i = 0; i<NUM_ALIEN; ++i){
        if(!(*p_enemies).alienShots.check_array[i]){
            ++(*p_enemies).alienShots.all_aliens_Rdead;
        }
    }

    srand(time(NULL));

    (*p_enemies).alienShots.k = rand () % 9;

    if(!(*p_enemies).alienShots.check_array[(*p_enemies).alienShots.k]){
        for(int i = 1; i>-1; --i){
            for(int j = 0; j<NUM_ALIEN; ++j){
                if((*p_enemies).alien3[i][j].live){
                    (*p_enemies).alienShots.alien_shooter[(*p_enemies).alienShots.k] = &(*p_enemies).alien3[i][j];
                    break;
                }else if((*p_enemies).alien2[i][j].live){
                    (*p_enemies).alienShots.alien_shooter[(*p_enemies).alienShots.k] = &(*p_enemies).alien2[i][j];
                    break;
                }else if((*p_enemies).alien1[j].live){
                   (*p_enemies).alienShots.alien_shooter[(*p_enemies).alienShots.k] = &(*p_enemies).alien1[j];
                   break;
                }
            }
        }

    }


}



void Init_aBullet(enemies *p_enemies){
    for(int i = 0; i<NUM_aBULLETS; ++i){

        (*p_enemies).alienShots.aBullet[i].live = false;
        (*p_enemies).alienShots.aBullet[i].speed = 5;
        (*p_enemies).alienShots.aBullet[i].width = 18;
        (*p_enemies).alienShots.aBullet[i].height = 23;

    }

}



void fire_aBullet (enemies *p_enemies){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if((*p_enemies).alienShots.all_aliens_Rdead < 10){
            if(!(*p_enemies).alienShots.aBullet[i].live){
                (*p_enemies).alienShots.aBullet[i].x = (*p_enemies).alienShots.alien_shooter[(*p_enemies).alienShots.k]->x + 32;  /////doubt
                (*p_enemies).alienShots.aBullet[i].y = (*p_enemies).alienShots.alien_shooter[(*p_enemies).alienShots.k]->y + 57;
                (*p_enemies).alienShots.aBullet[i].live = true;
                break;
            }
        }
    }

}


void update_aBullet(enemies *p_enemies){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if((*p_enemies).alienShots.aBullet[i].live){
            (*p_enemies).alienShots.aBullet[i].y += (*p_enemies).alienShots.aBullet[i].speed;
            if((*p_enemies).alienShots.aBullet[i].y > 720){
                (*p_enemies).alienShots.aBullet[i].live = false;
            }
        }
    }

}




void draw_aBullet (enemies *p_enemies){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if((*p_enemies).alienShots.aBullet[i].live){
            al_draw_bitmap((*p_enemies).alien_bullet_img, (*p_enemies).alienShots.aBullet[i].x , (*p_enemies).alienShots.aBullet[i].y , 0);
        }
    }

}


bool InitEnemies(enemies *p_enemies){


    InitAlien1(p_enemies);

    InitAlien2(p_enemies);

    InitAlien3(p_enemies);

    Init_aBullet(p_enemies);



    (*p_enemies).alien1img = al_load_bitmap("assets/images/alien1.png");
    if(!(*p_enemies).alien1img){
        fprintf(stderr, "Error: could not load alien1 image.\n");
        return false;
    }
    al_convert_mask_to_alpha((*p_enemies).alien1img, al_map_rgb(0, 0 ,0));



    (*p_enemies).alien2img = al_load_bitmap("assets/images/alien2.png");
    if(!(*p_enemies).alien2img){
        fprintf(stderr, "Error: could not load alien2 image.\n");
        //limpar o q ja foi criado
        return false;
    }
    al_convert_mask_to_alpha((*p_enemies).alien2img, al_map_rgb(0, 0 ,0));



    (*p_enemies).alien3img = al_load_bitmap("assets/images/alien3.png");
    if(!(*p_enemies).alien3img){
        fprintf(stderr, "Error: could not load alien3 bitmap");
        //limpar oq ja foi usado.
        return false;
    }
    al_convert_mask_to_alpha((*p_enemies).alien3img, al_map_rgb(0, 0 ,0));



    (*p_enemies).exp_img = al_load_bitmap("assets/images/exp.png");
    if(!(*p_enemies).exp_img){
        fprintf(stderr, "Error: could not load explosion bitmap");
        //liberar recursos;
        return false;
    }
    al_convert_mask_to_alpha((*p_enemies).exp_img, al_map_rgb(0, 0 , 0));



    (*p_enemies).alien_bullet_img = al_load_bitmap("assets/images/alienshot.png");
    if(!(*p_enemies).alien_bullet_img){
        fprintf(stderr, "Error: could not load alien bullet bitmap");
        //limpar o q foi usado
        return false;
    }
    al_convert_mask_to_alpha((*p_enemies).alien_bullet_img, al_map_rgb(0, 0 , 0));

    return true;
}

void free_enemies_resources(enemies *p_enemies){
    al_destroy_bitmap((*p_enemies).alien1img);
    al_destroy_bitmap((*p_enemies).alien2img);
    al_destroy_bitmap((*p_enemies).alien3img);
    al_destroy_bitmap((*p_enemies).exp_img);
    al_destroy_bitmap((*p_enemies).alien_bullet_img);

}
