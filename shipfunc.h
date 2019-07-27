#ifndef SHIPFUNC_H_INCLUDED
#define SHIPFUNC_H_INCLUDED


//Initial ship values
void Initship(spaceship *Pship){
    (*Pship).x = gDISPLAYw/2;
    (*Pship).y = gDISPLAYh - 150;
    (*Pship).lives = 3;
    (*Pship).speed = 7;
    (*Pship).score = 0;
}


//drawing the ship:
void drawShip(spaceship *Pship, ALLEGRO_BITMAP *shipimg){
    al_draw_bitmap(shipimg, (*Pship).x, (*Pship).y, 0);

}


//Moving the ship:

enum KEY{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};


void moveshipUP(spaceship *Pship){
    (*Pship).y -= (*Pship).speed;
    if((*Pship).y < 0)
        (*Pship).y = 0;
}

void moveshipDOWN(spaceship *Pship){
    (*Pship).y += (*Pship).speed;
    if((*Pship).y > gDISPLAYh)
        (*Pship).y = gDISPLAYh;
}

void moveshipLEFT(spaceship *Pship){
    (*Pship).x -= (*Pship).speed;
    if((*Pship).x < 0)
        (*Pship).y = 0;
}

void moveshipRIGHT(spaceship *Pship){
    (*Pship).x += (*Pship).speed;
    if((*Pship).x > gDISPLAYw)
        (*Pship).x = gDISPLAYw;
}



//player bullet functions:

const int NUM_BULLETS = 5;

void Initbullet(bullet bullets[], int size){
    for(int i = 0; i<size; ++i){
        bullets[i].speed = 10;
        bullets[i].live = false;
    }
}

void fireBullet(bullet bullets[], int size, spaceship *Pship){
    for(int i = 0; i<size; ++i){
        if(!bullets[i].live){
            bullets[i].x = (*Pship).x;
            bullets[i].y = (*Pship).y;
            bullets[i].live = true;
            break;
        }
    }

}

void drawBullet(bullet bullets[], int size, ALLEGRO_BITMAP *Bimg){
    for(int i = 0; i<size; ++i){
        if(bullets[i].live)
            al_draw_bitmap(Bimg, bullets[i].x, bullets[i].y, 0);

    }

}

void updateBullet(bullet bullets[], int size){
    for(int i = 0; i<size; ++i){
        if(bullets[i].live){
            bullets[i].y -= bullets[i].speed;
            if(bullets[i].y < 0)
                bullets[i].live = false;
        }
    }

}


#endif // SHIPFUNC_H_INCLUDED
