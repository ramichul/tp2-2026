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

## 2. Funcionamiento (Menú)
### Estructuras
#### Menú
Es el TDA implementado para el proyecto. Almacena cada opción en un TDA Lista (cuyo funcionamiento está detallado en [este directorio](https://github.com/ramichul/tplista-2026)). Cuenta además con funcionalidades de personalización para el usuario, almacenadas en el *Paquete de personalización*.

#### Opción
Es el componente principal del menú. Siempre tiene un nombre y *hotkey* asociado. Al momento de ser utilizado, el usuario distinguirá y accederá a las opciones por su *hotkey*.

Opcionalmente podrá tener un submenú asociado, el cual se mostrara por pantalla si se elige la opción al momento de ejecutar el programa.

#### Paquete de personalización
Almacena el titulo del menú, el marcador que se muestra antes de cada opción y el mensaje de ingresión de opciones que se muestra al usuario, junto con los colores para estos componentes.

Se adjunta una visualización de las diferentes estructuras que componen el menú en memoria (con la estructura del TDA Lista, sus nodos y la contención recursiva del menú simplificada para no saturar mucho el gráfico):

![Diagrama de las estructuras del menú en memoria](https://i.imgur.com/H4x86mf.png)

### Primitivas y funcionamiento interno (Menú)
#### Creación

**`menu_t *menu_crear(char *nombre, char hotkey)`**: Crea un nuevo menú, junto con su opción de salida. Devuelve un puntero a la nueva estructura o NULL en caso de error.

Internamente, esta primitiva reserva memoria para el nuevo menú y su opción de sálida, crea la lista contenedora de opciones e inserta dicha opción en ella.

#### Inserción

**`menu_t *menu_agregar_opcion(menu_t *menu, char *nombre, char hotkey, menu_t *submenu)`**: Agrega una opción simple o un submenú adicional al menú. Devuelve un puntero al mismo menú o NULL en caso de error.

Simplemente reserva memoria para la nueva opción y la inserta en el listado de opciones, justo antes de la opción de salida y luego de la última opción insertada.

#### Eliminación

**`menu_t *menu_eliminar_opcion(menu_t *menu, char *nombre, char hotkey, menu_t **submenu_asociado)`**: Elimina una opción del menú. Si la opción tenía un submenú asociado, devolverá un puntero a ese submenú por parámetro o lo eliminará si el parámetro es nulo. Devuelve un puntero al mismo menú o NULL en caso de error.

Valida que la opción exista dentro del menú especificado con `lista_buscar()`. Si la opción existe, se quita del listado de opciones y se libera la memoria que ocupaba. Finalmente destruye al submenú asociado con `menu_destruir()` o devuelve un puntero al mismo según lo que haya pedido el usuario.

#### Personalización

**`menu_personalizar_tipografia(menu_t *menu, char *titulo_menu, char *marcador_opcion, char *propuesta_opcion)`**: Permite agregar un titulo al menú, cambiar el marcador que se muestra antes de cada opción y cambiar el mensaje de ingresión de opciones que se muestra al usuario. No se cambiará la opción si el valor es nulo.

Esto es exactamente lo que hace con los valores de `paquete_personalizacion`.

**`void menu_personalizar_colores(menu_t *menu, size_t colores[MAX_COLORES])`**: Permite cambiar los colores del título, opciones, el marcador y el mensaje de opción en ese orden. Recibe códigos de escape ANSI (0 a 255).

#### Lectura de entrada

**`void menu_iniciar(menu_t *menu, char *hotkeys_capturadas, size_t *conteo_entradas_capturadas)`**: Muestra el menú por pantalla y captura los hotkeys ingresados por el usuario (sin distinguir entre minúsculas y mayúsculas). Inserta la entrada del usuario en el arreglo pasado por parámetro (en forma secuencial) y modifica `conteo_entradas_capturadas` con su tope.

Por su complejidad y llamados recursivos, se considera más didáctico ilustrar el funcionamiento de esta función con un diagrama:

![Diagrama de funcionamiento de menu_iniciar()](https://i.imgur.com/9mZkhos.png)

**`char *menu_leer_entrada(menu_t* menu, char *propuesta_entrada)`**: Muestra la propuesta de entrada de cadena por pantalla y captura lo ingresado por el usuario. Devuelve un string conteniendo la entrada que se deberá liberar despues de ser usado, o NULL en caso de error.

Se lee a partir del teclado (`stdin`). La entrada se inserta en un buffer de tamaño dinámico que se va escalando continuamente hasta poder contener a la línea completa. Se lee hasta recibir la tecla `Enter`.

#### Destrucción

**`void menu_destruir(menu_t *menu)`**: Destruye el menú y sus opciones, preservando los submenús asociados.

**`void menu_destruir_todo(menu_t *menu)`**: Destruye el menú y sus opciones, junto con los submenús asociados.

Ambas primitivas funcionan de la misma manera: llaman a una función separada `destructor_menu()`, la cual utiliza `lista_con_cada_elemento()` para destruir recursivamente al menú, a cada submenú (si es pedido) y sus opciones. Finalmente destruye el listado de opciones en sí y se libera la memoria que ocupaban el paquete de personalización y la estructura del menú.

### Complejidades temporales (Menú)
Las comparaciones entre los nombres de las opciones se suponen constantes para estos análisis.

Se deberá tener [el repositorio de lista](https://github.com/ramichul/tplista-2026) como referencia para las complejidades de primitivas externas.

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `menu_crear()`       |  $O(n)$   |Si falla la reserva de memoria en algún paso, se deberá llamar a `lista_destruir()`, la cual es $O(n)$. Cabe notar que en un caso común la creación es $O(1)$.|
|      `menu_agregar_opcion()`       |  $O(n)$   |Se utiliza `lista_insertar_posicion()`, una función $O(n)$.|
|      `menu_eliminar_opcion()`       |  $O(n)$ |Se utiliza `lista_buscar()`, `lista_obtener_posicion()`, `lista_eliminar_posicion()` y `menu_destruir()`, todas funciones $O(n)$.|
|      `menu_personalizar_tipografia()`       |  $O(1)$ |Asignación de valores simple.|
|      `menu_personalizar_colores()`       |  $O(1)$ |Asignación de valores simple.|
|      `menu_iniciar()`       |  $O(n)$ |Utiliza `lista_buscar()` para la validación de hotkeys.|
|      `menu_leer_entrada()`       |$O(n)$|Detallado más abajo.|
|      `menu_destruir()`       |  $O(n)$ |Llama a `lista_con_cada_elemento()` y a `lista_destruir()`, ambas $O(n)$.|
|      `menu_destruir_todo()`       |  $O(n²)$ |Deberá destruir las $n$ opciones de los $n$ submenús.|

[Este proyecto](https://github.com/ramichul/tplista-2026) utiliza un mecánismo de lectura idéntico a `menu_leer_entrada()`, con la mínima diferencia de que lee a partir de una cadena existente en vez de la entrada del teclado. Se puede ver la justificación de su complejidad en el siguiente recorte:

> Se invoca la función $O(1)$ `fgetc` una vez por cada carácter de una línea de $n$ carácteres. Para comprobar que la cota final es $O(n)$, necesito comprobar que el trabajo que realiza `realloc` durante la lectura no excede esa cota.

> Se sabe que `realloc` se invocará $log_2(n)$ veces durante toda la lectura, ya que el tamaño del buffer se duplica cada vez que se necesita ampliarlo, y que además moverá cada vez más posiciones de la memoria hasta que el bloque contenga a la línea completa. Entonces, matemáticamente, su trabajo es:

> $T(n) = n + \frac{n}{2} + \frac{n}{4} + \frac{n}{8} + ... + 1$

> $T(n) = \sum_{i=0}^{log_2(n)}\frac{n}{2^i}$

> [Se puede verificar](https://www.wolframalpha.com/input?i=sum+n%2F2%5Ei%2C+i%3D0+to+log2%28n%29) que esta sumatoria tiene el resultado:

> $T(n) = 2n - 1$

> Entonces:

> $T(n) \le O(n)$.

> Por lo tanto, la complejidad final de la función entera es $O(n)$.

## 3. Funcionamiento (Juego)
#### Juego (*Colector de Pokémon!*)
Es la estructura principal de la cúal se leen todos los datos del juego. Contiene los datos del jugador, un listado de objetivos elegidos (almacenados en un TDA Lista), una lista de columnas que representa el tablero, y un puntero a una Pokédex de donde se sacan los Pokémon objetivo.

#### Jugador
Almacena la posición actual en coordenadas cartesianas, los pasos restantes, los detalles de la última batalla o la batalla actual, y un record de batallas (tambíen almacenados en un TDA Lista).

#### Batalla
Se utiliza tanto para la batalla actual como para documentar batallas pasadas en el récord de batallas. Contiene un booleano que indica si está activa actualmente, un puntero a Pokémon que simboliza el contrincante, un conteo para la duración de la batalla en turnos, y un resultado que se almacena mediante un *enum*.

Se pueden ver las diferentes estructuras del juego en memoria en el siguiente gráfico (otra vez simplificando la estructura del TDA Lista y sus nodos):

![Diagrama de las estructuras del juego en memoria](https://i.imgur.com/SXSUUUu.png)

### Primitivas y funcionamiento interno (Juego)
#### Creación

**`struct juego *juego_crear(tp1_t *tp1)`**: Crea una nueva instancia de juego a partir de la Pokédex pasada por parámetro. Devuelve un puntero a la nueva instancia o NULL en caso de error.

Internamente, reserva memoria para el puntero a la estructura principal, crea ambas listas requeridas y elige los diez objetivos al azar desde la Pokédex.

#### Destrucción

**`void juego_destruir(struct juego *juego)`**: Destruye la instancia de juego, liberando la memoria que ocupa.

Libera la memoria que ocupa cada batalla grabada (ya que se requirió hacer una copia del nombre del Pokémon) con `lista_destruir_todo()`, luego destruye la lista de objetivos con `lista_destruir() y finalmente libera la memoria que ocupaba la estructura principal y sus componentes con `free()`.

#### Funcionamiento

**`void juego_iniciar(struct juego *juego, unsigned int semilla)`**: Inicializa la instancia de juego especificada con la semilla pasada por parámetro. Se iniciará con una semilla elegida al azar si esta es 0.

Lo primero que se hace es mostrar las reglas por pantalla. Luego de que el usuario haya apretado la tecla *Enter*, se iniciará el juego.

![Reglas del juego](https://i.imgur.com/NysMEFm.png)

El juego no inicializa todo el tablero a la vez, ya que una partida puede ser potencialmente infinita. Por esto, se optó por generar columnas a medida que el jugador las descubre. Entonces, lo primero que se hace es rellenar las 8 columnas iniciales que ve el jugador al principio del juego (asegurándose de no agregar un casillero donde podría ocurrir una batalla en el punto de partida).

Finalizado esto inicia el juego. Las diferentes acciones y chequeos que se realizan para cada fotograma, en orden, son las siguientes:

- **Chequeo de condiciones de corte**: El juego terminará si se presiono la tecla de salida, no le quedan pasos al jugador, se han capturado todos los Pokémon objetivo o si se reportó un error desde otra función.

- **Loop de batallas**: Si se detecta que el jugador está en una batalla, mostrará la *UI* correspondiente y hará lo siguiente:

  1. Analiza la entrada del usuario para determinar la opción elegida (Piedra/Papel/Tijera/Escapar).
  2. Una vez elegida una opción válida, se elije una opción para el Pokémon al azar y se determina el resultado de la batalla.
  3. Si la batalla resultó en un empate, se iniciará este proceso desde cero, sumando un turno a la duración de la batalla.
  4. Si el jugador ganó la batalla, se "atrapará" al contrincante, eliminándolo de la lista de objetivos.
  5. Una vez concluída la batalla, se quitará el pasto del espacio, se grabará en el récord y se borrarán los campos relevantes de la estructura para que se utilicen en la siguiente ocasión.

Las siguientes funciones se ejecutan si el jugador no está en una batalla actualmente:

- **Lógica de movimiento**: Detecta si la entrada del usuario corresponde con una de las teclas de movimiento, actualizando su posición dentro de la estructura correspondiente.

- **Rellenado de nuevos casilleros**: Como moverse a la derecha implíca dibujar una nueva columna del mapa, se quita el primer elemento de la lista de columnas (que se sabe que ya no es ni será visible) y se genera una nueva en tiempo real.

- **Impresión del *UI* por pantalla**: Muestra todos los casilleros en una ventana de 8x5 con su símbolo y color correspondiente según el carácter leído desde las columnas. Además, imprime un contador de pasos restantes y muestra los objetivos restantes por pantalla.

- **Lógica de batallas**: Decide si un jugador debe ser atacado por un Pokémon. Inicia una batalla y muestra una alerta por pantalla si este es el caso.

Dado que la mayoría de las funcionalidades usan un TDA Lista de fondo y pueden fallar, si algún error ocurre durante estos procesos se reportará de vuelta a la función principal. Esta se encargará de cortar la ejecución del programa al detectarlo.

Al finalizar el juego se le mostrarán todas las batallas grabadas al usuario con su resultado, contrincante y duración respectivos.

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

### Flujo del programa de prueba implementado

Se implementó un programa con ayuda de la estructura de Pokédex (detallada en [este directorio](https://github.com/ramichul/tp1-2026)) para comprobar el buen funcionamiento y las capacidades del menú y el juego. Su funcionamiento es el siguiente (dando por sentado que el programa se abortará cuando haya sucedido un error):

1. Antes de buscar, se parsean los argumentos. En este proceso se detecta una cantidad inválida de argumentos. Si el archivo es inválido o la Pokédex está vacía, esto se detectará más adelante por las estructuras.
2. Una vez validados los argumentos, se crea la Pokédex y se extraen los datos desde el archivo pasado por línea de comando. Si al finalizar la Pokédex está vacía, se le avisará de esto al usuario y no se seguirán procesando los datos.
3. Se crea el diccionario. Se insertan los Pokémon en él uno por uno utilizando `tp1_con_cada_pokemon()`.
4. Se crea el menú principal y el menú de búsqueda y se inicializa cada uno con sus opciones y personalizaciones estéticas.
5. Se inicia el menú principal y se captura la entrada del usuario.
6. Se ejecutan una de 4 opciones:
   - Si el usuario eligió buscar por nombre, se utiliza `diccionario_obtener()` para buscar el Pokémon dentro del diccionario. Una vez obtenido, se imprimen sus datos por pantalla. Si el Pokémon no fue encontrado, se le avisa de esto al usuario.
   - Si la busqueda es por tipo, se utiliza `diccionario_con_cada_elemento()` para identificar los Pokémon uno por uno, y luego se imprimen sus datos por pantalla si son del tipo buscado.
   - Si el usuario elegió jugar, se inicializará el juego con o sin una semilla predeterminada según la entrada.
7. Se libera la memoria utilizada y se termina la ejecución del programa.

## 3. Respuestas a las preguntas teóricas
(Hay diagramas de las estructuras más arriba)

#### Explicar y justificar las estructuras y TDAs utilizados para implementar las diferentes partes del juego.
Cuando se estaba pensando el diseño del juego, se supo que sí o sí se necesitarían varios contenedores para almacenar los diferentes datos (los objetivos, el tablero y el récord de batallas). 

Se descartó la utilización del TDA Diccionario a pesar de su eficiencia para los contenedores, ya que no permite al usuario insertar en una posición específica. Se decidió, en cambio, usar un TDA Lista para ellos por su simplicidad y facilidad de uso. Si bien se podría haber utilizado para el manejo de objetivos (ya que no requiere un orden estricto), se optó por no usarlo para poder mostrarlos en orden alfabético, agruparlos y no desorientar al usuario.

Inicialmente se había implementado el tablero con una matriz de caracteres: aunque el acceso fácil y directo a los datos ayudó durante el desarrollo, rápidamente resultó ineficiente (principalmente para el desplazamiento de columnas cuando el jugador se mueve a la derecha). Frente a esto, se optó por almacenar las columnas en un TDA Lista para solucionar el problema del desplazamiento, aunque esto no vino sin su contra: se dificultó mucho más el acceso y edición de datos, y se agregaron dificultades mayores a la implementación de `mostrar_mapa()` (imprimir fila por fila es mucho más complejo cuando el mapa está seccionado por columnas). 

Más allá de las dificultades, la implementación del TDA Lista para las columnas resultó muy exitosa en optimizar tanto el funcionamiento del programa como su uso de memoria.

Otras instrucciones del enunciado exigían la existencia de diferentes campos, como los pasos restantes y los detalles de la batalla.

#### Explicar las decisiones tomadas para la creación del TDA Menú (justificar datos y operaciones que lo conforman). Explicar cómo funciona.

La estructura del menú se penso desde el principio como una lista de opciones. Se pensó a la opción de sálida como un componente obligatorio para el menú, por lo que su inicialización está ligada a su creación.

La decisión de víncular submenús a opciones en vez de diferenciarlos se hizo con la intención principalmente de no saturar el TDA con primitivas y mantenerlo lo menos complicado posible para el usuario. Esta misma decisión es la que influyo la implementación separada de `menu_leer_entrada()`, ya que su incorporación a la estructura de opción resultaría en dos caminos que se vieron como ineficientes: agregar otra condición mas a `menu_agregar_opcion()` (no solo complicando su uso demás si no que también el código detrás, especialmente para `menu_iniciar()`), o agregar una primitiva distinta que permita agregar opciones que solo leen entradas.

Para la eliminación de opciones se quiso mantener al TDA flexible y práctico y darle la mayor autonomía posible al usuario, por lo que la opción de destruir o no el submenú asociado al momento de eliminar queda a su discreción. Esta misma filosofía se ve reflejada en la distinción de las dos primitivas `menu_destruir()` y `menu_destruir_todo()`.

Posteriormente se añadió el paquete de personalización, junto con sus dos primitivas relacionadas. Tambíen se buscó lograr un balance entre código y presentación simple sin quitar funcionalidade esenciales. Teniendo en cuenta esto, se decidió permitir al usuario agregar o no un titulo, un marcador o "ítem" para cada opción y una propuesta de entrada tanto para *hotkeys* como cadenas, junto con la opción de agregar colores a estos elementos.

La manera en la que funciona el menú está explicada más arriba en su apartado específico.