#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "menu.h"
#include "constantes_menu.h"
#include "lista.h"

struct menu {
    lista_t *listado_opciones;
    struct paquete_personalizacion *paquete_personalizacion;
    menu_t *menu_anterior;
};

typedef struct opcion {
	char *nombre;
	char hotkey;
    menu_t *submenu;
} opcion_t;

struct paquete_personalizacion {
    char *titulo_menu;
    char *marcador_opcion;
    char *propuesta_opcion;
    size_t colores[MAX_COLORES];
};

enum componente_menu {
    TITULO,
    OPCION,
    MARCADOR,
    PROPUESTA_OPCION,
};

opcion_t *inicializar_opcion(char *nombre, char hotkey, menu_t *submenu){
    opcion_t *nueva_opcion = calloc(1, sizeof(opcion_t));
    if (nueva_opcion == NULL){
        return NULL;
    }
    nueva_opcion->nombre = nombre;
    nueva_opcion->hotkey = hotkey;
    nueva_opcion->submenu = submenu;

    return nueva_opcion;
}

int buscar_hotkey(const void *_opcion_actual, const void *_hotkey){
    opcion_t *opcion_actual = (opcion_t *)_opcion_actual;
    char *hotkey = (char *)_hotkey;

    if (tolower(opcion_actual->hotkey) == tolower(*hotkey)){
        return 0;
    }
    return -1;
}

bool opciones_son_iguales(opcion_t opcion_1, opcion_t opcion_2){
    return opcion_1.hotkey == opcion_2.hotkey && strcmp(opcion_1.nombre, opcion_2.nombre) == 0;
}

int buscar_opcion(const void *_opcion_actual, const void *_opcion_auxiliar_para_busqueda){
    opcion_t *opcion_actual = (opcion_t *)_opcion_actual;
    opcion_t *opcion_auxiliar_para_busqueda = (opcion_t *)_opcion_auxiliar_para_busqueda;

    if (opciones_son_iguales(*opcion_actual, *opcion_auxiliar_para_busqueda)){
        return 0;
    }
    return -1;
}

menu_t *menu_crear(char *nombre, char hotkey){
    if (nombre == NULL || hotkey == '\0')
        return NULL;

    menu_t *nuevo_menu = calloc(1, sizeof(menu_t));
    if (nuevo_menu == NULL)
        return NULL;

    nuevo_menu->listado_opciones = lista_crear();
    if (nuevo_menu->listado_opciones == NULL){
        free(nuevo_menu);
        return NULL;
    }

    nuevo_menu->paquete_personalizacion = calloc(1, sizeof(struct paquete_personalizacion));
    if (nuevo_menu->paquete_personalizacion == NULL){
        lista_destruir(nuevo_menu->listado_opciones);
        free(nuevo_menu);
        return NULL;
    }
    for (int i = 0; i < MAX_COLORES; i++)
        nuevo_menu->paquete_personalizacion->colores[i] = VALOR_PREDETERMINADO_COLOR;

    opcion_t *opcion_de_salida = inicializar_opcion(nombre, hotkey, NULL);
    if (opcion_de_salida == NULL){
        lista_destruir(nuevo_menu->listado_opciones);
        free(nuevo_menu->paquete_personalizacion);
        free(nuevo_menu);
        return NULL;
    }

    lista_t *resultado_insertar = lista_insertar(nuevo_menu->listado_opciones, opcion_de_salida);
    if (resultado_insertar != nuevo_menu->listado_opciones){
        lista_destruir(nuevo_menu->listado_opciones);
        free(nuevo_menu->paquete_personalizacion);
        free(nuevo_menu);
        free(opcion_de_salida);
        return NULL;
    }

    return nuevo_menu;
}

menu_t *menu_agregar_opcion(menu_t *menu, char *nombre, char hotkey, menu_t *submenu){
    if (menu == NULL || nombre == NULL || hotkey == '\0')
        return NULL;
    if (submenu == menu){
        return NULL;
    }

    opcion_t *nueva_opcion = inicializar_opcion(nombre, hotkey, submenu);
    if (nueva_opcion == NULL)
        return NULL;
    if (submenu != NULL)
        submenu->menu_anterior = menu;

    lista_t *resultado_insertar = lista_insertar_posicion(menu->listado_opciones, lista_cantidad(menu->listado_opciones) - 1, nueva_opcion);
    if (resultado_insertar != menu->listado_opciones){
        free(nueva_opcion);
        return NULL;
    }

    return menu;
}

