#ifndef VISTA_TABLERO_H
#define VISTA_TABLERO_H
#include "raylib.h"
#include "Compartido.h"

typedef struct {
    int x;
    int y;
    int click; // 0 izquierdo, 1 derecho
}input_celda;


//Representa graficamente una celda de un tablero
 
typedef struct{
    Texture2D miss;
    Texture2D hit;
    Texture2D boat;
    Texture2D water;
    Texture2D selcting;
    Vector2 posicion;
    int state;
}Celda_v; 

//Representa graficamente las columnas y filas del tablrero
 
typedef struct{
    Texture2D textura;
    Vector2 posicion;
}Col_v;

//Representa graficamente el tablero del juego

typedef struct{
    Col_v filas[TAMAÑO_TABLERO];
    Col_v cols[TAMAÑO_TABLERO];
    Celda_v celdas[TAMAÑO_TABLERO][TAMAÑO_TABLERO]; // Las celdas
    Vector2 posicion;
}Tablero_v;

//Inicializa todas las texturas de una celda

void comCeldaV(Celda_v*, Vector2);

//Renderiza la textura de una celda

void dibCeldaV(Celda_v*);

//Iniciliza las texturas y posiciones de todos los elementos de un tablero

void comTableroV(Tablero_v*);

//Renderiza un tablero

void dibTableroV(Tablero_v*);


input_celda checkCeldas(Tablero_v* tablero);

#endif




