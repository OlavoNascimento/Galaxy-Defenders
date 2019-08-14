#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


#include "main.h"



void InitAlien1(enemy alien1[], const int NUMALIEN){
    for(int i = 0; i<NUMALIEN; ++i){
        alien1[i].x = 256 + i*75;
        alien1[i].y = 0;
        alien1[i].velx = 2;
        alien1[i].vely = 15;
        alien1[i].live = true;
        alien1[i].totalframes = 2;
        alien1[i].currentframe = 0;
        alien1[i].framedelay = 50;
        alien1[i].framecounter = 0;
        alien1[i].framewidth = 65;
        alien1[i].frameheight = 52;

        alien1[i].exp.totalframes = 7;
        alien1[i].exp.currentframe = 0;
        alien1[i].exp.framedelay = 5;
        alien1[i].exp.framecounter = 0;
        alien1[i].exp.framewidth = 65;
        alien1[i].exp.start = false;



    }

}

void InitAlien2(enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            alien2[i][j].x = 256 + j*75;
            alien2[i][j].y = (i+1)*62;
            alien2[i][j].velx = 2;
            alien2[i][j].vely = 7.5;
            alien2[i][j].live = true;
            alien2[i][j].totalframes = 2;
            alien2[i][j].currentframe = 0;
            alien2[i][j].framedelay = 50;
            alien2[i][j].framecounter = 0;
            alien2[i][j].framewidth = 65;
            alien2[i][j].frameheight = 52;

            alien2[i][j].exp.totalframes = 7;
            alien2[i][j].exp.currentframe = 0;
            alien2[i][j].exp.framedelay = 5;
            alien2[i][j].exp.framecounter = 0;
            alien2[i][j].exp.framewidth = 65;
            alien2[i][j].exp.start = false;

        }
    }

}


void InitAlien3(enemy alien3[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            alien3[i][j].x = 256 + j*75;
            alien3[i][j].y = (i+3)*62;
            alien3[i][j].velx = 2;
            alien3[i][j].vely = 7.5;
            alien3[i][j].live = true;
            alien3[i][j].totalframes = 2;
            alien3[i][j].currentframe = 0;
            alien3[i][j].framedelay = 50;
            alien3[i][j].framecounter = 0;
            alien3[i][j].framewidth = 65;
            alien3[i][j].frameheight = 52;

            alien3[i][j].exp.totalframes = 7;
            alien3[i][j].exp.currentframe = 0;
            alien3[i][j].exp.framedelay = 5;
            alien3[i][j].exp.framecounter = 0;
            alien3[i][j].exp.framewidth = 65;
            alien3[i][j].exp.start = false;

        }
    }

}


void limitXmoveY_alien1(enemy alien1[], const int NUMALIEN){
    for(int i = 0; i< NUMALIEN; ++i){
        if(alien1[9].x + alien1[9].framewidth >= 1200){
            alien1[i].velx = -2;
            if(alien1[9].y + alien1[9].frameheight <= 245)
                alien1[i].y += alien1[i].vely;
        }

        if(alien1[0].x <= 80){
            alien1[i].velx = 2;
            if(alien1[0].y + alien1[i].frameheight <= 245)
                alien1[i].y += alien1[i].vely;
        }
    }

}

void limitXmoveY_alien2(enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][9].x + alien2[1][j].framewidth >= 1200){
                alien2[i][j].velx = -2;
                if(alien2[1][j].y + alien2[1][j].frameheight <= 369)
                    alien2[1][j].y += alien2[i][j].vely;
                if(alien2[0][j].y + alien2[0][j].frameheight <= 307)
                    alien2[0][j].y += alien2[i][j].vely;
            }

            if(alien2[i][0].x <= 80){
                alien2[i][j].velx = 2;
                if(alien2[1][j].y + alien2[1][j].frameheight <= 369)
                    alien2[1][j].y += alien2[i][j].vely;
                if(alien2[0][j].y + alien2[0][j].frameheight <= 307)
                    alien2[0][j].y += alien2[i][j].vely;
            }
        }
    }

}


void limitXmoveY_alien3(enemy alien3[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien3[i][9].x + alien3[i][9].framewidth >= 1200){
                alien3[i][j].velx = -2;
                if(alien3[1][j].y + alien3[1][j].frameheight <= 493)
                    alien3[1][j].y += alien3[i][j].vely;
                if(alien3[0][j].y + alien3[0][j].frameheight<= 431)
                    alien3[0][j].y += alien3[i][j].vely;
            }

            if(alien3[i][0].x <=80){
                alien3[i][j].velx = 2;
                if(alien3[1][j].y + alien3[1][j].frameheight <= 493)
                    alien3[1][j].y += alien3[i][j].vely;
                if(alien3[0][j].y + alien3[0][j].frameheight<= 431)
                    alien3[0][j].y += alien3[i][j].vely;
            }
        }
    }

}


