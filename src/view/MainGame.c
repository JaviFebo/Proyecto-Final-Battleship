#include "MainGame.h"
#include <stdio.h>

Tablero_v tablero_ply1;
Tablero_v tablero_ply2;

void comMainGame(){
    int tamaño_tablero = 11*16*SCALE;
    tablero_ply1.posicion.x = tamaño_tablero/4;
    tablero_ply1.posicion.y = HEIGHT/2-tamaño_tablero/2;
    comTableroV(&tablero_ply1);
    tablero_ply2.posicion.x = WIDTH-tamaño_tablero*1.25f;
    tablero_ply2.posicion.y = HEIGHT/2-tamaño_tablero/2;
    comTableroV(&tablero_ply2);
}
void dibMainGame(){
    dibTableroV(&tablero_ply1);
    dibTableroV(&tablero_ply2);
}

input_celda getInputPly1_intern(){
    return checkCeldas(&tablero_ply1);
}


input_celda getInputPly2_intern(){
    return checkCeldas(&tablero_ply2);
}

void setCeldaPly1_intern(int x, int y, int estado){
    tablero_ply1.celdas[x][y].state = estado;

}
void setCeldaPly2_intern(int x, int y,int estado){
    tablero_ply2.celdas[x][y].state = estado;
}