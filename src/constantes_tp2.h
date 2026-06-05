#ifndef __CONSTANTES_TP2_H__
#define __CONSTANTES_TP2_H__

#define CANTIDAD_MINIMA_POKEMON 1
#define CANTIDAD_MAXIMA_OBJETIVOS 10
#define PASOS_INICIALES 300
#define MAX_FILAS_TABLERO 9
#define MAX_COLUMNAS_TABLERO 8
#define MAX_FILAS_PANTALLA 5
#define MAX_COLUMNAS_PANTALLA 8
#define MAX_TIPOS_POKEMON 8
#define CANTIDAD_MAXIMA_OPCIONES 3
#define X_PREDETERMINADO 3
#define Y_PREDETERMINADO 4
#define LIMITE_INFERIOR_Y 2
#define LIMITE_SUPERIOR_Y 6

#define COTA_PROBABILIDAD 10
#define AJUSTE_PROBABILIDAD 1
#define PROBABILIDAD_PASTO 4
#define PROBABILIDAD_POKEMON_ESCONDIDO 8
#define PROBABILIDAD_INICIAR_BATALLA 9

#define HOTKEY_SALIDA 'Q'
#define TECLA_MOVER_ARRIBA 'W'
#define TECLA_MOVER_IZQUIERDA 'A'
#define TECLA_MOVER_ABAJO 'S'
#define TECLA_MOVER_DERECHA 'D'
#define TECLA_ELEGIR_PIEDRA 'Z'
#define TECLA_ELEGIR_PAPEL 'X'
#define TECLA_ELEGIR_TIJERA 'C'
#define TECLA_ESCAPAR 'V'

#define FLAG_CONTINUAR_JUEGO 0
#define FLAG_TERMINAR_JUEGO 1
#define SIN_ERRORES 0
#define ERR_ELEGIR_OBJETIVOS -1
#define ERR_ATRAPAR_POKEMON -2
#define ERR_MOSTRAR_OBJETIVOS -3
#define ERR_GRABAR_BATALLA -4
#define ERR_GENERAR_COLUMNAS_INICIALES -5
#define ERR_DESPLAZAR_TABLERO -6
#define ERR_EDITAR_TERRENO -7

#define CARACTER_ESPACIO_VACIO '.'
#define CARACTER_PASTO_COMUN '*'
#define CARACTER_PASTO_PELIGROSO '!'
#define CARACTER_PARED 'P'
#define ICONO_ESPACIO_VACIO "."
#define ICONO_PASTO_COMUN "🞯"
#define ICONO_PASTO_PELIGROSO "🞴"
#define ICONO_JUGADOR "◓"
#define ICONO_PARED "■"
#define NOMBRE_JUGADOR "Ash"

#define FORMATO_IMPRESION_CASILLA "\033[38;5;%im%s\033[0m    "
#define FORMATO_IMPRESION_SEPARADOR_FILAS "\n\n"
#define DIVISOR_UI "------------------------------------\n\n"
#define MSJ_UI_PASOS_RESTANTES "Quedan \033[38;5;%im%i\033[0m pasos."
#define MSJ_UI_OBJETIVO "\n\n\033[38;5;%imObjetivos restantes: \033[0m"
#define MSJ_ALERTA_BATALLA \
	"\033[38;5;%im       ¡SE INICIÓ UNA BATALLA!             \033[0m\n"
#define MSJ_UI_CONTRINCANTES_BATALLA \
	"\033[38;5;%im%s\033[0m vs. \033[38;5;%im%s\033[0m\n\n"
#define MSJ_UI_PROPUESTA_ELECCION \
	"¡Elige una opción!\n\n\033[38;5;%imPIEDRA (%c)\033[0m - \033[38;5;%imPAPEL (%c)\033[0m - \033[38;5;%imTIJERA (%c)\033[0m - \033[38;5;%imESCAPAR (%c)\033[0m\n"
#define MSJ_UI_RESULTADO_VICTORIA "\n¡Atrapado! ¡Ganaste un paso!\n"
#define MSJ_UI_RESULTADO_DERROTA "\nDerrotado... ¡Perdiste dos pasos!\n"
#define MSJ_UI_RESULTADO_EMPATE "\n¡Empate!\n"
#define MSJ_UI_RESULTADO_ESCAPE "\n¡Escapaste!\n"
#define MSJ_UI_RECORD_BATALLA \
	"Batalla %s contra \033[38;5;%im%s\033[0m - Total de turnos: %zu\n"
