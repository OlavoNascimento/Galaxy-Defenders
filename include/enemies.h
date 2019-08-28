#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <allegro5/allegro.h>

#include "game_state.h"
#include "player_ship.h"


#define NUM_ALIEN 10
#define NUM_ALIEN_i 2

#define NUM_aBULLETS 10

//struct com as vars para construir a logica da explosao.
typedef struct{
    int totalframes;
    int currentframe;
    int framedelay;
    int framecounter;
    int framewidth;
    bool start;
}explosion;

//struct com as informaçoes gerais de cada alien.
typedef struct{
    float x;
    float y;
    float velx;
    float vely;
    int live;
    Sprite sprite;
    explosion exp;
}enemy;


//struct com as informaçoes gerais das balas dos aliens.
typedef struct{
    int x;
    int y;
    bool live;
    int speed;
    int width;
    int height;
}alienbullet;

//struct com as variaveis que possibilitam a logica do disparo dos aliens
typedef struct{
    alienbullet aBullet[NUM_aBULLETS]; // vetor em que cada posicao representa uma bala.
    enemy *alien_shooter[NUM_ALIEN];//ponteiro para guardar o endereco dos candidatos a disparar de cada coluna.
    int k;//indice gerado aleatoriamente para escolher qual alien do ponteiro acima ira disparar.
    bool check_array[NUM_ALIEN];//vetor para guardar qual coluna ja teve o seu candidato a disparo escolhido.
    int all_aliens_Rdead;//var para checar o momento em que todos os aliens estiverem mortos ( = parar disparos).
    int alien_shot_delay;  //delay para impedir que os aliens disparem muito rapido(a cada estouro do timer).
}alienshots;


typedef struct{
    enemy alien1[NUM_ALIEN]; //inimigos da 1.o linha.
    ALLEGRO_BITMAP *alien1img;
    enemy alien2[2][NUM_ALIEN]; //inimigos da 2.o e 3.o linha.
    ALLEGRO_BITMAP *alien2img;
    enemy alien3[2][NUM_ALIEN]; //inimigos da 4.o e 5.o linha.
    ALLEGRO_BITMAP *alien3img;
    ALLEGRO_BITMAP *exp_img; ; //imagem da explosao
    alienshots alienShots;
    ALLEGRO_BITMAP *alien_bullet_img;
    int aliens_defeated; //contador para ir guardando a quantidade de aliens mortos atualmente. (para determinarmos o termino do jogo)
}enemies;


//atribuindo valores iniciais as informacoes gerais de cada alien:
void InitAlien1(enemies *p_enemies);

void InitAlien2(enemies *p_enemies);

void InitAlien3(enemies *p_enemies);


//limitando o movimento horizontal dos aliens e movimentando-os verticalmente:
void limitXmoveY_alien1(enemies *p_enemies);

void limitXmoveY_alien2(enemies *p_enemies);

void limitXmoveY_alien3(enemies *p_enemies);


//movimentando os aliens horizontalmente:
void moveX_alien1(enemies *p_enemies);

void moveX_alien2(enemies *p_enemies);

void moveX_alien3(enemies *p_enemies);


//atualizando os sprites dos inimigos constantemente:
void updateSprite_alien1(enemies *p_enemies);

void updateSprite_alien2(enemies *p_enemies);

void updateSprite_alien3(enemies *p_enemies);


//desenhando cada alien na sua posicao atual:
void draw_alien1(enemies *p_enemies);

void draw_alien2(enemies *p_enemies);

void draw_alien3(enemies *p_enemies);


//verificando se houve a colisao entre as balas e os inimigos:
void detectBulletCollision_alien1(enemies *p_enemies, PlayerShip *player);

void detectBulletCollision_alien2(enemies *p_enemies, PlayerShip *player);

void detectBulletCollision_alien3(enemies *p_enemies, PlayerShip *player);



//atrubui valores iniciais a struct das balas:
void Init_aBullet(enemies *p_enemies);

//escolhe um alien aleatorio para disparar(apenas os aliens que sao os ultimos de sua coluna podem ser candidatos a disparar):
void choose_shooter_alien(enemies *p_enemies);

//funcao que faz o alien escolhido efetuar o disparo:
void fire_aBullet(enemies *p_enemies);

//movimenta as balas disparadas:
void update_aBullet(enemies *p_enemies);

//desenha as balas na tela:
void draw_aBullet(enemies *p_enemies);

//funçao de inicializaçao geral dos inimigos.
bool InitEnemies(enemies *p_enemies);

//libera os recursos usados pelos aliens
void free_enemies_resources(enemies *p_enemies);


#endif // ENEMIES_H_INCLUDED
