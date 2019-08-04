#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>


#include "main.h"

//funçoes basicas:
bool init_basic_resources(void);
void free_basic_resources(void);

bool create_display(ALLEGRO_DISPLAY *display);

int main(void){

    //iniciando os recursos basicos do programa:
    if(!init_basic_resources())
        return -1;

    //criando uma janela para o programa:
    if(!create_display(display))
        return -1;


    //inicializando objetos do programa{

       //nave do jogador:
       Initship(&Pship);

       //balas do jogador:
       Initbullet(bullets, NUM_BULLETS);

       //inimigos 1 linha:
       InitAlien1(alien1, NUM_ALIEN);

       //inimigos 2 e 3 linha:
       InitAlien2(alien2, 2);

       //inimigos 4 e 5 linha:
       InitAlien3(alien3, 2);

       Init_aBullet();
   //}


    //iniciando o timer de atualizaçao de display(atualiza a tela 60x/seg):
    al_start_timer(timer);


    exitl = false;

    //loop principal do programa:
    while(!exitl){
        //esperando aparecer um evento para podermos trata-lo:
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQ, &event);

        //lidando devidamente com o evento gerado:
        deal_with_events(&event);

        if(redraw && al_is_event_queue_empty(eventQ)){ //caso o evento seja gerado pelo timer e a fila de eventos estiver vazia atualizamos a tela.
                                                    //(como o timer gera 60 eventos por segundo atualizamos a tela do programa nessa frequencia)
            al_clear_to_color(al_map_rgb(0,0,0));

            drawShip(&Pship, ship);
            drawBullet(bullets, NUM_BULLETS, bimg);

            draw_alien1(alien1img, alien1, NUM_ALIEN);
            draw_alien2(alien2img, alien2, 2);
            draw_alien3(alien3img, alien3, 2);

            draw_explosion_alien1();
            draw_explosion_alien2();
            draw_explosion_alien3();

            draw_aBullet();

            al_flip_display();
        }

    }

    free_basic_resources();

    return 0;
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
    ship = al_load_bitmap("images/ship1.bmp");
    if(!ship){
        fprintf(stderr, "Error: could not load ship bitmap.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        return false;
    }
    al_convert_mask_to_alpha(ship, al_map_rgb(255, 255, 255));




    //imagem da bala da nave:
    bimg = al_load_bitmap("images/b.png");
    if(!bimg){
        fprintf(stderr, "Error: could not load bullet bitmap.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        return false;
    }
    al_convert_mask_to_alpha(bimg, al_map_rgb(0,0,0));


    //imagem dos aliens da 1 fileira:
    alien1img = al_load_bitmap("images/alien1.png");
    if(!alien1img){
        fprintf(stderr, "Error: could not load alien1 image.\n");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        al_destroy_bitmap(bimg);
        return false;
    }
    al_convert_mask_to_alpha(alien1img, al_map_rgb(0, 0 ,0));

    //imagem dos aliens da 2 e 3 fileira:
    alien2img = al_load_bitmap("images/alien2.png");
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

    //imagem dos aliens da 4 e 5 fileira:
    alien3img = al_load_bitmap("images/alien3.png");
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

    //imagem da explosao dos aliens:
    exp_img = al_load_bitmap("images/exp.png");
    if(!exp_img){
        fprintf(stderr, "Error: could not load explosion bitmap");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        al_destroy_bitmap(bimg);
        al_destroy_bitmap(alien1img);
        al_destroy_bitmap(alien2img);
        al_destroy_bitmap(alien3img);
        return false;
    }
    al_convert_mask_to_alpha(exp_img, al_map_rgb(0, 0 , 0));

    //imagem da bala dos aliens:
    alien_bullet_img = al_load_bitmap("images/alienshot.png");
    if(!alien_bullet_img){
        fprintf(stderr, "Error: could not load alien bullet bitmap");
        al_destroy_event_queue(eventQ);
        al_destroy_timer(timer);
        al_destroy_bitmap(ship);
        al_destroy_bitmap(bimg);
        al_destroy_bitmap(alien1img);
        al_destroy_bitmap(alien2img);
        al_destroy_bitmap(alien3img);
        al_destroy_bitmap(exp_img);
        return false;
    }
    al_convert_mask_to_alpha(alien_bullet_img, al_map_rgb(0, 0 , 0));



    //ligando as fontes de eventos do teclado e do timer a fila de eventos criada:
    al_register_event_source(eventQ, al_get_keyboard_event_source());
    al_register_event_source(eventQ, al_get_timer_event_source(timer));


    //variavel usada para atualizar a tela(redesenhar objetos):
    redraw = true;

    return true;
}

void free_basic_resources(void){
    //liberando os recursos usados no programa:
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQ);
    al_destroy_bitmap(ship);
    al_destroy_bitmap(bimg);
    al_destroy_bitmap(alien1img);
    al_destroy_bitmap(alien2img);
    al_destroy_bitmap(alien3img);
    al_destroy_bitmap(exp_img);
    al_destroy_bitmap(alien_bullet_img);

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
