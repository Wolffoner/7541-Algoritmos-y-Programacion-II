<details>
<summary>
Information
</summary>
Author: Wolffoner
Fecha: 01/05/2021
Facultad de Ingeniería, Universidad de Buenos Aires
7541 - Algoritmos y Programación II - Mendez
</details>

# Salon de la Fama :trophy:

## Introducción :raised_hand:

Este TP `(trabajo teorico-practico)` consiste en el desarrollo de una API `(Application Programming Interface)` para la escritura y lectura de archivos con un formato previamente establecido. Su tematica es un salon de la fama donde se llevara el registro, de los entrenadores que han vencido el alto mando junto con sus respectivos pokemones.

## Objetivo :heavy_check_mark:

- El objetivo principal del TP es la implementacion de los temas previamente vistos en Lenguaje C, dentro de los mas destacados estan los siguientes puntos: 
  - Manejo de Archivos. 
  - Metodos de Ordenamiento. 
  - Modularizacion.
  - Gestion de Memoria.
  - Punteros.
  - Aritmetica de Punteros.
  - Casteo de tipos.

## Condiciones Previas :lock:

### Archivos
El formato del contenido de los registros guardado en los archivos, debe ser el siguiente,
para entrenadores:
```
nombre;victorias
```
para pokemones:
```
nombre;nivel;fuerza;defensa;inteligencia;velocidad
```
Donde la primera linea del archivo ***SIEMPRE*** debe ser un entrenador y las lineas siguientes los Pokemones del mismo entrenador hasta que consiga una linea con el siguiente entrenador.

### Utilidades
Una de las convenciones previamente establecidas los vectores dinamicos se encuentran delimitados por un puntero NULL, esto nos quiere decir que el final del vector dinamico va a tener como valor el puntero NULL.

<img src="https://github.com/Wolffoner/TP1/blob/main/imgs/Algo2-Convencion.jpg">

## Compilacion y Ejecucion :hammer:

### Utilidades
Para poder correr nuestro makefile, deben estar instalados las siguientes utilidades:

- ***make***
- ***Valgrind***
- ***gcc***

### Compilacion y Ejecucion
Para compilarlo y ejecutarlo hay un archivo makefile, para automatizar nuestras pruebas sugeridas:
- Compilar:
```
make compilar
```
- Ejecutar:
```
make valgrind
```
- Compilar Test:
```
make compilar-test
```
- Test:
```
make test
```

## Marco Teórico :scroll:

### Heap y Stack ¿Para que y como se utiliza cada uno?

El heap y el stack son ambos espacios de memoria dentro del computador pero que son utilizados de manera distinta.
El stack es manejado exclusivamente por el compilador por lo que no es posible que algun programador pueda alterar este mismo, mientras que el heap si es manejada por el programador durante el tiempo de ejecucion.

- El stack lo utiliza el compilador para almacenar argumentos y variables locales durante la ejecucion de las funciones en las que esta definida.

- El heap es utilizado por el programador para almacenar variables adquiridas dinamicamente via funciones como malloc, calloc o realloc, durante la ejecucion de un programa. 

### Malloc / Realloc / Free ¿Para que y como se utilizan?

- Malloc es una funcion que nos permite reservar un espacio determinado dependiendo del parametro `size_t` que le pasemos. Esto nos retornara un puntero al espacio que reservamos.

- Realloc es una funcion que nos permite modificar o reservar un espacio determinado dependiendo de los parametros si le pasamos un puntero a NULL seria equivalente a hacer un malloc, si no es asi modificariamos el tamaño  `size_t` que le pasemos `Nota: si le pasamos cero al segundo parametro nos hara un free()`. Esto nos retornara un puntero al espacio que modificamos o reservamos.

- Free es una funcion que nos permite liberar el espacio en memoria previamente reservado, una vez que hicimos una llamada a alguna funcion `alloc` y trabajamos con esa memoria dinamica una vez que terminemos que usar esa memoria dinamica debemos liberar la memoria haciendo un free() y pasandole como parametro el puntero donde apunta la memoria reservada.

## Preview

<img src="https://github.com/Wolffoner/TP1/blob/main/imgs/Demo.PNG">
