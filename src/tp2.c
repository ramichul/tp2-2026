#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "../extra/engine.h"
#include "lista.h"
#include "tp1.h"
#include "tp2.h"
#include "menu.h"
#include "constantes_tp2.h"

enum resultado_batalla{
    BATALLA_GANADA,
    BATALLA_PERDIDA,
    BATALLA_ESCAPADA
};

struct batalla {
    bool activa;
    struct pokemon *contrincante;
    size_t turnos_de_duracion;
    enum resultado_batalla resultado;
};

struct jugador {
	size_t x;
	size_t y;
    int pasos_restantes;
    struct batalla detalles_batalla;
    lista_t *record_batallas;
};

struct juego {
	struct jugador jugador;
    lista_t *objetivos_elegidos;
    lista_t *columnas_tablero;
    tp1_t *tp1;
};

struct paquete_impresion {
    struct juego *juego;
    size_t indice_a_imprimir;
    size_t cantidad_iteraciones;
};

bool decidir_con_probabilidad(size_t probabilidad){
    return ((rand() % COTA_PROBABILIDAD) + 1) <= probabilidad;
}

bool se_presiono_tecla(int tecla_presionada, char tecla_buscada){
    return tecla_presionada == tecla_buscada || tecla_presionada == tolower(tecla_buscada);
}

int elegir_objetivos(tp1_t *tp1, lista_t *objetivos_elegidos){
    size_t cantidad_pokemon = tp1_cantidad(tp1);
    size_t indices_elegidos[cantidad_pokemon];
    for (int i = 0; i < cantidad_pokemon; i++)
        indices_elegidos[i] = 0;

    for (int i = 0; i < CANTIDAD_MAXIMA_OBJETIVOS; i++){
        size_t indice_elegido = (size_t)rand() % cantidad_pokemon;

        indices_elegidos[indice_elegido] += 1;
    }

    int i = 0;
    bool flag_error_insertar = false;
    while (i < cantidad_pokemon && !flag_error_insertar){
        if (indices_elegidos[i] > 0){
            struct pokemon *pokemon_elegido = tp1_buscar_orden(tp1, i);
            int j = 0;
            while (j < indices_elegidos[i] && !flag_error_insertar){
                lista_t *resultado_insertar = lista_insertar(objetivos_elegidos, pokemon_elegido);
                if (resultado_insertar == NULL)
                    flag_error_insertar = true;
                j++;
            }
        }
        i++;
    }

    if (flag_error_insertar)
        return ERR_ELEGIR_OBJETIVOS;
    return SIN_ERRORES;
}

struct pokemon *elegir_objetivo_al_azar(struct juego juego){
    size_t indice_elegido = (size_t)rand() % lista_cantidad(juego.objetivos_elegidos);

    struct pokemon *pokemon_elegido = lista_obtener_posicion(juego.objetivos_elegidos, indice_elegido);

    return pokemon_elegido;
}

char generar_casillero(){
    char casillero = '\0';

    if (decidir_con_probabilidad(PROBABILIDAD_PASTO)){
        casillero = CARACTER_PASTO_COMUN;
        if (decidir_con_probabilidad(PROBABILIDAD_POKEMON_ESCONDIDO))
            casillero = CARACTER_PASTO_PELIGROSO;
    }
    else{
        casillero = CARACTER_ESPACIO_VACIO;
    }

    return casillero;
}

char *generar_columna(){
    char *nueva_columna = calloc(MAX_FILAS_TABLERO, sizeof(char));
    if (nueva_columna == NULL)
        return NULL;

    for (int i = 0; i < MAX_FILAS_TABLERO; i++){
            if (i < LIMITE_INFERIOR_Y || i > LIMITE_SUPERIOR_Y)
                nueva_columna[i] = CARACTER_PARED;
            else
                nueva_columna[i] = generar_casillero();
    }

    return nueva_columna;
}

