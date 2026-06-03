#ifndef __CONSTANTES_MAIN_H__
#define __CONSTANTES_MAIN_H__

#define MAX_OPCIONES_MENU 5
#define CANT_OPCIONES_MENU_PRINCIPAL 3
#define MAX_PROFUNDIDAD_MENU 2

#define NOMBRE_JUGAR "Jugar"
#define NOMBRE_JUGAR_CON_SEMILLA "Jugar con semilla"
#define NOMBRE_BUSCAR "Buscar en la Pokédex"
#define NOMBRE_BUSCAR_NOMBRE "Buscar Pokémon con nombre"
#define NOMBRE_BUSCAR_TIPO "Mostrar Pokémon por tipo"
#define NOMBRE_SALIR_PRINCIPAL "Salir"
#define NOMBRE_SALIR_BUSQUEDA "Volver al menú anterior"

#define HOTKEY_JUGAR 'J'
#define HOTKEY_JUGAR_CON_SEMILLA 'S'
#define HOTKEY_BUSCAR 'B'
#define HOTKEY_BUSCAR_NOMBRE 'N'
#define HOTKEY_BUSCAR_TIPO 'T'
#define HOTKEY_SALIR_PRINCIPAL 'Q'
#define HOTKEY_SALIR_BUSQUEDA 'V'

#define TITULO_PRINCIPAL "   ______      __          __                    __        ____        __    __                        __\n  / ____/___  / /__  _____/ /_____  _____   ____/ /__     / __ \\____  / /___/_/ ____ ___  ____  ____  / /\n / /   / __ \\/ / _ \\/ ___/ __/ __ \\/ ___/  / __  / _ \\   / /_/ / __ \\/ //_/ _ \\/ __ `__ \\/ __ \\/ __ \\/ / \n/ /___/ /_/ / /  __/ /__/ /_/ /_/ / /     / /_/ /  __/  / ____/ /_/ / ,< /  _ ́/ / / / / / /_/ / / / /_/  \n\\____/\\____/_/\\___/\\___/\\__/\\____/_/      \\__,_/\\___/  /_/    \\____/_/|_|\\___/_/ /_/ /_/\\____/_/ /_(_)   \n"
#define TITULO_BUSQUEDA "    ____                            \n   / __ )__  ________________ ______\n  / __  / / / / ___/ ___/ __ `/ ___/\n / /_/ / /_/ (__  ) /__/ /_/ / /    \n/_____/\\__,_/____/\\___/\\__,_/_/     \n                                    "
#define MARCADOR_OPCION "▢"
#define PROPUESTA_OPCION "Ingrese una opción:"

#define COLOR_TITULO 204
#define COLOR_OPCIONES 256
#define COLOR_MARCADOR 204
#define COLOR_PROPUESTA_OPCION 256

#define CANT_VALIDA_ARGUMENTOS 2
#define MAX_NOMBRE_POKEMON 101
#define MAX_TIPOS 8
#define MAX_NOM_TIPO 5

#define SIN_ERRORES 0
#define ERR_INICIALIZACION_MENU -1
#define ERR_ARGUMENTOS -2
#define ERR_LECTURA -3
#define ERR_DICCIONARIO -4
#define ERR_RELLENAR_DICCIONARIO -5
#define ERR_INICIAR_JUEGO -6
#define ERR_EJECUTAR_COMANDOS -7

#define NOMBRE_TIPO_ELECTRICO "⚡Eléctrico"
#define NOMBRE_TIPO_FUEGO "🔥Fuego"
#define NOMBRE_TIPO_PLANTA "🌿Planta"
#define NOMBRE_TIPO_AGUA "💧Agua"
#define NOMBRE_TIPO_NORMAL "⬜Normal"
#define NOMBRE_TIPO_FANTASMA "👻Fantasma"
#define NOMBRE_TIPO_PSIQUICO "👁️‍🗨️Psíquico"
#define NOMBRE_TIPO_LUCHA "✊Lucha"
#define ABREVIACION_ELECTRICO "ELEC"
#define ABREVIACION_FUEGO "FUEG"
#define ABREVIACION_PLANTA "PLAN"
#define ABREVIACION_AGUA "AGUA"
#define ABREVIACION_NORMAL "NORM"
#define ABREVIACION_FANTASMA "FANT"
#define ABREVIACION_PSIQUICO "PSI"
#define ABREVIACION_LUCHA "LUCH"

#define MSJ_INSTRUCCIONES "El modo de uso es \033[38;5;223m./tp2 [nombre del archivo]\033[0m.\n\nVuelva a correr el programa por terminal, asegurándose de utilizar la estructura indicada.\n\n"
#define MSJ_ERR_LECTURA "\033[38;5;202;1mERROR\033[0m: Ocurrió un error al leer el archivo. Por favor, vuelva a intentar. Se debe incluír la extensión del archivo al ejecutar el programa.\n"
#define MSJ_ERR_DICCIONARIO "\033[38;5;202;1mERROR\033[0m: Ocurrió un error al crear el diccionario. Por favor, vuelva a intentar.\n"
#define MSJ_ERR_RELLENAR_DICCIONARIO "\033[38;5;202;1mERROR\033[0m: Ocurrió un error al rellenar el diccionario. Por favor, vuelva a intentar.\n"
#define MSJ_ERR_INICIALIZACION_MENU "\033[38;5;202;1mERROR\033[0m: Ocurrió un error al inicializar los menús. Por favor, vuelva a intentar.\n"
#define MSJ_AVISO_SEMILLA_MUY_GRANDE "\033[38;5;222;1mAVISO\033[0m: La semilla ingresada excede el rango máximo. Se inicializará el juego con un semilla elegida al azar.\n\n"
#define MSJ_AVISO_POKEMON_NO_PRESENTE "\033[38;5;222;1mAVISO\033[0m: El Pokémon buscado no está presente en la Pokédex.\n\n" 
#define MSJ_AVISO_TIPO_NO_PRESENTE "\033[38;5;222;1mAVISO\033[0m: No hay Pokémon del tipo buscado en la Pokédex.\n\n" 
#define MSJ_AVISO_POKEDEX_VACIA "\033[38;5;222;1mAVISO\033[0m: La Pokédex cargada desde el archivo está vacía. Se terminará la ejecución del programa."
#define MSJ_DATOS "\n\033[38;5;223;1mDATOS DEL POKÉMON: \n\033[0m\033[38;5;223mNOMBRE:\033[0m %s\n\033[38;5;223mTIPO:\033[0m %s\n\033[38;5;223mATAQUE:\033[0m %i\n\033[38;5;223mDEFENSA:\033[0m %i\n\033[38;5;223mVELOCIDAD:\033[0m %i\n"

#define PROPUESTA_INGRESAR_NOMBRE "\nIngrese el nombre del Pokémon a buscar:"
#define PROPUESTA_INGRESAR_TIPO "\nIngrese el nombre del tipo a buscar (ELEC, FUEG, PLAN, AGUA, NORM, FANT, PSI, LUCH):"
#define PROPUESTA_INGRESAR_SEMILLA "\nIngrese la semilla con la que desea jugar:"

#endif // __CONSTANTES_MAIN_H__