#include "pa2m.h"
#include "../src/menu.h"
#include "../src/tp1.h"
#include "../src/tp2.h"
#include <stdio.h>

void menu_crear_no_intenta_crear_con_nombre_de_opcion_nulo()
{
	char *nombre = NULL;
	char hotkey = 'A';

	menu_t *menu = menu_crear(nombre, hotkey);

	pa2m_afirmar(
		menu == NULL,
		"menu_crear() no intenta crear un nuevo menú dado un nombre nulo para la opción de salida");

	menu_destruir(menu);
}

void menu_crear_no_intenta_crear_con_hotkey_para_opcion_nulo()
{
	char *nombre = "Opción";
	char hotkey = '\0';

	menu_t *menu = menu_crear(nombre, hotkey);

	pa2m_afirmar(
		menu == NULL,
		"menu_crear() no intenta crear un nuevo menú dado un hotkey nulo para la opción de salida");
}

void menu_crear_crea_un_menu_dado_parametros_validos()
{
	char *nombre = "Opción";
	char hotkey = 'A';

	menu_t *menu = menu_crear(nombre, hotkey);

	pa2m_afirmar(menu != NULL,
		     "menu_crear() crea un nuevo menú dado parámetros válidos");

	menu_destruir(menu);
}

void menu_agregar_opcion_devuelve_mismo_menu_al_agregar_con_exito()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_agregar == menu,
		"menu_agregar_opcion() devuelve un puntero al mismo menú al agregar con éxito");

	menu_destruir(menu);
}

void menu_agregar_opcion_devuelve_null_al_fallar()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = NULL;
	char hotkey_nueva_opcion = 'B';
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_agregar == NULL,
		"menu_agregar_opcion() devuelve un puntero nulo al fallar");

	menu_destruir(menu);
}

void menu_agregar_opcion_no_intenta_agregar_a_menu_nulo()
{
	menu_t *menu = NULL;

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(resultado_agregar == NULL,
		     "menu_agregar_opcion() no intenta agregar a un menú nulo");

	menu_destruir(menu);
}

void menu_agregar_opcion_no_intenta_agregar_con_nombre_de_opcion_nulo()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = NULL;
	char hotkey_nueva_opcion = 'B';
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_agregar == NULL,
		"menu_agregar_opcion() no intenta agregar una nueva opción dado un nombre nulo para ella");

	menu_destruir(menu);
}

void menu_agregar_opcion_no_intenta_agregar_con_hotkey_para_opcion_nulo()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = '\0';
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_agregar == NULL,
		"menu_agregar_opcion() no intenta agregar una nueva opción dado un hotkey nulo para ella");

	menu_destruir(menu);
}

void menu_agregar_opcion_agrega_opcion_sin_submenu()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_t *submenu = NULL;
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, submenu);

	pa2m_afirmar(
		resultado_agregar == menu,
		"menu_agregar_opcion() agrega una nueva opción sin un submenú asociado");

	menu_destruir(menu);
}

void menu_agregar_opcion_agrega_opcion_con_submenu()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);
	menu_t *submenu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_t *resultado_agregar = menu_agregar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, submenu);

	pa2m_afirmar(
		resultado_agregar == menu,
		"menu_agregar_opcion() agrega una nueva opción con un submenú asociado");

	menu_destruir_todo(menu);
}

void menu_eliminar_opcion_devuelve_mismo_menu_al_eliminar_con_exito()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_agregar_opcion(menu, nombre_nueva_opcion, hotkey_nueva_opcion,
			    NULL);
	menu_t *resultado_eliminar = menu_eliminar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_eliminar == menu,
		"menu_eliminar_opcion() devuelve un puntero al mismo menú al eliminar con éxito");

	menu_destruir(menu);
}

void menu_eliminar_opcion_devuelve_null_al_fallar()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = NULL;
	char hotkey_nueva_opcion = '\0';
	menu_t *resultado_eliminar = menu_eliminar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_eliminar == NULL,
		"menu_eliminar_opcion() devuelve un puntero nulo al fallar");

	menu_destruir(menu);
}

void menu_eliminar_opcion_no_intenta_eliminar_de_menu_nulo()
{
	menu_t *menu = NULL;

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_t *resultado_eliminar = menu_eliminar_opcion(
		menu, nombre_nueva_opcion, hotkey_nueva_opcion, NULL);

	pa2m_afirmar(
		resultado_eliminar == NULL,
		"menu_eliminar_opcion() no intenta eliminar en un menú nulo");

	menu_destruir(menu);
}

void menu_eliminar_opcion_no_intenta_eliminar_opcion_de_salida()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	menu_t *resultado_eliminar = menu_eliminar_opcion(
		menu, nombre_opcion_de_salida, hotkey_opcion_de_salida, NULL);

	pa2m_afirmar(
		resultado_eliminar == NULL,
		"menu_eliminar_opcion() no intenta eliminar la opción de salida");

	menu_destruir(menu);
}