bool mostrar_fila(void *_columna_actual, void *_paquete_impresion){
    char *columna_actual = (char *)_columna_actual;
    struct paquete_impresion *paquete_impresion = (struct paquete_impresion *)_paquete_impresion;
    
    if (paquete_impresion->indice_a_imprimir == paquete_impresion->juego->jugador.y && paquete_impresion->cantidad_iteraciones == X_PREDETERMINADO)
        printf(FORMATO_IMPRESION_CASILLA, COLOR_JUGADOR, ICONO_JUGADOR);
    else if (columna_actual[paquete_impresion->indice_a_imprimir] == CARACTER_PASTO_COMUN)
        printf(FORMATO_IMPRESION_CASILLA, COLOR_PASTO, ICONO_PASTO_COMUN);
    else if (columna_actual[paquete_impresion->indice_a_imprimir] == CARACTER_PASTO_PELIGROSO)
        printf(FORMATO_IMPRESION_CASILLA, COLOR_PASTO, ICONO_PASTO_PELIGROSO);
    else if (columna_actual[paquete_impresion->indice_a_imprimir] == CARACTER_PARED)
        printf(FORMATO_IMPRESION_CASILLA, COLOR_PARED, ICONO_PARED);
    else
        printf(FORMATO_IMPRESION_CASILLA, COLOR_PREDETERMINADO, ICONO_ESPACIO_VACIO);

    paquete_impresion->cantidad_iteraciones++;
    return true;
}

void mostrar_mapa(struct juego juego){
    struct paquete_impresion paquete_impresion;
    paquete_impresion.juego = &juego;
    paquete_impresion.indice_a_imprimir = juego.jugador.y - (MAX_FILAS_PANTALLA / 2);
    paquete_impresion.cantidad_iteraciones = 0;

    for (int i = 0; i < MAX_FILAS_PANTALLA; i++){
        lista_con_cada_elemento(juego.columnas_tablero, mostrar_fila, &paquete_impresion);
        printf(FORMATO_IMPRESION_SEPARADOR_FILAS);

        paquete_impresion.cantidad_iteraciones = 0;
        paquete_impresion.indice_a_imprimir++;
    }
}

int mostrar_objetivos(struct juego juego){
    printf(MSJ_UI_OBJETIVO, COLOR_JUGADOR);

    struct pokemon *objetivo_actual;

    lista_iterador_t *iterador = lista_iterador_crear(juego.objetivos_elegidos);
    if (iterador == NULL)
        return ERR_MOSTRAR_OBJETIVOS;
    
    size_t i = 0;
    bool flag_fallo_obtencion = false;
    while (i < lista_cantidad(juego.objetivos_elegidos) - 1 && !flag_fallo_obtencion){
        objetivo_actual = lista_iterador_actual(iterador);

        if (objetivo_actual == NULL){
            flag_fallo_obtencion = true;
        }
        else{
            printf(FORMATO_IMPRESION_OBJETIVOS, objetivo_actual->nombre);
            lista_iterador_avanzar(iterador);
            i++;
        }
    }
    if (!flag_fallo_obtencion){
        objetivo_actual = lista_iterador_actual(iterador);
        printf(FORMATO_IMPRESION_OBJETIVO_FINAL, objetivo_actual->nombre);
    }

    lista_iterador_destruir(iterador);

    if (flag_fallo_obtencion)
        return ERR_MOSTRAR_OBJETIVOS;
    return SIN_ERRORES;
}

void mostrar_alerta_batalla(){
    borrar_pantalla();
    for (int i = 0; i < LONG_BANNER_BATALLA; i++){
        printf(FONDO_BATALLA);
        if (i == (LONG_BANNER_BATALLA / 2) - 1)
            printf(MSJ_ALERTA_BATALLA, COLOR_JUGADOR);
    }
}

int mostrar_ui_exploracion(struct juego juego){
    mostrar_mapa(juego);

    printf(DIVISOR_UI);
    
    if (juego.jugador.pasos_restantes >= 0)
        printf(MSJ_UI_PASOS_RESTANTES, COLOR_JUGADOR, juego.jugador.pasos_restantes);
    else
        printf(MSJ_UI_PASOS_RESTANTES, COLOR_JUGADOR, 0);
    
    if (mostrar_objetivos(juego) == ERR_MOSTRAR_OBJETIVOS)
        return ERR_MOSTRAR_OBJETIVOS;
    return SIN_ERRORES;
}

