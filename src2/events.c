#include <allegro5/allegro.h>

#include "main.h"


void key_pressed_down_event_dealing(ALLEGRO_EVENT *event){ //OBS: (aqui ficam as açoes que precisam ser performadas quando uma tecla e pressionada)

    //guarda qual das setas foi pressionada:
    switch((*event).keyboard.keycode){
        case ALLEGRO_KEY_ESCAPE:
            exitl = true;
            break;
        case ALLEGRO_KEY_UP:
            keys[UP] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            keys[DOWN] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            keys[LEFT] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            keys[RIGHT] = true;
            break;
        case ALLEGRO_KEY_SPACE:
            keys[SPACE] = true;
            //quando a tecla espaço for pressionada chamamos a funçao que efetua o disparo da nave:
            fireBullet(bullets, NUM_BULLETS, &Pship);
            break;
    }

}

void key_pressed_up_event_dealing(ALLEGRO_EVENT *event){       //OBS: (aqui ficam as açoes que precisam ser performadas quando uma tecla,
                                                             //       anteriormente pressionada, for solta)

    //guarda qual das setas foi solta:
    switch((*event).keyboard.keycode){
        case ALLEGRO_KEY_UP:
            keys[UP] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            keys[DOWN] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            keys[LEFT] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            keys[RIGHT] = false;
            break;
        case ALLEGRO_KEY_SPACE:
            keys[SPACE] = false;
            break;

}

}

void timer_event_dealing(void){  //OBS: (aqui ficam as açoes que precisam ser performadas a todo momento)
    redraw = true;

    //nave{
        //verifica se alguma das setas foi pressionada. Se sim move a nave nessa direçao:
        if(keys[UP])
            moveshipUP(&Pship);
        if(keys[DOWN])
            moveshipDOWN(&Pship);
        if(keys[LEFT])
            moveshipLEFT(&Pship);
        if(keys[RIGHT])
            moveshipRIGHT(&Pship);

        //movimentação das balas da nave:
        updateBullet(bullets, NUM_BULLETS);

        //}

    //colisao dos aliens com balas{

        //verificando se houve a colisao entre as balas e os inimigos. Se sim, apaga o inimigo e a bala.
        detectBulletCollision_alien1(alien1, NUM_ALIEN, bullets, NUM_BULLETS);

        detectBulletCollision_alien2(alien2, 2, bullets, NUM_BULLETS);

        detectBulletCollision_alien3(alien3, 2, bullets, NUM_BULLETS);

        //colisionPlayer();

        update_explosion_alien1();

        update_explosion_alien2();

        update_explosion_alien3();

    //}

    //colisoes da barreira

        colisionAlien();

        colisionPlayer();

        lifeBarrier();


    //Movimento dos aliens{

        //limitando o movimento horizontal dos aliens e movimentando-os verticalmente:
        limitXmoveY_alien1(alien1, NUM_ALIEN);

        limitXmoveY_alien2(alien2, 2);

        limitXmoveY_alien3(alien3, 2);


        //movimentando os aliens horizontalmente:
        moveX_alien1(alien1, NUM_ALIEN);

        moveX_alien2(alien2, 2);

        moveX_alien3(alien3, 2);


        //atualizando os sprites dos inimigos constantemente:
        updateSprite_alien1(alien1, NUM_ALIEN);

        updateSprite_alien2(alien2, 2);

        updateSprite_alien3(alien3, 2);
    //}


    //Disparo dos aliens{

        //delay para impedir que os aliens disparem muito rapido(a cada estouro do timer):
        if(++alien_shot_delay >= 50){

            choose_shooter_alien();

            fire_aBullet();

            alien_shot_delay = 0;
        }

        update_aBullet();

    //}


}



void deal_with_events(ALLEGRO_EVENT *event){         //lida devidamente com o evento gerado:
    switch((*event).type){
        case ALLEGRO_EVENT_KEY_DOWN:
            key_pressed_down_event_dealing(event);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key_pressed_up_event_dealing(event);
            break;
        case ALLEGRO_EVENT_TIMER:
            timer_event_dealing();
            break;

    }

}