menu_t *menu_eliminar_opcion(menu_t *menu, char *nombre, char hotkey, menu_t **submenu_asociado){
    if (menu == NULL || nombre == NULL || hotkey == '\0'){
        return NULL;
    }
    
    opcion_t *opcion_de_salida = lista_obtener(menu->listado_opciones);
    size_t indice_opcion = 0;

    opcion_t opcion_auxiliar_para_busqueda;
    opcion_auxiliar_para_busqueda.nombre = nombre;
    opcion_auxiliar_para_busqueda.hotkey = hotkey;

    bool opcion_es_valida = lista_buscar(menu->listado_opciones, &opcion_auxiliar_para_busqueda, buscar_opcion, &indice_opcion);
    if (!opcion_es_valida)
        return NULL;

    opcion_t *opcion_a_eliminar = lista_obtener_posicion(menu->listado_opciones, indice_opcion);
    if (opcion_a_eliminar == opcion_de_salida)
        return NULL;

    opcion_a_eliminar = lista_eliminar_posicion(menu->listado_opciones, indice_opcion);
    if (opcion_a_eliminar == NULL)
        return NULL;

    if (opcion_a_eliminar->submenu != NULL){
        if (submenu_asociado == NULL){
            menu_destruir(opcion_a_eliminar->submenu);
        }
        else{
            *submenu_asociado = opcion_a_eliminar->submenu;
        }
    }

    free(opcion_a_eliminar);
    return menu;
}

void menu_personalizar_tipografia(menu_t *menu, char *titulo_menu, char *marcador_opcion, char *propuesta_opcion){
    if (menu == NULL){
        return;
    }

    if (titulo_menu != NULL){
        menu->paquete_personalizacion->titulo_menu = titulo_menu;
    }
    if (marcador_opcion != NULL){
        menu->paquete_personalizacion->marcador_opcion = marcador_opcion;
    }
    if (propuesta_opcion != NULL){
        menu->paquete_personalizacion->propuesta_opcion = propuesta_opcion;
    }
}

void menu_personalizar_colores(menu_t *menu, size_t colores[MAX_COLORES]){
    if (menu == NULL ){
        return;
    }

    for (size_t j = 0; j < MAX_COLORES; j++){
        if (colores[j] < VALOR_PREDETERMINADO_COLOR){
            menu->paquete_personalizacion->colores[j] = colores[j];
        }
    }
} 

void agregar_color(struct paquete_personalizacion *paquete_personalizacion, enum componente_menu componente_menu){
    if (paquete_personalizacion->colores[componente_menu] != VALOR_PREDETERMINADO_COLOR){
            printf(FORMATO_IMPRESION_COLOR, paquete_personalizacion->colores[componente_menu]);
    }
}

void imprimir_con_color(struct paquete_personalizacion *paquete_personalizacion, enum componente_menu componente_menu, char *formato_impresion, void *componente_1, void *componente_2){
    agregar_color(paquete_personalizacion, componente_menu);

    if (componente_menu == OPCION){
        printf(formato_impresion, componente_1, *((char *)componente_2));
        return;
    }

    if (componente_2 == NULL)
        printf(formato_impresion, componente_1);
    else
        printf(formato_impresion, componente_1, componente_2);
}

bool imprimir_opcion(void *_opcion_actual, void *_paquete_personalizacion){
    opcion_t *opcion_actual = (opcion_t *)_opcion_actual;
    struct paquete_personalizacion *paquete_personalizacion = (struct paquete_personalizacion *)_paquete_personalizacion;

    if (paquete_personalizacion->marcador_opcion != NULL){
        imprimir_con_color(paquete_personalizacion, MARCADOR, FORMATO_IMPRESION_MARCADOR, paquete_personalizacion->marcador_opcion, NULL);
    }

    imprimir_con_color(paquete_personalizacion, OPCION, FORMATO_IMPRESION_OPCION, opcion_actual->nombre, &opcion_actual->hotkey);
    
    return true;
}

void mostrar_menu_por_pantalla(menu_t *menu){
    system("clear");

    if (menu->paquete_personalizacion->titulo_menu != NULL){
        imprimir_con_color(menu->paquete_personalizacion, TITULO, FORMATO_IMPRESION_TITULO, menu->paquete_personalizacion->titulo_menu, NULL);
    }

    lista_con_cada_elemento(menu->listado_opciones, imprimir_opcion, menu->paquete_personalizacion);

    if (menu->paquete_personalizacion->propuesta_opcion != NULL){
            imprimir_con_color(menu->paquete_personalizacion, PROPUESTA_OPCION, FORMATO_IMPRESION_MENSAJE_DE_OPCION, menu->paquete_personalizacion->propuesta_opcion, NULL);
    }
}