int desplazar_columnas_tablero(struct juego juego, int tecla_presionada){
    if (!se_presiono_tecla(tecla_presionada, TECLA_MOVER_DERECHA))
        return SIN_ERRORES;

    char *nueva_columna = generar_columna();
    if (nueva_columna == NULL)
        return ERR_DESPLAZAR_TABLERO;
    
    lista_t *resultado_eliminar = lista_eliminar_posicion(juego.columnas_tablero, 0);
    if (resultado_eliminar == NULL){
        free(nueva_columna);
        return ERR_DESPLAZAR_TABLERO;
    }
    free(resultado_eliminar);

    lista_t *resultado_insertar = lista_insertar(juego.columnas_tablero, nueva_columna);
    if (resultado_insertar == NULL){
        free(nueva_columna);
        return ERR_DESPLAZAR_TABLERO;
    }

    return SIN_ERRORES;
}

void logica_de_movimiento(struct juego *juego, int tecla_presionada){
    if (se_presiono_tecla(tecla_presionada, TECLA_MOVER_DERECHA)){
        juego->jugador.x++;
        juego->jugador.pasos_restantes--;
    }
    if (se_presiono_tecla(tecla_presionada, TECLA_MOVER_ARRIBA) && juego->jugador.y != LIMITE_INFERIOR_Y){
        juego->jugador.y--;
        juego->jugador.pasos_restantes--;
    }
    if (se_presiono_tecla(tecla_presionada, TECLA_MOVER_ABAJO) && juego->jugador.y != LIMITE_SUPERIOR_Y){
        juego->jugador.y++;
        juego->jugador.pasos_restantes--;
    }
}

char elegir_opcion_para_pokemon(){
    char opciones[CANTIDAD_MAXIMA_OPCIONES] = {TECLA_ELEGIR_PIEDRA, TECLA_ELEGIR_PAPEL, TECLA_ELEGIR_TIJERA};
    size_t indice_elegido = (size_t)rand() % CANTIDAD_MAXIMA_OPCIONES;

    return opciones[indice_elegido];
}

bool jugador_gano_batalla(char eleccion_jugador, char eleccion_pokemon){
    return (eleccion_jugador == TECLA_ELEGIR_PIEDRA && eleccion_pokemon == TECLA_ELEGIR_TIJERA) || (eleccion_jugador == TECLA_ELEGIR_PAPEL && eleccion_pokemon == TECLA_ELEGIR_PIEDRA) || (eleccion_jugador == TECLA_ELEGIR_TIJERA && eleccion_pokemon == TECLA_ELEGIR_PAPEL);
}

int identificar_pokemon_por_puntero(const void *pokemon_actual, const void *pokemon_buscado){
    if (pokemon_actual == pokemon_buscado)
        return 0;
    return 1;
}

int atrapar_pokemon(struct juego juego){
    size_t indice_pokemon;
    bool pokemon_esta_presente = lista_buscar(juego.objetivos_elegidos, juego.jugador.detalles_batalla.contrincante, identificar_pokemon_por_puntero, &indice_pokemon);

    if (pokemon_esta_presente){
        struct pokemon *pokemon_atrapado = lista_eliminar_posicion(juego.objetivos_elegidos, indice_pokemon);
        
        if (pokemon_atrapado == NULL)
            return ERR_ATRAPAR_POKEMON;

        return SIN_ERRORES;
    }

    return ERR_ATRAPAR_POKEMON;
}

int grabar_batalla(struct juego juego){
    struct batalla *batalla_antigua = calloc(1, sizeof(struct batalla));
    if (batalla_antigua == NULL)
        return ERR_GRABAR_BATALLA;
    
    batalla_antigua->activa = false;
    batalla_antigua->contrincante = juego.jugador.detalles_batalla.contrincante;
    batalla_antigua->turnos_de_duracion = juego.jugador.detalles_batalla.turnos_de_duracion;
    batalla_antigua->resultado = juego.jugador.detalles_batalla.resultado;

    lista_t *resultado_insertar = lista_insertar(juego.jugador.record_batallas, batalla_antigua);
    if (resultado_insertar == NULL)
        return ERR_GRABAR_BATALLA;
    return SIN_ERRORES;
}

