#include "engine.h"
#include "ansi.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

//Este archivo está por separado del resto del proyecto porque no es C99 puro.
//Entonces lo compilamos por separado con otros flags.
//Esperemos que funcione para todos 👀
//No tomen este archivo como buen ejemplo de nada. Lo usamos simplemente para
//facilitarles el manejo de la consola y las entradas de teclado sin tener que
//complicarnos con ncurses o similar (que sería la decisión correcta para algo serio).

static int old_flags;

static struct termios inicializar_consola()
{
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);

	return oldt;
}

static void restaurar_consola(struct termios oldt)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, old_flags);
}

static int proxima_tecla()
{
	unsigned char c[20];
	int n = read(STDIN_FILENO, c, 20);

	if (n == -1) {
		return 0;
	}

	if (c[0] == 27 && n >= 3 && c[1] == 91) {
		switch (c[2]) {
		case 65:
			return TECLA_ARRIBA;
		case 66:
			return TECLA_ABAJO;
		case 67:
			return TECLA_DERECHA;
		case 68:
			return TECLA_IZQUIERDA;
		}
	}

	return c[0];
}

void borrar_pantalla()
{
	printf(ANSI_CURSOR_HOME ANSI_CLEAR_TO_END);
}

void resetear_consola()
{
	printf(ANSI_RESET_SCREEN);
}

void esconder_cursor()
{
	printf(ANSI_HIDE_CURSOR);
}

void mostrar_cursor()
{
	printf(ANSI_SHOW_CURSOR);
}

void game_loop(int (*callback)(int, void *), void *data)
{
	int input = 0;
	int result = 0;
	struct termios oldt = inicializar_consola();
	esconder_cursor();
	do {
		input = proxima_tecla();
		printf(ANSI_CURSOR_HOME);
		result = callback(input, data);
		printf(ANSI_CLEAR_TO_END);
		usleep(200000);
	} while (result == 0);
	mostrar_cursor();
	restaurar_consola(oldt);
}
