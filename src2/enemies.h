#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <allegro5/allegro.h>
#include "main.h"

//numero de aliens em cada fileira:
#define NUM_ALIEN 10

//struct com as informaçoes de cada alien:
typedef struct{
    float x;
    float y;
    float velx;
    float vely;
    int live;
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
    int framewidth;
    int frameheight;
    bool explosion;

}enemy;

//atribuindo valores iniciais as informaçoes de cada alien:
void InitAlien1(enemy alien1[], int NUMALIEN);

void InitAlien2(enemy alien2[][NUM_ALIEN], const int x);

void InitAlien3(enemy alien3[][NUM_ALIEN], const int x);


//limitando o movimento horizontal dos aliens e movimentando-os verticalmente:
void limitXmoveY_alien1(enemy alien1[], const int NUMALIEN);

void limitXmoveY_alien2(enemy alien2[][NUM_ALIEN], const int x);

void limitXmoveY_alien3(enemy alien3[][NUM_ALIEN], const int x);


//movimentando os aliens horizontalmente:
void moveX_alien1(enemy alien1[], const int NUMALIEN);

void moveX_alien2(enemy alien2[][NUM_ALIEN], const int x);

void moveX_alien3(enemy alien3[][NUM_ALIEN], const int x);


//atualizando os sprites dos inimigos constantemente:
void updateSprite_alien1(enemy alien1[], const int NUMALIEN);

void updateSprite_alien2(enemy alien2[][NUM_ALIEN], const int x);

void updateSprite_alien3(enemy alien3[][NUM_ALIEN], const int x);


//desenhando cada alien na sua posiçao atual:
void draw_alien1(ALLEGRO_BITMAP *alien1img, enemy alien1[], const int NUMALIEN);

void draw_alien2(ALLEGRO_BITMAP *alien2img, enemy alien2[][NUM_ALIEN], const int x);

void draw_alien3(ALLEGRO_BITMAP *alien3img, enemy alien3[][NUM_ALIEN], const int x);


//verificando se houve a colisao entre as balas e os inimigos:
void detectBulletCollision_alien1(enemy alien1[], const int NUMALIEN, bullet bullets[], const int bulletquantity);

void detectBulletCollision_alien2(enemy alien2[][NUM_ALIEN], const int x, bullet bullets[], const int bulletquantity);

void detectBulletCollision_alien3(enemy alien3[][NUM_ALIEN], const int x, bullet bullets[], const int bulletquantity);


#endif // ENEMIES_H_INCLUDED
