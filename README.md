# Proyecto-Final

Este repositorio incluye el código para el proyecto final del curso de Programación
bajo plataformas abiertas.

## 1. Descripción del proyecto

Este proyecto es una réplica del juego Battleship, desarrollada en lenguaje C 
utilizando la librería gráfica Raylib para mostrar un tablero interactivo y 
permitir al usuario hundir barcos mediante una interfaz simple. El objetivo del 
proyecto es implementar la lógica del juego de forma modular, separando el código
en archivos .c y .h, y permitir ejecutar el juego en sistemas Linux.

## 2. Instalación y dependencias

### Dependencias:

- Compilador de C
- Make
- Git
- Raylib v5.5

### Instalación de Raylib:

Instalar el archivo en el siguiente enlace de descarga de [Raylib](https://github.com/raysan5/raylib/releases/download/5.5/raylib-5._linux_amd64.tar.gz).
Una vez instalado, deberá descomprimir el contenido. Una vez descomprimido el 
archivo, deberá posicionarse en el directorio de la descarga y ejecutar el comando
`sudo cp -r ./* /usr/`.

### Clonación del proyecto:

Utilice el comando `git clone https://github.com/JaviFebo/Proyecto-Final-Battleship.git` 
para clonar el proyecto en su entorno. Para acceder al directorio del proyecto 
utilice el comando `cd Proyecto-Final-Battleship`.

## 3. Ejecución y compilación

### Compilación

Dentro del directorio del proyecto, utilice el comando `make`. Esto va a generar 
un archivo `/build/output`.

### Ejecución

Utilice el comando `cd build/` para acceder al directorio donde está el ejecutable 
y dentro utilice el comando `./output` para ejecutar el programa.

## 4. Diseño del proyecto

### Estructura de archivos

El proyecto está estructurado de la siguiente forma:

```
├── assets/                    			# Directorio para recursos gráficos para los íconos y fuentes
│   ├── letters/						# Directorio para fuentes de letras	                		
│   ├── numbers/                		# Directorio para fuentes de números
│   └── *.png							# Íconos del juego
├── build/                     			# Directorio para archivos generados durante la compilación
│   └── output                 		# Ejecutable final del juego
├── src/                       			# Directorio para código fuente principal
│   ├── controller/            		# Directorio para el control del juego
│   │   ├── headers/Control.h  		# Definición de la interfaz del controlador
│   │   └── Control.c         			# Implementación de la gestión de entradas
│   ├── model/                 		# Directorio para la lógica del juego
│   │   ├── headers/ModeloTablero.h 	# Definición de la interfaz del modelo
│   │   └── ModeloTablero.c    		# Implementación de reglas y estado del juego
│   ├── view/                  		# Directorio de la vista con gráficos de Raylib
│   │   ├── headers/*h         		# Interfaces para todas las ventanas y vistas
│   │   └── *c                 		# Implementaciones de dibujo y manejo de la ventana
│   └── main.c                 		# Función de arranque que inicializa y maneja el ciclo de juego
├── makefile                   			# Script de compilación
└── Readme.md							# Documentación
```
