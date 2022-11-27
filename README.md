# algo2-tp2

## Cuestionario

1) ¿Qué es “SVN”?
Apache Subversion es un sofware utilizado para versionar y controlar archivos de texto como codigo. Actualmente no es muy utilizado ya que crea copias de los repositorios cada vez que se hace un branch por lo que puede hacer que los proyectos aumenten mucho su tamaño.

2) ¿Qué es un “git” y “Github”?
Al igual que SVN, git es un software de gestion de versiones de archivos. A diferencia de SVN, git trabaja con deltas entre archivos que lo hacen mas livianos pero en contraste requiere mas procesamiento para cambiar de una rama (branch) a otra. Github por otro lado, es un servicio ofrecido actualmente por Microsoft que hostea un servidor git y ademas tiene una UI muy conveniente para gestionar proyectos que ademas poseé muchas otras funciones como por ejemplo pipelines de CI/CD.

3) ¿Qué es “valgrind”?
Valgrind es una hermanienta que permite depurar (debugging) memoria y detectar fugas de memoria.


## Uso
Una vez que se inicia el programa, se debe elegir entre 4 opciones:

    Elija una opcion del menu:
    [1] Configuracion 1
    [2] Configuracion 2
    [3] Configuracion 3
    [4] Ingresar manualmente

La primeras 3 opciones son templates ya cargados con las celdas vivas y las celdad con funciones especiales. La cuarta opcion nos permite elegir el tamaño del tablero y la ubicacion de las celdad vivas. Aparecera un mensaje como el siguiente:

    Ingrese la cantidad de planos del tablero: 
    Ingrese la cantidad de filas del tablero: 
    Ingrese la cantidad de columnas del tablero: 
    Por favor ingrese el plano: 
    Por favor ingrese el fila: 
    Por favor ingrese el columna: 
    Para seguir ingrtesando celulas presione S:

Las primeras tres lineas esperan recibir 3 entradas numericas que definiran el tamaño del tablero del juego. Luego se solicitaran las 3 coordenadas donde se quiere que se coloque la celula viva. Luego, deberemos decidir si continuamos con la carga de celulas vivas prsionando `s` o `S` o finalizar con cualquier otra tecla.

Una vez finalizada la carga, se mostratan las estadisticas del turno y las totales:

    Celulas vivas: 6
    Nacimientos turno: 0
    Fallecimientos turno: 0
    Nacimientos TOTALES: 0
    Fallecimientos TOTALES: 0
    Juego congelado: S

Tambien se imprimira el tablero en la linea de comandos en forma de matriz de caracteres indicando con la letra V si esta viva y con la letra M si esta muerta:

    Plano: 1
    V V M M M 
    M M M M M 
    V M M M M 

Notar que se imprime una matriz por plano y se imprimiran tantas matrices como planos.

Por ultimo, se imprime un menu para elegir como continuar en el juego:

    Eliga una opcion del menu para continuar:
    [t] Pasar un turno
    [v] Pasar varios turno
    [r] Reiniciar juego
    [f] Finalizar juego

### Comportamiento de genes
* Maximo: obtiene el maximo entre una lista de genes.

* Minimo: obtiene el minimo entre una lista de genes.

* Promedio: calcula un promedio de los genes.
### Casillero
a) Celda Zombie: no muere y sus 3 genes son 0.

b) Celda decay: se desintegra un 5% por turno si esta viva.

c) Celda complemento: copia a otra celda de forma complementaria. Si esta viva muere, y sus genes seran 255 - gen.

d) Celda portal: duplica el nacimiento de una célula en otra.

e) Celda radioactiva: afecta a uno o varios genes al heredarse.

## Compilacion
Para compilar el proyecto hay que situarse en la carpeta raiz del mismo y correr el siguiente comando:

    g++ easyBMP/EasyBMP.cpp main.cpp -o main

Luego para correrlo en Linux:

    ./main


## Links
* [Repositorio del proyecto](https://github.com/jmacid/algo2-tp2)