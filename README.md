# TP2
## Información del estudiante

* **Nombre y Apellido**: Ramiro Carrattini
* **Padrón**: 113212
* **Mail**: ramirocarrattini@gmail.com / rcarrattini@fi.uba.ar

## 1. Instrucciones
### 1.1. Compilar el proyecto
```bash
make tp2
make pruebas_tp2
```

### 1.2. Ejecutar las pruebas
```bash
./tp2 [archivo]
./pruebas_tp2
```

### 1.3. Ejecutar el programa con Valgrind
```bash
valgrind ./tp2 [archivo]
valgrind ./pruebas_tp2
```

&nbsp;

## 2. Funcionamiento
### Primitivas y funcionamiento interno (Menú)
#### Creación

**`menu_crear()`**: Crea un nuevo menú, junto con su opción de salida. Devuelve un puntero a la nueva estructura o NULL en caso de error.

Internamente, esta primitiva reserva memoria para el nuevo menú y su opción de salida e inserta dicha opción en él.

#### Inserción

**`menu_agregar_opcion()`**: Agrega una opción simple o un submenú adicional al menú. Devuelve un puntero al mismo menú o NULL en caso de error.

Simplemente reserva memoria para la nueva opción y la inserta en el menú, justo antes de la opción de salida y luego de la última opción insertada.

#### Eliminación

**`menu_eliminar_opcion()`**: Elimina una opción del menú. Si la opción tenía un submenú asociado, opcionalmente devolverá un puntero a ese submenú por parámetro. Devuelve un puntero al mismo menú o NULL en caso de error.

Valida que la opción exista dentro del menú especificado. Si la opción existe, se quita del menú y se libera la memoria que ocupaba. Finalmente, devuelve un puntero al submenú asociado a la opción eliminada según lo que haya pedido el usuario.

#### Personalización

**`menu_personalizar_tipografia()`**: Permite agregar un título al menú, cambiar el marcador que se muestra antes de cada opción y cambiar el mensaje de ingreso de opciones que se muestra al usuario. No se cambiará la opción si el valor es nulo.

Esto es exactamente lo que hace con los valores de `paquete_personalizacion`.

**`void menu_personalizar_colores()`**: Permite cambiar los colores del título, opciones, el marcador y el mensaje de opción en ese orden. Recibe códigos de escape ANSI (0 a 255).

#### Lectura de entrada

**`void menu_iniciar()`**: Muestra el menú por pantalla y captura los hotkeys ingresados por el usuario (sin distinguir entre minúsculas y mayúsculas). Inserta la entrada del usuario en el arreglo pasado por parámetro (en forma secuencial) y modifica `conteo_entradas_capturadas` con su tope.

Por su complejidad y llamados recursivos, se considera más didáctico ilustrar el funcionamiento de esta función con un diagrama:

