#ifndef MENU_H_
#define MENU_H_

#include "constantes_menu.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct menu menu_t;

typedef struct opcion {
	char *nombre;
	char hotkey;
	menu_t *submenu;
} opcion_t;

/**
* Crea un nuevo menú, junto con su opción de salida.
*
* Devuelve un puntero a la nueva estructura o NULL en caso de error.
*/
menu_t *menu_crear(char *nombre, char hotkey);

/**
* Agrega una opción simple o un submenú adicional al menú.
*
* Devuelve un puntero al mismo menú o NULL en caso de error.
*/
menu_t *menu_agregar_opcion(menu_t *menu, char *nombre, char hotkey,
			    menu_t *submenu);

/**
* Elimina una opción del menú.
* Si la opción tenía un submenú asociado, opcionalmente devolverá un puntero a ese submenú por parámetro.
*
* Devuelve un puntero al mismo menú o NULL en caso de error.
*/
menu_t *menu_eliminar_opcion(menu_t *menu, char *nombre, char hotkey,
			     menu_t **submenu_asociado);

/**
* Permite agregar un titulo al menú, cambiar el marcador que se muestra antes de cada opción y cambiar el mensaje de ingreso de opciones que se muestra al usuario.
* No se cambiará la opción si el valor es nulo.
*/
void menu_personalizar_tipografia(menu_t *menu, char *titulo_menu,
				  char *marcador_opcion,
				  char *propuesta_opcion);

/**
* Permite cambiar los colores del título, opciones, el marcador y el mensaje de opción en ese orden.
* Recibe códigos de escape ANSI (0 a 255).
*/
void menu_personalizar_colores(menu_t *menu, size_t colores[MAX_COLORES]);

/**
* Muestra el menú por pantalla y captura los hotkeys ingresados por el usuario (sin distinguir entre minúsculas y mayúsculas).
* Inserta la entrada del usuario en el arreglo pasado por parámetro (en forma secuencial) y modifica conteo_entradas_capturadas con su tope.
* Se espera que la capacidad del vector sea mayor o igual a la profundidad máxima del menú.
* Solo captura la entrada si la opción elegida no es la opción de salída.
*/
void menu_iniciar(menu_t *menu, char *hotkeys_capturadas,
		  size_t *conteo_entradas_capturadas);

/**
* Muestra la propuesta de entrada de cadena por pantalla y captura lo ingresado por el usuario.
*
* Devuelve un string conteniendo la entrada que se deberá liberar despues de ser usado, o NULL en caso de error.
*/
char *menu_leer_entrada(menu_t *menu, char *propuesta_entrada);

/**
* Destruye el menú y sus opciones, preservando los submenús asociados.
*/
void menu_destruir(menu_t *menu);

/**
* Destruye el menú y sus opciones, junto con los submenús asociados.
*/
void menu_destruir_todo(menu_t *menu);

#endif // MENU_H_