void mostrar_ui_batalla(struct juego juego){
    printf(MSJ_UI_CONTRINCANTES_BATALLA, COLOR_JUGADOR, NOMBRE_JUGADOR, COLOR_JUGADOR, juego.jugador.detalles_batalla.contrincante->nombre);
    printf(DIVISOR_UI);
    printf(MSJ_UI_PROPUESTA_ELECCION, COLOR_JUGADOR, TECLA_ELEGIR_PIEDRA, COLOR_JUGADOR, TECLA_ELEGIR_PAPEL, COLOR_JUGADOR, TECLA_ELEGIR_TIJERA, COLOR_JUGADOR, TECLA_ESCAPAR);
}

int loop_batallas(struct juego *juego, int tecla_presionada, struct pokemon *contrincante){
    char eleccion_jugador = '\0';
    bool jugador_eligio_opcion = false;
    bool batalla_concluida = false;

    mostrar_ui_batalla(*juego);

    if (!jugador_eligio_opcion){
        if (se_presiono_tecla(tecla_presionada, TECLA_ELEGIR_PIEDRA)){
            eleccion_jugador = TECLA_ELEGIR_PIEDRA;
            jugador_eligio_opcion = true;
        }
        if (se_presiono_tecla(tecla_presionada, TECLA_ELEGIR_PAPEL)){
            eleccion_jugador = TECLA_ELEGIR_PAPEL;
            jugador_eligio_opcion = true;
        }
        if (se_presiono_tecla(tecla_presionada, TECLA_ELEGIR_TIJERA)){
            eleccion_jugador = TECLA_ELEGIR_TIJERA;
            jugador_eligio_opcion = true;
        }
        if (se_presiono_tecla(tecla_presionada, TECLA_ESCAPAR)){
            batalla_concluida = true;
            juego->jugador.detalles_batalla.resultado = BATALLA_ESCAPADA;
            juego->jugador.detalles_batalla.turnos_de_duracion++;
            juego->jugador.pasos_restantes -= DEDUCCION_PASOS_ESCAPE;
            printf(MSJ_UI_RESULTADO_ESCAPE);
            sleep(PAUSA_BATALLA);
            borrar_pantalla();
        }
    }
    if (jugador_eligio_opcion){
        char eleccion_pokemon = elegir_opcion_para_pokemon();
        juego->jugador.detalles_batalla.turnos_de_duracion++;

        if (eleccion_jugador == eleccion_pokemon){
            printf(MSJ_UI_RESULTADO_EMPATE);
            sleep(PAUSA_BATALLA);
        }
        else if (jugador_gano_batalla(eleccion_jugador, eleccion_pokemon)){
            printf(MSJ_UI_RESULTADO_VICTORIA);
            sleep(PAUSA_BATALLA);
            borrar_pantalla();
            batalla_concluida = true;
            juego->jugador.detalles_batalla.resultado = BATALLA_GANADA;
            juego->jugador.pasos_restantes += PASOS_EXTRA_VICTORIA;

            if (atrapar_pokemon(*juego) == ERR_ATRAPAR_POKEMON)
                return ERR_ATRAPAR_POKEMON;   
        }
        else{
            printf(MSJ_UI_RESULTADO_DERROTA);
            sleep(PAUSA_BATALLA);
            borrar_pantalla();
            batalla_concluida = true;
            juego->jugador.detalles_batalla.resultado = BATALLA_PERDIDA;
            juego->jugador.pasos_restantes -= DEDUCCION_PASOS_DERROTA;
        }
    }

    if (batalla_concluida){
        char *columna_actual = lista_obtener_posicion(juego->columnas_tablero, X_PREDETERMINADO);
        if (columna_actual == NULL)
            return ERR_EDITAR_TERRENO;
        columna_actual[juego->jugador.y] = CARACTER_ESPACIO_VACIO;

        if (grabar_batalla(*juego) == ERR_GRABAR_BATALLA)
            return ERR_GRABAR_BATALLA;
        
        juego->jugador.detalles_batalla.activa = false;
        juego->jugador.detalles_batalla.contrincante = NULL;
        juego->jugador.detalles_batalla.turnos_de_duracion = 0;
    }

    return SIN_ERRORES;
}

