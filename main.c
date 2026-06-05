#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "src/menu.h"
#include "src/tp1.h"
#include "src/tp2.h"
#include "src/diccionario.h"
#include "constantes_main.h"

int inicializar_menus(menu_t **menu_principal, menu_t **menu_buscar)
{
	*menu_principal =
		menu_crear(NOMBRE_SALIR_PRINCIPAL, HOTKEY_SALIR_PRINCIPAL);
	if (*menu_principal == NULL)
		return ERR_INICIALIZACION_MENU;
	*menu_buscar = menu_crear(NOMBRE_SALIR_BUSQUEDA, HOTKEY_SALIR_BUSQUEDA);
	if (*menu_buscar == NULL) {
		menu_destruir(*menu_principal);
		return ERR_INICIALIZACION_MENU;
	}

	char *nombres_opciones[MAX_OPCIONES_MENU] = {
		NOMBRE_JUGAR, NOMBRE_JUGAR_CON_SEMILLA, NOMBRE_BUSCAR,
		NOMBRE_BUSCAR_NOMBRE, NOMBRE_BUSCAR_TIPO
	};
	char hotkeys_opciones[MAX_OPCIONES_MENU] = {
		HOTKEY_JUGAR, HOTKEY_JUGAR_CON_SEMILLA, HOTKEY_BUSCAR,
		HOTKEY_BUSCAR_NOMBRE, HOTKEY_BUSCAR_TIPO
	};
	menu_t *submenus[MAX_OPCIONES_MENU] = { NULL, NULL, *menu_buscar, NULL,
						NULL };

	int i = 0;
	bool flag_fallo_agregar = false;
	while (i < MAX_OPCIONES_MENU && !flag_fallo_agregar) {
		menu_t *resultado_agregar;

		if (i < CANT_OPCIONES_MENU_PRINCIPAL)
			resultado_agregar = menu_agregar_opcion(
				*menu_principal, nombres_opciones[i],
				hotkeys_opciones[i], submenus[i]);
		else
			resultado_agregar = menu_agregar_opcion(
				*menu_buscar, nombres_opciones[i],
				hotkeys_opciones[i], submenus[i]);

		if (resultado_agregar == NULL) {
			flag_fallo_agregar = true;
		}

		i++;
	}
	if (flag_fallo_agregar) {
		menu_destruir(*menu_principal);
		menu_destruir(*menu_buscar);
		return ERR_INICIALIZACION_MENU;
	}

	menu_personalizar_tipografia(*menu_principal, TITULO_PRINCIPAL,
				     MARCADOR_OPCION, PROPUESTA_OPCION);
	menu_personalizar_tipografia(*menu_buscar, TITULO_BUSQUEDA,
				     MARCADOR_OPCION, PROPUESTA_OPCION);

	size_t colores[MAX_COLORES] = { COLOR_TITULO, COLOR_OPCIONES,
					COLOR_MARCADOR,
					COLOR_PROPUESTA_OPCION };
	menu_personalizar_colores(*menu_principal, colores);
	menu_personalizar_colores(*menu_buscar, colores);

	return SIN_ERRORES;
}

void imprimir_pokemon(struct pokemon *pokemon)
{
	char *nombres_completos_tipos[] = {
		NOMBRE_TIPO_ELECTRICO, NOMBRE_TIPO_FUEGO,  NOMBRE_TIPO_PLANTA,
		NOMBRE_TIPO_AGUA,      NOMBRE_TIPO_NORMAL, NOMBRE_TIPO_FANTASMA,
		NOMBRE_TIPO_PSIQUICO,  NOMBRE_TIPO_LUCHA
	};

	printf(MSJ_DATOS, pokemon->nombre,
	       nombres_completos_tipos[pokemon->tipo], pokemon->ataque,
	       pokemon->defensa, pokemon->velocidad);
}