#define MSJ_UI_RECORD_BATALLA_ESCAPADA \
	"Escapó de \033[38;5;%im%s\033[0m - Total de turnos: %zu \n"
#define MSJ_RESULTADO_BATALLA_GANADA "ganada"
#define MSJ_RESULTADO_BATALLA_PERDIDA "perdida"
#define FONDO_BATALLA "!    !    !    !    !    !    !    !    \n"
#define FORMATO_IMPRESION_OBJETIVOS "%s, "
#define FORMATO_IMPRESION_OBJETIVO_FINAL "%s."
#define MSJ_SALIR_DEL_JUEGO "Saliendo...\n\n"
#define MSJ_SIN_PASOS "¡Se terminó el juego!\n\n"
#define MSJ_GANASTE "Felicidades, ¡¡Ganaste el juego!!\n\n"
#define MSJ_ERROR_LOOP_BATALLAS "Ocurrió un error durante el manejo interno de las batallas. Por favor, vuelva a correr el juego.\n\n"
#define MSJ_ERROR_DESPLAZAR_TABLERO "Ocurrió un error con el manejo del tablero. Por favor, vuelva a correr el juego.\n\n"
#define MSJ_ERROR_MOSTRAR_OBJETIVOS "Ocurrió un error al mostrar los objetivos. Por favor, vuelva a correr el juego.\n\n"

#define MSJ_REGLAS_ENCABEZADO \
	"\033[38;5;%im    ____             __          \n   / __ \\___  ____ _/ /___ ______\n  / /_/ / _ \\/ __ `/ / __ `/ ___/\n / _, _/  __/ /_/ / / /_/ (__  ) \n/_/ |_|\\___/\\__, /_/\\__,_/____/  \n           /____/\033[0m\n"
#define ITEM_REGLA "\n\n\033[38;5;%im-\033[0m"
#define MSJ_REGLA_1 \
	"%s se puede mover con las teclas '%c', '%c' o '%c' e inicia con un total de \033[38;5;%im%i\033[0m pasos. Cada movimiento resta un paso."
#define MSJ_REGLA_2 \
	"Cada casilla del tablero puede estar vacía ( \033[38;5;%im%s\033[0m ), contener pasto común ( \033[38;5;%im%s\033[0m ) o pasto peligroso  ( \033[38;5;%im%s\033[0m )."
#define MSJ_REGLA_3 \
	"Al pisar un casillero de pasto peligroso ( \033[38;5;%im%s\033[0m ), el jugador puede ser \033[38;5;%imatacado por un Pokémon\033[0m , iniciando una batalla."
#define MSJ_REGLA_4 \
	"Al iniciarse una batalla pokemon, se presentará un juego de \033[38;5;%impiedra, papel o tijera\033[0m, con la opción de escapar de la batalla."
#define MSJ_REGLA_5 \
	"Ganar una batalla agrega %i pasos al contador. Además se considerará capturado el Pokémon que haya atacado. En caso de empate se reiniciará la batalla y no cambiará el número de pasos. Si la batalla se pierde, se restarán %i pasos. Si se escapa de la batalla, se restarán %i pasos."
#define MSJ_REGLA_6 \
	"En cualquier caso, luego de finalizar una batalla, el casillero en donde ocurrió \033[38;5;%imno podrá generar más batallas.\033[0m"
#define MSJ_REGLA_7 \
	"El juego finaliza cuando se capturan todos los Pokémon objetivo o no quedan más pasos.\n\n"
#define MSJ_REGLAS_EMPEZAR "\nPresione Enter para empezar."

#define COLOR_PREDETERMINADO 255
#define COLOR_JUGADOR 204
#define COLOR_PASTO 193
#define COLOR_PARED 250

#define LONG_BANNER_BATALLA 8
#define PAUSA_BATALLA 1

#define DEDUCCION_PASOS_ESCAPE 2
#define DEDUCCION_PASOS_DERROTA 4
#define PASOS_EXTRA_VICTORIA 1

#endif // __CONSTANTES_TP2_H__