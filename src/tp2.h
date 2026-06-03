#ifndef __TP2_H__
#define __TP2_H__

#include "tp1.h"

struct juego;

/**
* Crea una nueva instancia de juego a partir de la Pokédex pasada por parámetro.
*
* Devuelve un puntero a la nueva instancia o NULL en caso de error.
*/
struct juego *juego_crear(tp1_t *tp1);

/**
* Inicializa la instancia de juego especificada con la semilla pasada por parámetro.
* Se iniciará con una semilla elegida al azar si esta es 0.
*/
void juego_iniciar(struct juego *juego, unsigned int semilla);

/**
* Destruye la instancia de juego, liberando la memoria que ocupa.
*/
void juego_destruir(struct juego *juego);

#endif // __TP2_H__