![Diagrama de funcionamiento de menu_iniciar()](https://i.imgur.com/foMnxoS.png)

**`char *menu_leer_entrada()`**: Muestra la propuesta de entrada de cadena por pantalla y captura lo ingresado por el usuario. Devuelve un string conteniendo la entrada que se deberá liberar después de ser usado, o NULL en caso de error.

La entrada se inserta en un buffer que se va escalando continuamente hasta poder contener a la línea completa. Se lee a partir del teclado hasta recibir la tecla `Enter`.

#### Destrucción

**`void menu_destruir()`**: Destruye el menú y sus opciones, preservando los submenús asociados.

**`void menu_destruir_todo()`**: Destruye el menú y sus opciones, junto con los submenús asociados.

Ambas primitivas funcionan de la misma manera: liberan la memoria que corresponde al menú, a cada submenú (si es pedido) y a sus opciones. Luego de finalizar este proceso se libera la memoria ocupada por el resto de las estructuras que componen al menú.

### Primitivas y funcionamiento interno (Juego)
#### Creación

**`struct juego *juego_crear()`**: Crea una nueva instancia de juego a partir de la Pokédex pasada por parámetro. Devuelve un puntero a la nueva instancia o NULL en caso de error.

Internamente, reserva memoria para la estructura principal y todos sus componentes. Luego, elige los diez objetivos al azar desde la Pokédex.

#### Destrucción

**`void juego_destruir()`**: Destruye la instancia de juego, liberando la memoria que ocupa.

Libera la memoria que ocupa cada batalla grabada (ya que se requirió hacer una copia del nombre del Pokémon). Luego, libera la memoria que ocupaba la estructura principal y sus componentes.

#### Funcionamiento

**`void juego_iniciar`**: Inicializa la instancia de juego especificada con la semilla pasada por parámetro. Se iniciará con una semilla elegida al azar si esta es 0.

Lo primero que se hace es mostrar las reglas por pantalla. Luego de que el usuario haya apretado la tecla *Enter*, se iniciará el juego.

![Reglas del juego](https://i.imgur.com/NysMEFm.png)

El juego no inicializa todo el tablero a la vez, ya que una partida puede ser potencialmente infinita. Por esto, se optó por generar columnas a medida que el jugador las descubre. Entonces, lo primero que se hace es rellenar las 8 columnas iniciales que ve el jugador al principio del juego (asegurándose de no agregar un casillero donde podría ocurrir una batalla en el punto de partida).

Finalizado esto, inicia el juego. Las diferentes acciones y chequeos que se realizan para cada fotograma, en orden, son las siguientes:

- **Chequeo de condiciones de corte**: El juego terminará si se presionó la tecla de salida, no le quedan pasos al jugador, se han capturado todos los Pokémon objetivo o si se reportó un error desde otra función.

- **Loop de batallas**: Si se detecta que el jugador está en una batalla, mostrará la *UI* correspondiente y hará lo siguiente:

  1. Analiza la entrada del usuario para determinar la opción elegida (Piedra/Papel/Tijera/Escapar).
  2. Una vez elegida una opción válida, se elige una opción para el Pokémon al azar y se determina el resultado de la batalla.
  3. Si la batalla resultó en un empate, se iniciará este proceso desde cero, sumando un turno a la duración de la batalla.
  4. Si el jugador ganó la batalla, se "atrapará" al contrincante, eliminándolo de la lista de objetivos.
  5. Una vez concluida la batalla, se quitará el pasto del espacio, se grabará en el récord y se borrarán los campos relevantes de la estructura para que se utilicen en la siguiente ocasión.

Las siguientes funciones se ejecutan si el jugador no está en una batalla actualmente:

- **Lógica de movimiento**: Detecta si la entrada del usuario corresponde con una de las teclas de movimiento, actualizando su posición dentro de la estructura correspondiente.

- **Rellenado de nuevos casilleros**: Como moverse a la derecha implica dibujar una nueva columna del mapa, se quita el primer elemento de la lista de columnas (que se sabe que ya no es ni será visible) y se genera una nueva en tiempo real.

- **Impresión de la *UI* por pantalla**: Muestra todos los casilleros en una ventana de 8x5 con su símbolo y color correspondiente según el carácter leído desde las columnas. Además, imprime un contador de pasos restantes y muestra los objetivos restantes por pantalla.

- **Lógica de batallas**: Decide si un jugador debe ser atacado por un Pokémon. Inicia una batalla y muestra una alerta por pantalla si este es el caso.

Al finalizar el juego, se le mostrarán todas las batallas grabadas al usuario con su resultado, contrincante y duración respectivos.

### Flujo del programa de prueba implementado

Se implementó un programa con ayuda de la estructura de Pokédex (detallada en [este directorio](https://github.com/ramichul/tp1-2026)) para comprobar el buen funcionamiento y las capacidades del menú y el juego. Su funcionamiento es el siguiente (dando por sentado que el programa se abortará cuando haya sucedido un error):

1. Antes de buscar, se parsean los argumentos. En este proceso se detecta una cantidad inválida de argumentos. Si el archivo es inválido o la Pokédex está vacía, esto se detectará más adelante por las estructuras.
2. Una vez validados los argumentos, se crea la Pokédex y se extraen los datos desde el archivo pasado por línea de comando. Si al finalizar la Pokédex está vacía, se le avisará de esto al usuario y no se seguirán procesando los datos.
3. Se inicializa el resto de las estructuras requeridas (diccionario y menús).
4. Se ejecutan una de 4 opciones:
   - Si el usuario eligió buscar por nombre, se buscará el Pokémon pedido en el diccionario. Una vez obtenido, se imprimen sus datos por pantalla. Si el Pokémon no fue encontrado, se le avisa de esto al usuario.
   - Si la búsqueda es por tipo, se recorrerá el diccionario identificando los Pokémon uno por uno, imprimiendo sus datos por pantalla si son del tipo buscado.
   - Si el usuario eligió jugar, se inicializará el juego con o sin una semilla predeterminada según la entrada.
5. Se libera la memoria utilizada y se termina la ejecución del programa.


## 3. Estructuras
#### Menú
Es el TDA implementado para el proyecto. Almacena cada opción en un TDA Lista (cuyo funcionamiento está detallado en [este directorio](https://github.com/ramichul/tplista-2026)). Cuenta además con funcionalidades de personalización para el usuario, almacenadas en el *Paquete de personalización*.

#### Opción
Es el componente principal del menú. Siempre tiene un nombre y *hotkey* asociado. Al momento de ser utilizado, el usuario distinguirá y accederá a las opciones por su *hotkey*.

Podrá tener un submenú asociado, el cual se mostrará por pantalla si se elige la opción al momento de ejecutar el programa.

#### Paquete de personalización
Almacena el título del menú, el marcador que se muestra antes de cada opción y el mensaje de ingreso de opciones que se muestra al usuario, junto con los colores para estos componentes.

#### Juego (*Colector de Pokémon!*)
Es la estructura principal de la cúal se leen todos los datos del juego. Contiene los datos del jugador, un listado de objetivos elegidos (almacenados en un TDA Lista), una lista de columnas que representa el tablero, y un puntero a una Pokédex de donde se sacan los Pokémon objetivo.

#### Jugador
Almacena la posición actual en coordenadas cartesianas, los pasos restantes, los detalles de la última batalla o la batalla actual, y un récord de batallas (también almacenados en un TDA Lista).

#### Batalla
Se utiliza tanto para la batalla actual como para documentar batallas pasadas en el récord de batallas. Contiene un booleano que indica si está activa actualmente, un puntero a Pokémon que simboliza el contrincante, un conteo para la duración de la batalla en turnos, y un resultado que se almacena mediante un *enum*.

## 3.1. Diagrama de memoria

Se adjunta una visualización de las diferentes estructuras que componen el menú en memoria:

![Diagrama de las estructuras del menú en memoria](https://i.imgur.com/UxbCkcR.png)

Se pueden ver las diferentes estructuras del juego en memoria en el siguiente gráfico:

![Diagrama de las estructuras del juego en memoria](https://i.imgur.com/brTCmgp.png)

## 3.2. Análisis de complejidades

### Complejidades temporales (Menú)
Las comparaciones entre los nombres de las opciones se suponen constantes para estos análisis.

Se deberá tener [el repositorio de lista](https://github.com/ramichul/tplista-2026) como referencia para las complejidades de primitivas externas.

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `menu_crear()`       |  $O(n)$   |Si falla la reserva de memoria en algún paso, se deberá llamar a `lista_destruir()`, la cual es $O(n)$. Cabe notar que en un caso común la creación es $O(1)$.|
|      `menu_agregar_opcion()`       |  $O(n)$   |Se utiliza `lista_insertar_posicion()`, una función $O(n)$.|
|      `menu_eliminar_opcion()`       |  $O(n)$ |Se utiliza `lista_buscar()`, `lista_obtener_posicion()` y `lista_eliminar_posicion()`, todas funciones $O(n)$.|
|      `menu_personalizar_tipografia()`       |  $O(1)$ |Asignación de valores simple.|
|      `menu_personalizar_colores()`       |  $O(1)$ |Asignación de valores simple.|
|      `menu_iniciar()`       |  $O(n)$ |Utiliza `lista_buscar()` para la validación de hotkeys.|
|      `menu_leer_entrada()`       |$O(n)$|Detallado más abajo.|
|      `menu_destruir()`       |  $O(n)$ |Llama a `lista_con_cada_elemento()` y a `lista_destruir()`, ambas $O(n)$.|
|      `menu_destruir_todo()`       |  $O(n²)$ |Deberá destruir las $n$ opciones de los $n$ submenús.|

[Este proyecto](https://github.com/ramichul/tp1-2026) utiliza un mecanismo de lectura idéntico a `menu_leer_entrada()`, con la mínima diferencia de que lee a partir de una cadena existente en vez de la entrada del teclado. Se puede ver la justificación de su complejidad en el siguiente recorte:

> Se invoca la función $O(1)$ `fgetc` una vez por cada carácter de una línea de $n$ carácteres. Para comprobar que la cota final es $O(n)$, necesito comprobar que el trabajo que realiza `realloc` durante la lectura no excede esa cota.

> Se sabe que `realloc` se invocará $log_2(n)$ veces durante toda la lectura, ya que el tamaño del buffer se duplica cada vez que se necesita ampliarlo, y que además moverá cada vez más posiciones de la memoria hasta que el bloque contenga a la línea completa. Entonces, matemáticamente, su trabajo es:

> $T(n) = n + \frac{n}{2} + \frac{n}{4} + \frac{n}{8} + ... + 1$

> $T(n) = \sum_{i=0}^{log_2(n)}\frac{n}{2^i}$

> [Se puede verificar](https://www.wolframalpha.com/input?i=sum+n%2F2%5Ei%2C+i%3D0+to+log2%28n%29) que esta sumatoria tiene el resultado:

> $T(n) = 2n - 1$

> Entonces:

> $T(n) \le O(n)$.

> Por lo tanto, la complejidad final de la función entera es $O(n)$.

### Complejidades temporales (Juego)

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `juego_crear()`       |  $O(n)$   |`elegir_objetivos()`, llama a las funciones $O(1)$ `tp1_buscar_orden()` y `lista_insertar()` $n$ veces.|
|      `juego_destruir()`       |  $O(n)$   |Se utiliza `lista_destruir_todo()`, una función $O(n)$.|
|      Chequeo de condiciones de corte       |  $O(1)$   |Son accesos y chequeos simples de valores.|
|      Loop de batallas       |  $O(n)$   |Se utiliza `lista_buscar()` y `lista_eliminar_posicion()`.|
|      Lógica de movimiento       |  $O(1)$   |Acceso y modificación simple de valores.|
|      Rellenado de nuevos casilleros       |  $O(n)$   |Se debe generar una nueva columna.|
|      Impresión del *UI* por pantalla       |  $O(n²)$   |Se debe mostrar la matriz del tablero.|
|      Lógica de batallas       |  $O(n)$   |Se utiliza `lista_obtener_posicion()`|

## 4. Respuestas a las preguntas teóricas
(Hay diagramas de las estructuras más arriba)

#### Explicar y justificar las estructuras y TDAs utilizados para implementar las diferentes partes del juego.
Cuando se estaba pensando en el diseño del juego, se supo que sí o sí se necesitarían varios contenedores para almacenar los diferentes datos (los objetivos, el tablero y el récord de batallas). 

Se descartó la utilización del TDA Diccionario a pesar de su eficiencia para los contenedores, ya que no permite al usuario insertar en una posición específica. Se decidió, en cambio, usar un TDA Lista para ellos por su simplicidad y facilidad de uso. Si bien se podría haber utilizado para el manejo de objetivos (ya que no requiere un orden estricto), se optó por no usarlo para poder mostrarlos en orden alfabético, agruparlos y no desorientar al usuario.

Inicialmente, se había implementado el tablero con una matriz de caracteres: aunque el acceso fácil y directo a los datos ayudó durante el desarrollo, rápidamente resultó ineficiente (principalmente para el desplazamiento de columnas cuando el jugador se mueve a la derecha). Frente a esto, se optó por almacenar las columnas en un TDA Lista para solucionar el problema del desplazamiento, aunque esto no vino sin su contra: se dificultó mucho más el acceso y edición de datos, y se agregaron dificultades mayores a la implementación de `mostrar_mapa()` (imprimir fila por fila es mucho más complejo cuando el mapa está seccionado por columnas). 

Más allá de las dificultades, la implementación del TDA Lista para las columnas resultó muy exitosa en optimizar tanto el funcionamiento del programa como su uso de memoria.

Otras instrucciones del enunciado exigían la existencia de diferentes campos, como los pasos restantes y los detalles de la batalla.

#### Explicar las decisiones tomadas para la creación del TDA Menú (justificar datos y operaciones que lo conforman). Explicar cómo funciona.

La estructura del menú se pensó desde el principio como una lista de opciones, ya que era el contenedor más práctico que también tiene un orden predefinido (no como el diccionario). Se pensó a la opción de salida como un componente obligatorio para el menú, por lo que su inicialización está ligada a su creación.

La decisión de vincular submenús a opciones en vez de diferenciarlos se hizo con la intención principalmente de no saturar el TDA con primitivas y mantenerlo lo menos complicado posible para el usuario. Esta misma decisión es la que influyó en la implementación separada de `menu_leer_entrada()`, ya que su incorporación a la estructura de opción resultaría en dos caminos que se vieron como ineficientes: agregar otra condición más a `menu_agregar_opcion()` (no solo complicando su uso demás sino también el código detrás, especialmente para `menu_iniciar()`), o agregar una primitiva distinta que permita agregar opciones que solo leen entradas.

Para la eliminación de menús, se quiso mantener al TDA flexible y práctico y darle la mayor autonomía posible al usuario, por lo que la opción de destruir o no los submenús asociados queda a su discreción.

Posteriormente, se añadió el paquete de personalización, junto con sus dos primitivas relacionadas. También se buscó lograr un balance entre código y presentación simple sin quitar funcionalidades esenciales. Teniendo en cuenta esto, se decidió permitir al usuario agregar o no un título, un marcador o "ítem" para cada opción y una propuesta de entrada tanto para *hotkeys* como cadenas, junto con la opción de agregar colores a estos elementos.

La manera en la que funciona el menú está explicada más arriba en su apartado específico.