#include "main.h"


void update_explosion_alien1(void){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if(alien1[i].exp.start){
            if(++alien1[i].exp.framecounter >= alien1[i].exp.framedelay){
                    if(++alien1[i].exp.currentframe >= alien1[i].exp.totalframes){
                        alien1[i].exp.start = false;
                    }
                    alien1[i].exp.framecounter = 0;
                }
        }
    }



}


void draw_explosion_alien1(void){
    for(int i = 0; i<NUM_ALIEN; ++i){
        if(alien1[i].exp.start){
            al_draw_bitmap_region(exp_img, alien1[i].exp.framewidth * alien1[i].exp.currentframe, 0, alien1[i].framewidth, alien1[i].frameheight, alien1[i].x, alien1[i].y, 0);

        }
    }



}


void update_explosion_alien2(void){
    for(int i = 0; i<2; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
                if(alien2[i][j].exp.start){
                    if(++alien2[i][j].exp.framecounter >= alien2[i][j].exp.framedelay){
                        if(++alien2[i][j].exp.currentframe >= alien2[i][j].exp.totalframes){
                                alien2[i][j].exp.start = false;
                        }
                        alien2[i][j].exp.framecounter = 0;
                    }
                }
        }
    }

}


void draw_explosion_alien2(void){
    for(int i = 0; i<2; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][j].exp.start){
                al_draw_bitmap_region(exp_img, alien2[i][j].exp.framewidth * alien2[i][j].exp.currentframe, 0, alien2[i][j].framewidth, alien2[i][j].frameheight, alien2[i][j].x, alien2[i][j].y, 0);
            }
        }
    }

}




void update_explosion_alien3(void){
    for(int i = 0; i<2; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
                if(alien3[i][j].exp.start){
                    if(++alien3[i][j].exp.framecounter >= alien3[i][j].exp.framedelay){
                        if(++alien3[i][j].exp.currentframe >= alien3[i][j].exp.totalframes){
                                alien3[i][j].exp.start = false;
                        }
                        alien3[i][j].exp.framecounter = 0;
                    }
                }
        }
    }

}


void draw_explosion_alien3(void){
    for(int i = 0; i<2; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien3[i][j].exp.start){
                al_draw_bitmap_region(exp_img, alien3[i][j].exp.framewidth * alien3[i][j].exp.currentframe, 0, alien3[i][j].framewidth, alien3[i][j].frameheight, alien3[i][j].x, alien3[i][j].y, 0);
            }
        }
    }

}