bool debo_iniciar_batalla(struct juego juego){
    char *columna_actual = lista_obtener_posicion(juego.columnas_tablero, X_PREDETERMINADO);
    if (columna_actual == NULL)
        return false;
        
    if (columna_actual[juego.jugador.y] == CARACTER_PASTO_PELIGROSO && juego.jugador.pasos_restantes > 0 && lista_cantidad(juego.objetivos_elegidos) > 0 && decidir_con_probabilidad(PROBABILIDAD_INICIAR_BATALLA))
        return true;
    return false;
}

void logica_batallas(struct juego *juego, int tecla_presionada){
    if (debo_iniciar_batalla(*juego)){
        juego->jugador.detalles_batalla.contrincante = elegir_objetivo_al_azar(*juego);
        juego->jugador.detalles_batalla.activa = true;
        mostrar_alerta_batalla();
        sleep(PAUSA_BATALLA);
        borrar_pantalla();
    }
}

int condiciones_de_corte(struct juego juego, int tecla_presionada){
    if (se_presiono_tecla(tecla_presionada, HOTKEY_SALIDA)){
        borrar_pantalla();
        printf(MSJ_SALIR_DEL_JUEGO);
		return FLAG_TERMINAR_JUEGO;
    }
    if (juego.jugador.pasos_restantes <= 0){
        borrar_pantalla();
        printf(MSJ_SIN_PASOS);
        return FLAG_TERMINAR_JUEGO;
    }
    if (lista_cantidad(juego.objetivos_elegidos) == 0){
        borrar_pantalla();
        printf(MSJ_GANASTE);
        return FLAG_TERMINAR_JUEGO;
    }

    return FLAG_CONTINUAR_JUEGO;
}

bool mostrar_record(void *_record_batalla_actual, void *extra){
    struct batalla *record_batalla = (struct batalla *)_record_batalla_actual;

    if (record_batalla->resultado == BATALLA_GANADA)
        printf(MSJ_UI_RECORD_BATALLA, MSJ_RESULTADO_BATALLA_GANADA, COLOR_JUGADOR, record_batalla->contrincante->nombre, record_batalla->turnos_de_duracion);
    else if (record_batalla->resultado == BATALLA_PERDIDA)
        printf(MSJ_UI_RECORD_BATALLA, MSJ_RESULTADO_BATALLA_PERDIDA, COLOR_JUGADOR, record_batalla->contrincante->nombre, record_batalla->turnos_de_duracion);
    else
        printf(MSJ_UI_RECORD_BATALLA_ESCAPADA, COLOR_JUGADOR, record_batalla->contrincante->nombre, record_batalla->turnos_de_duracion);

    return true;
}

void mostrar_record_de_batallas(struct juego juego){
    lista_con_cada_elemento(juego.jugador.record_batallas, mostrar_record, NULL);
}

int logica_del_juego(int tecla_presionada, void *_juego){
    struct juego *juego = _juego;

    if (condiciones_de_corte(*juego, tecla_presionada) == FLAG_TERMINAR_JUEGO){
        if (lista_cantidad(juego->jugador.record_batallas) > 0)
            mostrar_record_de_batallas(*juego);
        return FLAG_TERMINAR_JUEGO;
    }

    if (juego->jugador.detalles_batalla.activa) {
        if (loop_batallas(juego, tecla_presionada, juego->jugador.detalles_batalla.contrincante) != SIN_ERRORES)
            return FLAG_TERMINAR_JUEGO;
    }
    else {
        logica_de_movimiento(juego, tecla_presionada);
        if (desplazar_columnas_tablero(*juego, tecla_presionada) == ERR_DESPLAZAR_TABLERO)
            return FLAG_TERMINAR_JUEGO;
        if (mostrar_ui_exploracion(*juego) == ERR_MOSTRAR_OBJETIVOS)
            return FLAG_TERMINAR_JUEGO;
        logica_batallas(juego, tecla_presionada);
    }

    return FLAG_CONTINUAR_JUEGO;
}

struct juego *juego_crear(tp1_t *tp1){
    if (tp1 == NULL || tp1_cantidad(tp1) < CANTIDAD_MINIMA_POKEMON)
        return NULL;