void menu_eliminar_opcion_no_intenta_eliminar_opcion_no_presente()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_opcion_no_presente = "Opción no presente";
	char hotkey_opcion_no_presente = 'B';
	menu_t *resultado_eliminar =
		menu_eliminar_opcion(menu, nombre_opcion_no_presente,
				     hotkey_opcion_no_presente, NULL);

	pa2m_afirmar(
		resultado_eliminar == NULL,
		"menu_eliminar_opcion() no intenta eliminar una opción no presente");

	menu_destruir(menu);
}

void menu_eliminar_opcion_no_intenta_eliminar_opcion_que_coincide_en_nombre_pero_no_en_hotkey()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_opcion_no_presente = "Nueva opción";
	menu_t *resultado_eliminar = menu_eliminar_opcion(
		menu, nombre_opcion_no_presente, 'A', NULL);

	pa2m_afirmar(
		resultado_eliminar == NULL,
		"menu_eliminar_opcion() no intenta eliminar una opción que coincide en nombre pero no en hotkey");

	menu_destruir(menu);
}

void menu_eliminar_opcion_no_intenta_eliminar_opcion_que_coincide_en_hotkey_pero_no_en_nombre()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char hotkey_opcion_no_presente = 'B';
	menu_t *resultado_eliminar = menu_eliminar_opcion(
		menu, "Opción", hotkey_opcion_no_presente, NULL);

	pa2m_afirmar(
		resultado_eliminar == NULL,
		"menu_eliminar_opcion() no intenta eliminar una opción que coincide en hotkey pero no en nombre");

	menu_destruir(menu);
}

void menu_eliminar_opcion_elimina_opcion_y_devuelve_submenu_asociado()
{
	char *nombre_opcion_de_salida = "Opción";
	char hotkey_opcion_de_salida = 'A';
	menu_t *menu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);
	menu_t *submenu =
		menu_crear(nombre_opcion_de_salida, hotkey_opcion_de_salida);

	char *nombre_nueva_opcion = "Nueva opción";
	char hotkey_nueva_opcion = 'B';
	menu_t *submenu_asociado = NULL;
	menu_agregar_opcion(menu, nombre_nueva_opcion, hotkey_nueva_opcion,
			    submenu);
	menu_eliminar_opcion(menu, nombre_nueva_opcion, hotkey_nueva_opcion,
			     &submenu_asociado);

	pa2m_afirmar(
		submenu_asociado == submenu,
		"menu_eliminar_opcion() elimina una opción y devuelve su submenú asociado por parámetro si es pedido");

	menu_destruir(menu);
	menu_destruir(submenu);
}

void juego_crear_no_intenta_crear_a_partir_de_tp1_nulo()
{
	tp1_t *tp1 = NULL;

	struct juego *juego = juego_crear(tp1);

	pa2m_afirmar(
		juego == NULL,
		"juego_crear() no intenta crear una nueva instancia de juego a partir de una Pokédex nula");
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación del menú");
	menu_crear_no_intenta_crear_con_nombre_de_opcion_nulo();
	menu_crear_no_intenta_crear_con_hotkey_para_opcion_nulo();
	menu_crear_crea_un_menu_dado_parametros_validos();

	pa2m_nuevo_grupo("Pruebas de manipulación de opciones");
	menu_agregar_opcion_devuelve_mismo_menu_al_agregar_con_exito();
	menu_agregar_opcion_devuelve_null_al_fallar();
	menu_agregar_opcion_no_intenta_agregar_a_menu_nulo();
	menu_agregar_opcion_no_intenta_agregar_con_nombre_de_opcion_nulo();
	menu_agregar_opcion_no_intenta_agregar_con_hotkey_para_opcion_nulo();
	menu_agregar_opcion_agrega_opcion_sin_submenu();
	menu_agregar_opcion_agrega_opcion_con_submenu();
	menu_eliminar_opcion_devuelve_mismo_menu_al_eliminar_con_exito();
	menu_eliminar_opcion_devuelve_null_al_fallar();
	menu_eliminar_opcion_no_intenta_eliminar_de_menu_nulo();
	menu_eliminar_opcion_no_intenta_eliminar_opcion_de_salida();
	menu_eliminar_opcion_no_intenta_eliminar_opcion_no_presente();
	menu_eliminar_opcion_no_intenta_eliminar_opcion_que_coincide_en_nombre_pero_no_en_hotkey();
	menu_eliminar_opcion_no_intenta_eliminar_opcion_que_coincide_en_hotkey_pero_no_en_nombre();
	menu_eliminar_opcion_elimina_opcion_y_devuelve_submenu_asociado();

	pa2m_nuevo_grupo("Pruebas de creación de instancia de juego");
	juego_crear_no_intenta_crear_a_partir_de_tp1_nulo();

	return pa2m_mostrar_reporte();
}
