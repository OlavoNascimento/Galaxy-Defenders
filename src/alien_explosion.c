#include <allegro5/allegro.h>

#include "alien_explosion.h"
#include "enemies.h"



void update_explosion_alien1 (enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[i].exp.start){
            if(++(*p_enemies).alien1[i].exp.framecounter >= (*p_enemies).alien1[i].exp.framedelay){
                    if(++(*p_enemies).alien1[i].exp.currentframe >= (*p_enemies).alien1[i].exp.totalframes){
                        (*p_enemies).alien1[i].exp.start = false;
                    }
                    (*p_enemies).alien1[i].exp.framecounter = 0;
                }
        }
    }



}


void draw_explosion_alien1(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if((*p_enemies).alien1[i].exp.start){
            al_draw_bitmap_region((*p_enemies).exp_img,
                                  (*p_enemies).alien1[i].exp.framewidth * (*p_enemies).alien1[i].exp.currentframe,
                                  0,
                                  (*p_enemies).alien1[i].sprite.width,
                                  (*p_enemies).alien1[i].sprite.height,
                                  (*p_enemies).alien1[i].x,
                                  (*p_enemies).alien1[i].y,
                                  0);
        }
    }

}


void update_explosion_alien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
                if((*p_enemies).alien2[i][j].exp.start){
                    if(++(*p_enemies).alien2[i][j].exp.framecounter >= (*p_enemies).alien2[i][j].exp.framedelay){
                        if(++(*p_enemies).alien2[i][j].exp.currentframe >= (*p_enemies).alien2[i][j].exp.totalframes){
                                (*p_enemies).alien2[i][j].exp.start = false;
                        }
                        (*p_enemies).alien2[i][j].exp.framecounter = 0;
                    }
                }
        }
    }

}


void draw_explosion_alien2(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien2[i][j].exp.start){
                al_draw_bitmap_region((*p_enemies).exp_img,
                                      (*p_enemies).alien2[i][j].exp.framewidth * (*p_enemies).alien2[i][j].exp.currentframe,
                                      0,
                                      (*p_enemies).alien2[i][j].sprite.width,
                                      (*p_enemies).alien2[i][j].sprite.height,
                                      (*p_enemies).alien2[i][j].x,
                                      (*p_enemies).alien2[i][j].y,
                                      0);
            }
        }
    }

}




void update_explosion_alien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
                if((*p_enemies).alien3[i][j].exp.start){
                    if(++(*p_enemies).alien3[i][j].exp.framecounter >= (*p_enemies).alien3[i][j].exp.framedelay){
                        if(++(*p_enemies).alien3[i][j].exp.currentframe >= (*p_enemies).alien3[i][j].exp.totalframes){
                                (*p_enemies).alien3[i][j].exp.start = false;
                        }
                        (*p_enemies).alien3[i][j].exp.framecounter = 0;
                    }
                }
        }
    }

}


void draw_explosion_alien3(enemies *p_enemies){
    for(int i = 0; i<NUM_ALIEN_i; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if((*p_enemies).alien3[i][j].exp.start){
                al_draw_bitmap_region((*p_enemies).exp_img,
                                      (*p_enemies).alien3[i][j].exp.framewidth * (*p_enemies).alien3[i][j].exp.currentframe,
                                       0,
                                      (*p_enemies).alien3[i][j].sprite.width,
                                      (*p_enemies).alien3[i][j].sprite.height,
                                      (*p_enemies).alien3[i][j].x,
                                      (*p_enemies).alien3[i][j].y,
                                      0);
            }
        }
    }

}


