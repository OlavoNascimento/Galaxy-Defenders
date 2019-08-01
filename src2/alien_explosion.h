#ifndef ALIEN_EXPLOSION_H_INCLUDED
#define ALIEN_EXPLOSION_H_INCLUDED

typedef struct{
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
    int framewidth;
    bool start;
}explosion;


void update_explosion_alien1(void);

void draw_explosion_alien1(void);


void update_explosion_alien2(void);

void draw_explosion_alien2(void);


void update_explosion_alien3(void);

void draw_explosion_alien3(void);

#endif // ALIEN_EXPLOSION_H_INCLUDED