    struct juego *juego = calloc(1, sizeof(struct juego));
    if (juego == NULL)
        return NULL;

    juego->jugador.x = X_PREDETERMINADO;
    juego->jugador.y = Y_PREDETERMINADO;
    juego->jugador.pasos_restantes = PASOS_INICIALES;
    juego->jugador.record_batallas = lista_crear();
    if (juego->jugador.record_batallas == NULL){
        free(juego);
        return NULL;
    }

    juego->columnas_tablero = lista_crear();
    if (juego->columnas_tablero == NULL){
        lista_destruir(juego->jugador.record_batallas);
        free(juego);
        return NULL;
    }

    juego->objetivos_elegidos = lista_crear();
    if (juego->objetivos_elegidos == NULL){
        lista_destruir(juego->columnas_tablero);
        lista_destruir(juego->jugador.record_batallas);
        free(juego);
        return NULL;
    }
    if (elegir_objetivos(tp1, juego->objetivos_elegidos) == ERR_ELEGIR_OBJETIVOS){
        lista_destruir(juego->columnas_tablero);
        lista_destruir(juego->jugador.record_batallas);
        lista_destruir(juego->objetivos_elegidos);
        free(juego);
        return NULL;
    }

    juego->tp1 = tp1;

    return juego;
}

int generar_columnas_iniciales(struct juego juego){
    int i = 0;
    bool flag_error_inicializacion = false;

    while (i < MAX_COLUMNAS_TABLERO && !flag_error_inicializacion){
        char *nueva_columna = generar_columna();
        if (nueva_columna == NULL){
            flag_error_inicializacion = true;
        }
        else {
            if (i == X_PREDETERMINADO)
                nueva_columna[Y_PREDETERMINADO] = CARACTER_ESPACIO_VACIO;

            lista_t *resultado_insertar = lista_insertar(juego.columnas_tablero, nueva_columna);
            if (resultado_insertar == NULL)
                flag_error_inicializacion = true;
        }

        i++;
    }

    if (flag_error_inicializacion)
        return ERR_GENERAR_COLUMNAS_INICIALES;
    return SIN_ERRORES;
}

void mostrar_reglas(){
    printf(MSJ_REGLAS_ENCABEZADO, COLOR_JUGADOR);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_1, NOMBRE_JUGADOR, TECLA_MOVER_ARRIBA, TECLA_MOVER_ABAJO, TECLA_MOVER_DERECHA, COLOR_JUGADOR, PASOS_INICIALES);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_2, COLOR_PREDETERMINADO, ICONO_ESPACIO_VACIO, COLOR_PASTO, ICONO_PASTO_COMUN, COLOR_PASTO, ICONO_PASTO_PELIGROSO);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_3, COLOR_PASTO, ICONO_PASTO_PELIGROSO, COLOR_JUGADOR);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_4, COLOR_JUGADOR);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_5, PASOS_EXTRA_VICTORIA, DEDUCCION_PASOS_DERROTA, DEDUCCION_PASOS_ESCAPE);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_6, COLOR_JUGADOR);
    printf(ITEM_REGLA, COLOR_JUGADOR);
    printf(MSJ_REGLA_7);
    printf(MSJ_REGLAS_EMPEZAR);


    fgetc(stdin);
    while(fgetc(stdin) != '\n');

    borrar_pantalla();
}

void juego_iniciar(struct juego *juego, unsigned int semilla){
    if (juego == NULL)
        return;

    if (semilla != 0)
        srand(semilla);
    else
        srand((unsigned int)time(NULL));

    borrar_pantalla();
    esconder_cursor();

    mostrar_reglas();

    if (generar_columnas_iniciales(*juego) == ERR_GENERAR_COLUMNAS_INICIALES)
        return;
    game_loop(logica_del_juego, juego);

    mostrar_cursor();
}

void juego_destruir(struct juego *juego){
    if (juego == NULL)
        return;

    lista_destruir_todo(juego->jugador.record_batallas, free);
    lista_destruir_todo(juego->columnas_tablero, free);
    lista_destruir(juego->objetivos_elegidos);
    free(juego);
}