bool mostrar_pokemon_por_tipo(struct diccionario_par *par_actual,
			      void *_tipo_buscado)
{
	struct pokemon *pokemon_actual = (struct pokemon *)par_actual->valor;
	enum tipo_pokemon *tipo_buscado = (enum tipo_pokemon *)_tipo_buscado;

	if (pokemon_actual->tipo == *tipo_buscado)
		imprimir_pokemon(pokemon_actual);
	return true;
}

int ejecutar_comando_iniciar_juego(menu_t *menu, char entrada_usuario,
				   tp1_t *tp1)
{
	char *semilla_leida = NULL;
	struct juego *juego = juego_crear(tp1);
	if (juego == NULL)
		return ERR_INICIAR_JUEGO;

	if (entrada_usuario == (char)tolower(HOTKEY_JUGAR)) {
		juego_iniciar(juego, 0);
	} else {
		semilla_leida =
			menu_leer_entrada(menu, PROPUESTA_INGRESAR_SEMILLA);
		unsigned long semilla = strtoul(semilla_leida, NULL, 0);

		if (semilla > __UINT32_MAX__) {
			printf(MSJ_AVISO_SEMILLA_MUY_GRANDE);
			semilla = 0;
		}

		free(semilla_leida);

		juego_iniciar(juego, (unsigned int)semilla);
	}

	juego_destruir(juego);
	return SIN_ERRORES;
}

void ejecutar_comando_buscar_nombre(menu_t *menu, diccionario_t *diccionario)
{
	char *nombre_buscado =
		menu_leer_entrada(menu, PROPUESTA_INGRESAR_NOMBRE);

	struct pokemon *pokemon_buscado =
		diccionario_obtener(diccionario, nombre_buscado);

	if (pokemon_buscado != NULL)
		imprimir_pokemon(pokemon_buscado);
	else
		printf(MSJ_AVISO_POKEMON_NO_PRESENTE);

	free(nombre_buscado);
}

int identificar_id_tipo(const char *tipo)
{
	char tipos_validos[MAX_TIPOS][MAX_NOM_TIPO] = {
		ABREVIACION_ELECTRICO, ABREVIACION_FUEGO,  ABREVIACION_PLANTA,
		ABREVIACION_AGUA,      ABREVIACION_NORMAL, ABREVIACION_FANTASMA,
		ABREVIACION_PSIQUICO,  ABREVIACION_LUCHA
	};

	int i = 0;
	int id_tipo = -1;
	bool buscando = true;

	if (tipo == NULL)
		return id_tipo;

	while (buscando && i < MAX_TIPOS) {
		if (strcmp(tipos_validos[i], tipo) == 0) {
			id_tipo = i;
			buscando = false;
		}
		i++;
	}

	return id_tipo;
}

void ejecutar_comando_buscar_tipo(menu_t *menu, diccionario_t *diccionario)
{
	char *tipo_buscado = menu_leer_entrada(menu, PROPUESTA_INGRESAR_TIPO);
	enum tipo_pokemon id_tipo = identificar_id_tipo(tipo_buscado);
	size_t cantidad_de_pokemon_mostrados = 0;

	if (id_tipo != -1)
		cantidad_de_pokemon_mostrados = diccionario_con_cada_elemento(
			diccionario, mostrar_pokemon_por_tipo, &id_tipo);
	if (cantidad_de_pokemon_mostrados == 0)
		printf(MSJ_AVISO_TIPO_NO_PRESENTE);

	free(tipo_buscado);
}

void ejecutar_comando_busqueda(menu_t *menu, char entrada_usuario,
			       diccionario_t *diccionario)
{
	if (entrada_usuario == (char)tolower(HOTKEY_BUSCAR_NOMBRE))
		ejecutar_comando_buscar_nombre(menu, diccionario);
	else
		ejecutar_comando_buscar_tipo(menu, diccionario);
}