void capturar_hotkeys(menu_t *menu, char *hotkeys_capturadas, size_t *conteo_entradas_capturadas){
    char hotkey_ingresada;
    bool hotkey_es_valida = false;
    size_t indice_opcion;
    opcion_t *opcion_de_salida = lista_obtener(menu->listado_opciones);

    do {
        mostrar_menu_por_pantalla(menu);
        scanf(FORMATO_LECTURA_HOTKEY, &hotkey_ingresada);

        hotkey_es_valida = lista_buscar(menu->listado_opciones, &hotkey_ingresada, buscar_hotkey, &indice_opcion);
    } while (!hotkey_es_valida);

    if (tolower(hotkey_ingresada) == tolower(opcion_de_salida->hotkey)){
        if (menu->menu_anterior != NULL){
            (*conteo_entradas_capturadas)--;
            hotkeys_capturadas[*conteo_entradas_capturadas] = '\0';
            menu_iniciar(menu->menu_anterior, hotkeys_capturadas, conteo_entradas_capturadas);
        }
    }
    else {
        hotkeys_capturadas[*conteo_entradas_capturadas] = (char)tolower(hotkey_ingresada);
        (*conteo_entradas_capturadas)++;

        opcion_t *opcion_elegida = lista_obtener_posicion(menu->listado_opciones, indice_opcion);
        if (opcion_elegida->submenu != NULL)
            menu_iniciar(opcion_elegida->submenu, hotkeys_capturadas, conteo_entradas_capturadas);
    }
}

void menu_iniciar(menu_t *menu, char *hotkeys_capturadas, size_t *conteo_entradas_capturadas){
    if (menu == NULL || hotkeys_capturadas == NULL || conteo_entradas_capturadas == NULL){
        return;
    }

    capturar_hotkeys(menu, hotkeys_capturadas, conteo_entradas_capturadas);
}

bool se_puede_continuar_la_lectura(bool flag_fallo_memoria, char leido){
    return !flag_fallo_memoria && leido != '\n';
}

char *menu_leer_entrada(menu_t* menu, char *propuesta_entrada)
{
	char *buffer = calloc(1, TAM_INICIAL_BUFFER * sizeof(char));
	if (buffer == NULL)
		return NULL;
	char *puntero_aux_buffer = NULL;
	unsigned long tam_actual_buffer = TAM_INICIAL_BUFFER;

    imprimir_con_color(menu->paquete_personalizacion, PROPUESTA_OPCION, FORMATO_IMPRESION_PROPUESTA_INGRESO_DE_CADENA, propuesta_entrada, NULL);

	int i = 0;
	char leido = (char)fgetc(stdin);

    if (leido == '\n'){
        leido = (char)fgetc(stdin);
    }

	bool flag_fallo_memoria = false;
	while (se_puede_continuar_la_lectura(flag_fallo_memoria, leido)){
		buffer[i] = (char)leido;
		i++;

		if (i >= tam_actual_buffer) {
			tam_actual_buffer *= AJUSTE_TAM_BUFFER;
			puntero_aux_buffer = realloc(buffer, tam_actual_buffer * sizeof(char));
			if (puntero_aux_buffer == NULL)
				flag_fallo_memoria = true;
			else
				buffer = puntero_aux_buffer;
		}

		leido = (char)fgetc(stdin);
	}
	if (flag_fallo_memoria){
        free(buffer);
		return NULL;
    }

	buffer[i] = '\0';

	return buffer;
}

bool destruir_menus(void *_opcion_actual, void *_destruir_submenus){
    opcion_t *opcion_actual = (opcion_t *)_opcion_actual;
    bool *destruir_submenus = (bool *)_destruir_submenus;
    menu_t *puntero_auxiliar_submenu = opcion_actual->submenu;

    free(opcion_actual);
    if (puntero_auxiliar_submenu != NULL && *destruir_submenus){
        menu_destruir(puntero_auxiliar_submenu);
    }

    return true;
}

void destructor_menu(menu_t *menu, bool destruir_submenus){
    lista_con_cada_elemento(menu->listado_opciones, destruir_menus, &destruir_submenus);
    lista_destruir(menu->listado_opciones);
    free(menu->paquete_personalizacion);
    free(menu);
}

void menu_destruir(menu_t *menu){
    if (menu == NULL){
        return;
    }

    destructor_menu(menu, false);
}

void menu_destruir_todo(menu_t *menu){
    if (menu == NULL){
        return;
    }
    
    destructor_menu(menu, true);
}