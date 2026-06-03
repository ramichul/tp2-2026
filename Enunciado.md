<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP2: Integración

Este trabajo pide que el alumno demuestre los conocimientos adquiridos durante la cursada integrando las bibliotecas implementadas a lo largo de la materia. Adicionalmente se pide la creación de un nuevo TDA definido completamente por el alumno.

El trabajo consiste en un simple juego de consola donde el jugador tiene un límite de tiempo para atrapar cierta cantidad de pokemones.

# TDA Menu

Se pide la creación de un TDA Menú lo suficientemente genérico para ser utilizado en cualquier otro TP posible de la materia (o cualquier otro programa). Los requisitos minimos son los siguientes:

- Debe poder manejar multiples opciones definidas por el usuario.
- Debe manejar la lógica de dibujo del mismo menú permitiendo modificar la presentación por el usuario si así lo desea.
- Debe ser abstracto, no debe contener lógica del juego.

# Inicio del programa

Al iniciar el programa se debe leer el archivo de pokedex (**TP1**) pasado como parámetro. El programa no puede iniciar sin dicho archivo. Luego se debe presentar un menú con las siguientes opciones:

- **J**: Iniciar el juego
- **S**: Iniciar el juego con una semilla
- **B**: Buscar en la pokedex
- **Q**: Salir

# Inicio del juego

Al iniciar el juego se crea un listado de 10 pokemon objetvo que debe atrapar el jugador. Estos pokemon son tomados del archivo de pokedex de manera aleatoria pudiendo existir repetidos. Se recomienda que el jugador pueda visualizar en todo momento dicho listado de objetivos restantes durante el juego.

Luego se crea un tablero de 8 x 5 casilleros. El jugador inicia en medio del tablero y puede desplazarse hacia arriba, hacia abajo o hacia la derecha. El juego inicia con una cantidad límite de pasos (300) a dar por el jugador. Una vez llegada a esta cantidad de pasos el juego finaliza.

Cada casillero del tablero tiene un 40% de probabilidad de contener pasto. Cada casillero de pasto tiene 80% de probabilidad de esconder un pokemon. Cada vez que el jugador se posiciona sobre un casillero de pasto que esconde un pokemon, existe un 90% de probabilidad de que se inicie una batalla pokemon. En caso de que no se inicie la batalla, se considera que el pokemon ha escapado y el casillero no volverá a presentar encuentros con pokemones.

Al iniciarse una batalla pokemon, se presenta al usuario un juego de piedra/papel/tijera y la opción de escapar de la batalla. Si el jugador gana la batalla, se considera capturado al pokemon y se gana un paso. Si el jugador pierde se descuentan 4 pasos. Si el jugador empata no cambia la cantidad de pasos pero se debe volver a jugar o escapar. Al escapar se finaliza la batalla y se pierden 2 pasos. Una vez finalizada la batalla (sin importar el resultado), el casillero queda vacante y no es posible tener mas encuentros en el mismo.

El juego finaliza cuando se capturan todos los pokemon objetivos o el jugador se queda sin pasos. Antes de salir se debe mostrar por pantalla la información de cada una de las batallas ocurridas durante el juego, mostrando el resultado: pokemon enfrentado, resultado (ganado, perdido, escapado) y la cantidad de turnos de duración.

Se recomienda dibujar los pastos de diferente forma o color para distinguir el tipo de pokemon que se esconde allí y la presencia o no de pokemones.

# Iniciar con semilla

En caso de iniciar con semilla, se debe pedir al jugador ingresar un número para utilizar para utilizar con **srand** y así inicializar la generación de números aleatorios.

# Buscar

Esta opción debe mostrar un submenú con las opciones **N**, **T** y **V**:

- **N**: Pide que se ingrese un nombre y busca los datos del pokemon en la pokedex
- **T**: Pide un tipo y busca todos los pokemon de dicho tipo en la pokedex
- **V**: Vuelve al menú anterior.

# Engine

Para la elaboración del trabajo se provee **engine.h** y un main de ejemplo. No es obligatorio el uso de estos archivos y se deja a discreción del alumno la utilización. Recordar que NO se permite la utilización de bibliotecas externas (ncurses o similares).

---

## Puntos teóricos

- Explicar y justificar las estructuras y tdas utilizados para implementar las diferentes partes del juego.
- Explicar las decisiones tomadas para la creación del TDA Menú (justificar datos y operaciones que lo conforman). Explicar cómo funciona
- No hace falta decirlo a esta altura, pero hagan diagramas para explicar.
