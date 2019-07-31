#ifndef PLAYER_SHIP_H_INCLUDED
#define PLAYER_SHIP_H_INCLUDED

//vetor para guardar o estado das setas(pressionada ou nao):
enum KEY{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5];


typedef struct{
    int x;
    int y;
    int lives;
    int speed;
    int score;
}spaceship;


//atribuindo valores iniciais as informaçoes da nave:
void Initship(spaceship *Pship);

//desenha a nave na posicao atual:
void drawShip(spaceship *Pship, ALLEGRO_BITMAP *shipimg);

//move a nave na direçao da seta pressionada:
void moveshipUP(spaceship *Pship);

void moveshipDOWN(spaceship *Pship);

void moveshipLEFT(spaceship *Pship);

void moveshipRIGHT(spaceship *Pship);



//numero maximo de balas (da nave) na tela ao mesmo tempo:
#define NUM_BULLETS 5


typedef struct{
    int x;
    int y;
    int live;
    int speed;
    int width;
    int height;
}bullet;


//atribuindo valores iniciais as informaçoes das balas:
void Initbullet(bullet bullets[], int size);

//revive uma bala morta e a posiciona em algum lugar(frente a nave):
void fireBullet(bullet bullets[], int size, spaceship *Pship);

//desenha a bala em sua posicao atual(caso esteja viva):
void drawBullet(bullet bullets[], int size, ALLEGRO_BITMAP *Bimg);

//faz as balas vivas subirem para cima constantemente:
void updateBullet(bullet bullets[], int size);



#endif // PLAYER_SHIP_H_INCLUDED
