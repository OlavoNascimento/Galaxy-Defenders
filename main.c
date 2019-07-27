//headers basicos:
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

//valores fixos:
#define gDISPLAYw 1280
#define gDISPLAYh 720
#define FPS 60

//headers criados:
#include "objects.h"
#include "shipfunc.h"
#include "alienfunc.h"


//funçoes criadas:
bool create_display(ALLEGRO_DISPLAY *display);
bool init_basic_resources(void);
void free_basic_resources(void);


//variaveis allegro:
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *ship = NULL;
ALLEGRO_BITMAP *bimg = NULL;
ALLEGRO_BITMAP *alien1img = NULL;
ALLEGRO_BITMAP *alien2img = NULL;
ALLEGRO_BITMAP *alien3img = NULL;
ALLEGRO_EVENT_QUEUE *eventQ = NULL;
ALLEGRO_TIMER *timer = NULL;



int main(void){

    //variavel usada para sair do loop principal do jogo:
    bool exit = false;
    //variavel usada para atualizar a tela(redesenhar objetos):
    bool redraw = true;


    if(!init_basic_resources()){
        return -1;
    }

    if(!create_display(display)){
        return -1;
    }

    //variaveis de objetos do jogo:
    spaceship Pship;
    bullet bullets[5];
    enemy alien1[NUM_ALIEN];
    enemy alien2[2][NUM_ALIEN];
    enemy alien3[2][NUM_ALIEN];



    //iniciando os objetos do jogo:
    Initship(&Pship);
    Initbullet(bullets, NUM_BULLETS);
    InitAlien1(alien1, NUM_ALIEN);
    InitAlien2(alien2, 2);
    InitAlien3(alien3, 2);


    //iniciando o timer (estoura 60 vezes por seg):
    al_start_timer(timer);


    while(!exit){
        //esperando aparecer um evento para podermos trata-lo:
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQ, &event);


        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;

            //movimentação da nave:
            if(keys[UP])
                moveshipUP(&Pship);
            if(keys[DOWN])
                moveshipDOWN(&Pship);
            if(keys[LEFT])
                moveshipLEFT(&Pship);
            if(keys[RIGHT])
                moveshipRIGHT(&Pship);
            //movimentação da bala da nave:
            updateBullet(bullets, NUM_BULLETS);


            //limitando o movimento horizontal dos aliens e movimentando-os verticalmente:
            limitXmoveY_alien1(alien1, NUM_ALIEN);

            limitXmoveY_alien2(alien2, 2);

            limitXmoveY_alien3(alien3, 2);


            //movimentando os aliens horizontalmente:
            moveX_alien1(alien1, NUM_ALIEN);

            moveX_alien2(alien2, 2);

            moveX_alien3(alien3, 2);


            //atualizando os sprites:
            updateSprite_alien1(alien1, NUM_ALIEN);

            updateSprite_alien2(alien2, 2);

            updateSprite_alien3(alien3, 2);


        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    exit = true;
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
                    fireBullet(bullets, NUM_BULLETS, &Pship);
                    break;
            }
        }else if(event.type == ALLEGRO_EVENT_KEY_UP){
            switch(event.keyboard.keycode){
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
        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit = true;
        }


        //redesenhando os objetos do jogo:
        if(redraw && al_is_event_queue_empty(eventQ)){
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));

            drawShip(&Pship, ship);
            drawBullet(bullets, NUM_BULLETS, bimg);

            draw_alien1(alien1img, alien1, NUM_ALIEN);
            draw_alien2(alien2img, alien2, 2);
            draw_alien3(alien3img, alien3, 2);

            al_flip_display();


        }

    }

    //desalocando a memoria usada pelas variaveis allegro:
    free_basic_resources();

    return 0;
}


bool create_display(ALLEGRO_DISPLAY *display){
    //criando uma janela com a resoluçao do desktop do usuario (fullscreen):
    ALLEGRO_MONITOR_INFO info;

    int res_x, res_y;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_get_monitor_info(0, &info);

    res_x = info.x2 - info.x1;
    res_y = info.y2 - info.y1;


    display = al_create_display(res_x, res_y);
    if(!display){
        fprintf(stderr, "Error: could not create display.\n");
        return false;
    }

    //redimensionando o jogo para se encaixar na resoluçao do desktop do usuario:

    float red_x = res_x/(float)gDISPLAYw;
    float red_y = res_y/(float)gDISPLAYh;

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, red_x, red_y);
    al_use_transform(&transform);

    al_register_event_source(eventQ, al_get_display_event_source(display));

    return true;

}


bool init_basic_resources(void){

    if(!al_init()){
        fprintf(stderr, "Error: could not initialize Allegro.\n");
        return false;
    }

    if(!al_init_image_addon()){
        fprintf(stderr, "Error: could not initialize Image Add-on.\n");
        return false;
    }

    if(!al_install_keyboard()){
        fprintf(stderr, "Error: could not initialize Keyboard.\n");
        return false;
    }

    eventQ = al_create_event_queue();
    if(!eventQ){
        fprintf(stderr, "Error: could not create event queue.\n");
        return false;
    }

    timer = al_create_timer(1.0/FPS);
    if(!timer){
        fprintf(stderr, "Error: could not create timer.\n");
        al_destroy_event_queue(eventQ);
        return false;
    }

    //imagem da nave
    ship = al_load_bitmap("image/ship1.bmp");
    if(!ship){
        fprintf(stderr, "Error: could not load ship bitmap.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        return false;
    }
    al_convert_mask_to_alpha(ship, al_map_rgb(255, 255, 255));




    //imagen da bala da nave:
    bimg = al_load_bitmap("image/b.png");
    if(!bimg){
        fprintf(stderr, "Error: could not load bullet bitmap.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        return false;
    }
    al_convert_mask_to_alpha(bimg, al_map_rgb(0,0,0));



    alien1img = al_load_bitmap("image/alien1.png");
    if(!alien1img){
        fprintf(stderr, "Error: could not load alien1 image.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        al_destroy_bitmap(bimg);
        return false;
    }
    al_convert_mask_to_alpha(alien1img, al_map_rgb(0, 0 ,0));


    alien2img = al_load_bitmap("image/alien2.png");
    if(!alien2img){
        fprintf(stderr, "Error: could not load alien2 image.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        al_destroy_bitmap(bimg);
        al_destroy_bitmap(alien1img);
        return false;
    }
    al_convert_mask_to_alpha(alien2img, al_map_rgb(0, 0 ,0));


    alien3img = al_load_bitmap("image/alien3.png");
    if(!alien3img){
        fprintf(stderr, "Error: could not load alien3 bitmap");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        al_destroy_bitmap(bimg);
        al_destroy_bitmap(alien1img);
        al_destroy_bitmap(alien2img);
        return false;
    }
    al_convert_mask_to_alpha(alien3img, al_map_rgb(0, 0 ,0));

    al_register_event_source(eventQ, al_get_keyboard_event_source());
    al_register_event_source(eventQ, al_get_timer_event_source(timer));

    return true;
}

void free_basic_resources(void){
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQ);
    al_destroy_bitmap(ship);
    al_destroy_bitmap(bimg);
    al_destroy_bitmap(alien1img);
    al_destroy_bitmap(alien2img);
    al_destroy_bitmap(alien3img);
}