bool usuario_eligio_jugar(char entrada_usuario)
{
	return entrada_usuario == (char)tolower(HOTKEY_JUGAR) ||
	       entrada_usuario == (char)tolower(HOTKEY_JUGAR_CON_SEMILLA);
}

int ejecutar_comandos(menu_t *menu, char entrada_usuario[MAX_PROFUNDIDAD_MENU],
		      size_t conteo_entradas_capturadas,
		      diccionario_t *diccionario, tp1_t *tp1)
{
	if (usuario_eligio_jugar(entrada_usuario[0])) {
		if (ejecutar_comando_iniciar_juego(menu, entrada_usuario[0],
						   tp1) == ERR_INICIAR_JUEGO)
			return ERR_EJECUTAR_COMANDOS;
	} else if (conteo_entradas_capturadas == 2) {
		ejecutar_comando_busqueda(menu, entrada_usuario[1],
					  diccionario);
	}

	return SIN_ERRORES;
}

bool cargar_pokemon_en_diccionario(struct pokemon *pokemon, void *_diccionario)
{
	diccionario_t *diccionario = (diccionario_t *)_diccionario;

	return diccionario_insertar(diccionario, pokemon->nombre, pokemon,
				    NULL) == diccionario;
}

int rellenar_diccionario(tp1_t *tp1, diccionario_t *diccionario)
{
	size_t cantidad_pokemones_insertados = tp1_con_cada_pokemon(
		tp1, cargar_pokemon_en_diccionario, diccionario);

	if (cantidad_pokemones_insertados != tp1_cantidad(tp1))
		return ERR_RELLENAR_DICCIONARIO;
	return SIN_ERRORES;
}

int main(int argc, char *argv[])
{
	if (argc != CANT_VALIDA_ARGUMENTOS) {
		printf(MSJ_INSTRUCCIONES);
		return ERR_ARGUMENTOS;
	}

	tp1_t *tp1 = tp1_leer_archivo(argv[INDICE_ARGUMENTO_ARCHIVO]);
	if (tp1 == NULL) {
		printf(MSJ_ERR_LECTURA);
		return ERR_LECTURA;
	}
	if (tp1_cantidad(tp1) == 0) {
		printf(MSJ_AVISO_POKEDEX_VACIA);
		tp1_destruir(tp1);
		return ERR_LECTURA;
	}

	diccionario_t *diccionario = diccionario_crear(tp1_cantidad(tp1));
	if (diccionario == NULL) {
		printf(MSJ_ERR_DICCIONARIO);
		tp1_destruir(tp1);
		return ERR_DICCIONARIO;
	}
	if (rellenar_diccionario(tp1, diccionario) ==
	    ERR_RELLENAR_DICCIONARIO) {
		printf(MSJ_ERR_RELLENAR_DICCIONARIO);
		diccionario_destruir(diccionario);
		tp1_destruir(tp1);
		return ERR_RELLENAR_DICCIONARIO;
	}

	menu_t *menu_principal = NULL;
	menu_t *menu_buscar = NULL;
	if (inicializar_menus(&menu_principal, &menu_buscar) ==
	    ERR_INICIALIZACION_MENU) {
		printf(MSJ_ERR_INICIALIZACION_MENU);
		diccionario_destruir(diccionario);
		tp1_destruir(tp1);
		return ERR_INICIALIZACION_MENU;
	}

	char entrada_usuario[MAX_PROFUNDIDAD_MENU] = { '\0', '\0' };
	size_t conteo_entradas_capturadas = 0;
	menu_iniciar(menu_principal, entrada_usuario,
		     &conteo_entradas_capturadas);

	if (ejecutar_comandos(menu_principal, entrada_usuario,
			      conteo_entradas_capturadas, diccionario,
			      tp1) == ERR_EJECUTAR_COMANDOS)
		return ERR_EJECUTAR_COMANDOS;

	menu_destruir_todo(menu_principal);
	diccionario_destruir(diccionario);
	tp1_destruir(tp1);
	return SIN_ERRORES;
}