#ifndef ALIENFUNC_H_INCLUDED
#define ALIENFUNC_H_INCLUDED

const int NUM_ALIEN = 10;


void InitAlien1(enemy alien1[], const int NUM_ALIEN){
    for(int i = 0; i<NUM_ALIEN; ++i){
        alien1[i].x = 256 + i*75;
        alien1[i].y = 0;
        alien1[i].velx = 5;
        alien1[i].vely = 15;
        alien1[i].live = true;
        alien1[i].totalframes = 2;
        alien1[i].currentframe = 0;
        alien1[i].framedelay = 50;
        alien1[i].framecounter = 0;
        alien1[i].framewidth = 65;
        alien1[i].frameheight = 52;

    }

}

void InitAlien2(enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            alien2[i][j].x = 256 + j*75;
            alien2[i][j].y = (i+1)*62;
            alien2[i][j].velx = 5;
            alien2[i][j].vely = 7.5;
            alien2[i][j].live = true;
            alien2[i][j].totalframes = 2;
            alien2[i][j].currentframe = 0;
            alien2[i][j].framedelay = 50;
            alien2[i][j].framecounter = 0;
            alien2[i][j].framewidth = 65;
            alien2[i][j].frameheight = 52;
        }
    }

}


void InitAlien3(enemy alien3[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            alien3[i][j].x = 256 + j*75;
            alien3[i][j].y = (i+3)*62;
            alien3[i][j].velx = 5;
            alien3[i][j].vely = 7.5;
            alien3[i][j].live = true;
            alien3[i][j].totalframes = 2;
            alien3[i][j].currentframe = 0;
            alien3[i][j].framedelay = 50;
            alien3[i][j].framecounter = 0;
            alien3[i][j].framewidth = 65;
            alien3[i][j].frameheight = 52;
        }
    }

}


void limitXmoveY_alien1(enemy alien1[], const int NUM_ALIEN){
    for(int i = 0; i< NUM_ALIEN; ++i){
        if(alien1[9].x + alien1[9].framewidth >= 1200){
            alien1[i].velx = -5;
            if(alien1[9].y + alien1[9].frameheight <= 245)
                alien1[i].y += alien1[i].vely;
        }

        if(alien1[0].x <= 80){
            alien1[i].velx = 5;
            if(alien1[0].y + alien1[i].frameheight <= 245)
                alien1[i].y += alien1[i].vely;
        }
    }

}

void limitXmoveY_alien2(enemy alien2[][NUM_ALIEN], const int x){
    for(int i = 0; i<x; ++i){
        for(int j = 0; j<NUM_ALIEN; ++j){
            if(alien2[i][9].x + alien2[1][j].framewidth >= 1200){
                alien2[i][j].velx = -5;
                if(alien2[1][j].y + alien2[1][j].frameheight <= 369)
                    alien2[1][j].y += alien2[i][j].vely;
                if(alien2[0][j].y + alien2[0][j].frameheight <= 307)
                    alien2[0][j].y += alien2[i][j].vely;
            }

            if(alien2[i][0].x <= 80){
                alien2[i][j].velx = 5;
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
                alien3[i][j].velx = -5;
                if(alien3[1][j].y + alien3[1][j].frameheight <= 493)
                    alien3[1][j].y += alien3[i][j].vely;
                if(alien3[0][j].y + alien3[0][j].frameheight<= 431)
                    alien3[0][j].y += alien3[i][j].vely;
            }

            if(alien3[i][0].x <=80){
                alien3[i][j].velx = 5;
                if(alien3[1][j].y + alien3[1][j].frameheight <= 493)
                    alien3[1][j].y += alien3[i][j].vely;
                if(alien3[0][j].y + alien3[0][j].frameheight<= 431)
                    alien3[0][j].y += alien3[i][j].vely;
            }
        }
    }

}


void moveX_alien1(enemy alien1[], const int NUM_ALIEN){
    for(int i = 0; i< NUM_ALIEN; ++i)
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


void updateSprite_alien1(enemy alien1[], const int NUM_ALIEN){
    for(int i = 0; i< NUM_ALIEN; ++i){
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


void draw_alien1(ALLEGRO_BITMAP *alien1img, enemy alien1[], const int NUM_ALIEN){
    for(int i = 0; i<NUM_ALIEN; ++i){
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

#endif // ALIENFUNC_H_INCLUDED