void moveX_alien1(enemy alien1[], const int NUMALIEN){
    for(int i = 0; i< NUMALIEN; ++i)
        alien1[i].x += alien1[i].velx;

}


void moveX_alien2(enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i)
        for(int j = 0; j<NUM_ALIEN; ++j)
            alien2[i][j].x += alien2[i][j].velx;

}


void moveX_alien3(enemy alien3[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i)
        for(int j = 0; j<NUM_ALIEN; ++j)
            alien3[i][j].x += alien3[i][j].velx;

}


void updateSprite_alien1(enemy alien1[], const int NUMALIEN){
    for(int i = 0; i< NUMALIEN; ++i){
        if(alien1[i].live){
            if(++alien1[i].framecounter >= alien1[i].framedelay){
                if(++alien1[i].currentframe >= alien1[i].totalframes){
                    alien1[i].currentframe = 0;
                }
                alien1[i].framecounter = 0;
            }
        }
    }

}

void updateSprite_alien2(enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][j].live){
                if(++alien2[i][j].framecounter >= alien2[i][j].framedelay){
                    if(++alien2[i][j].currentframe >= alien2[i][j].totalframes){
                        alien2[i][j].currentframe = 0;
                    }
                    alien2[i][j].framecounter = 0;
                }
            }
        }
    }

}

void updateSprite_alien3(enemy alien3[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien3[i][j].live){
                if(++alien3[i][j].framecounter >= alien3[i][j].framedelay){
                    if(++alien3[i][j].currentframe >= alien3[i][j].totalframes){
                        alien3[i][j].currentframe = 0;
                    }
                    alien3[i][j].framecounter = 0;
                }
            }
        }
    }

}


void draw_alien1(ALLEGRO_BITMAP *alien1img, enemy alien1[], const int NUMALIEN){
    for(int i = 0; i<NUMALIEN; ++i){
        if(alien1[i].live)
            al_draw_bitmap_region(alien1img, alien1[i].currentframe*alien1[i].framewidth, 0, alien1[i].framewidth, alien1[i].frameheight, alien1[i].x, alien1[i].y, 0);
    }

}

void draw_alien2(ALLEGRO_BITMAP *alien2img, enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][j].live)
                al_draw_bitmap_region(alien2img, alien2[i][j].currentframe*alien2[i][j].framewidth, 0, alien2[i][j].framewidth, alien2[i][j].frameheight, alien2[i][j].x, alien2[i][j].y, 0);
        }
    }

}

void draw_alien3(ALLEGRO_BITMAP *alien3img, enemy alien3[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien3[i][j].live)
                al_draw_bitmap_region(alien3img, alien3[i][j].currentframe*alien3[i][j].framewidth, 0, alien3[i][j].framewidth, alien3[i][j].frameheight, alien3[i][j].x, alien3[i][j].y, 0);
        }
    }

}

void detectBulletCollision_alien1(enemy alien1[], const int NUMALIEN, PlayerShip *player){
    for(int i = 0; i<NUMALIEN; ++i){
        if(alien1[i].live){
            for(int j = 0; j<player->lasers.alive; ++j){
                if(player->lasers.fired[j].pos_x <= alien1[i].x + alien1[i].framewidth - 2 &&
                   player->lasers.fired[j].pos_x + player->lasers.sprite.width >= alien1[i].x + 2 &&
                   player->lasers.fired[j].pos_y <= alien1[i].y + alien1[i].frameheight - 2 &&
                   player->lasers.fired[j].pos_y + player->lasers.sprite.height >= alien1[i].y + 2){
                    remove_player_laser_fired(player, j);
                    alien1[i].live = false;
                    alien1[i].exp.start = true;
                }
            }
        }

    }
}


void detectBulletCollision_alien2(enemy alien2[][NUM_ALIEN], const int x, PlayerShip *player){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][j].live){
                for(int k = 0; k<player->lasers.alive; ++k){
                    if(player->lasers.fired[k].pos_x <= alien2[i][j].x + alien2[i][j].framewidth - 2 &&
                       player->lasers.fired[k].pos_x + player->lasers.sprite.width >= alien2[i][j].x + 2 &&
                       player->lasers.fired[k].pos_y <= alien2[i][j].y + alien2[i][j].frameheight - 2 &&
                       player->lasers.fired[k].pos_y + player->lasers.sprite.height >= alien2[i][j].y + 2){
                        remove_player_laser_fired(player, j);
                        alien2[i][j].live = false;
                        alien2[i][j].exp.start = true;
                    }
                }
            }
        }
    }
}

