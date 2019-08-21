#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <allegro5/allegro.h>

#include "main.h"
#include "alien_explosion.h"
#include "player_ship.h"

//numero de aliens em cada fileira:
#define NUM_ALIEN 10


//struct com as informa�oes de cada alien:
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
    explosion exp;
}enemy;

//atribuindo valores iniciais as informa�oes de cada alien:
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


//desenhando cada alien na sua posi�ao atual:
void draw_alien1(ALLEGRO_BITMAP *alien1img, enemy alien1[], const int NUMALIEN);

void draw_alien2(ALLEGRO_BITMAP *alien2img, enemy alien2[][NUM_ALIEN], const int x);

void draw_alien3(ALLEGRO_BITMAP *alien3img, enemy alien3[][NUM_ALIEN], const int x);


//verificando se houve a colisao entre as balas e os inimigos:
void detectBulletCollision_alien1(enemy alien1[], const int NUMALIEN, PlayerShip *player);

void detectBulletCollision_alien2(enemy alien2[][NUM_ALIEN], const int x, PlayerShip *player);

void detectBulletCollision_alien3(enemy alien3[][NUM_ALIEN], const int x, PlayerShip *player);



//disparo dos aliens{

    //ponteiro para guardar o endere�o dos candidatos a disparar de cada coluna:
    enemy *alien_shooter[NUM_ALIEN];

    //indice gerado aleatoriamente para escolher qual alien do ponteiro acima ira disparar:
    int k;

    //vetor para guardar qual coluna ja teve o seu candidato a disparo escolhido:
    bool check_array[NUM_ALIEN];

    //var para checar o momento em que todos os aliens estiverem mortos ( = parar disparos):
    int all_aliens_Rdead;

    //delay para impedir que os aliens disparem muito rapido(a cada estouro do timer):
    int alien_shot_delay;

    //struct e vetor das balas dos aliens:
    typedef struct{
        int x;
        int y;
        bool live;
        int speed;
        int width;
        int height;
    }alienbullet;


    #define NUM_aBULLETS 7

    //(o tamanho dele se refere a quantidade de balas simutaneas que podem haver na tela)
    alienbullet aBullet[NUM_aBULLETS];



    //atrubui valores iniciais a struct das balas:
    void Init_aBullet(void);

    //escolhe um alien aleatorio para disparar(apenas os aliens que sao os ultimos de sua coluna podem ser candidatos a disparar):
    void choose_shooter_alien(void);

    //fun�ao que faz o alien escolhido efetuar o disparo:
    void fire_aBullet(void);

    //movimenta as balas disparadas:
    void update_aBullet(void);

    //void aBullet_sprite(void);

    //desenha as balas na tela:
    void draw_aBullet(void);

//}


#endif // ENEMIES_H_INCLUDED
