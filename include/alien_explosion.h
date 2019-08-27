#ifndef ALIEN_EXPLOSION_H_INCLUDED
#define ALIEN_EXPLOSION_H_INCLUDED

#include "enemies.h"


//logica para ir trocando os sprites da explosao de tempos em tempos.
void update_explosion_alien1 (enemies *p_enemies);

//desenha o sprite atual (selecionado a partir da funcao acima) na tela.
void draw_explosion_alien1(enemies *p_enemies);

//logica para ir trocando os sprites da explosao de tempos em tempos.
void update_explosion_alien2(enemies *p_enemies);

//desenha o sprite atual (selecionado a partir da funcao acima) na tela.
void draw_explosion_alien2(enemies *p_enemies);

//logica para ir trocando os sprites da explosao de tempos em tempos.
void update_explosion_alien3(enemies *p_enemies);

//desenha o sprite atual (selecionado a partir da funcao acima) na tela.
void draw_explosion_alien3(enemies *p_enemies);

#endif // ALIEN_EXPLOSION_H_INCLUDED