void detectBulletCollision_alien3(enemy alien3[][NUM_ALIEN], const int x, PlayerShip *player){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien3[i][j].live){
                for(int k = 0; k<player->lasers.alive; ++k){
                    if(player->lasers.fired[k].pos_x <= alien3[i][j].x + alien3[i][j].framewidth - 2 &&
                       player->lasers.fired[k].pos_x + player->lasers.sprite.width >= alien3[i][j].x + 2 &&
                       player->lasers.fired[k].pos_y <= alien3[i][j].y + alien3[i][j].frameheight - 2 &&
                       player->lasers.fired[k].pos_y + player->lasers.sprite.height >= alien3[i][j].y + 2){
                        remove_player_laser_fired(player, k);
                        alien3[i][j].live = false;
                        alien3[i][j].exp.start = true;
                    }
                }
            }
        }
    }
}


//escolhe um alien aleatorio para disparar(apenas os aliens que sao os ultimos de sua coluna podem ser candidatos a disparar):
void choose_shooter_alien(void){
    //devemos limpar as variaves antes de come�ar para evitar lixo:
    for(int i = 0; i<NUM_ALIEN; ++i){
        check_array[i] = false;
        alien_shooter[i] = NULL;
    }

    for(int i = 1; i>-1; --i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien3[i][j].live && !check_array[j]){
                check_array[j] = true;
                alien_shooter[j] = &alien3[i][j];
            }

        }
    }

    for(int i = 1; i>-1; --i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][j].live && !check_array[j]){
                check_array[j] = true;
                alien_shooter[j] = &alien2[i][j];
            }
        }
    }

    for(int i = 0; i<NUM_ALIEN; ++i){
        if(alien1[i].live && !check_array[i]){
            check_array[i] = true;
            alien_shooter[i] = &alien1[i];
        }
    }

    all_aliens_Rdead = 0;

    for(int i = 0; i< NUM_ALIEN; ++i){
        if(!check_array[i]){
            ++all_aliens_Rdead;
        }
    }
    srand(time(NULL));

    k = rand () % 9;

    if(!check_array[k]){
        for(int i = 1; i>-1; --i){
            for(int j = 0; j<NUM_ALIEN; ++j){
                if(alien3[i][j].live){
                    alien_shooter[k] = &alien3[i][j];
                    break;
                }else if(alien2[i][j].live){
                    alien_shooter[k] = &alien2[i][j];
                    break;
                }else if(alien1[j].live){
                   alien_shooter[k] = &alien1[j];
                   break;
                }
            }
        }

    }


}

int alien_shot_delay = 0;

void Init_aBullet(void){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        aBullet[i].live = false;
        aBullet[i].speed = 5;
        aBullet[i].width = 18;
        aBullet[i].height = 23;
        //aBullet[i].totalframes = 11;
        //aBullet[i].currentframe = 0;
        //aBullet[i].framedelay = 10;
        //aBullet[i].framecounter = 0;

    }

}



void fire_aBullet (void){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if(all_aliens_Rdead < 10){
            if(!aBullet[i].live){
                aBullet[i].x = (*alien_shooter[k]).x + 32;
                aBullet[i].y = (*alien_shooter[k]).y + 57;
                aBullet[i].live = true;
                break;
            }
        }
    }

}


void update_aBullet(void){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if(aBullet[i].live){
            aBullet[i].y += aBullet[i].speed;
            if(aBullet[i].y > 720){
                aBullet[i].live = false;
                //aBullet[i].currentframe = 0;
            }
        }
    }

}

/*
void aBullet_sprite(void){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if(aBullet[i].live){
            if(aBullet[i].currentframe < aBullet[i].totalframes){
                if(++aBullet[i].framecounter >= aBullet[i].framedelay){
                    ++aBullet[i].currentframe;
                    aBullet[i].framecounter = 0;
                }
            }
        }

    }

}*/


void draw_aBullet (void){
    for(int i = 0; i<NUM_aBULLETS; ++i){
        if(aBullet[i].live){
            al_draw_bitmap(alien_bullet_img, aBullet[i].x , aBullet[i].y , 0);
        }
    }

}

