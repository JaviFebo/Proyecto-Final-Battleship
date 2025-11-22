#include "MainGame.h"
#include <stdio.h>

Tablero_v board_ply1;
Tablero_v board_ply2;

void comMainGame(){
    int tamaño_tablero = 11*16*SCALE;
    board_ply1.posicion.x = tamaño_tablero/4;
    board_ply1.posicion.y = HEIGHT/2-tamaño_tablero/2;
    comTableroV(&board_ply1);
    board_ply2.posicion.x = WIDTH-tamaño_tablero*1.25f;
    board_ply2.posicion.y = HEIGHT/2-tamaño_tablero/2;
    comTableroV(&board_ply2);
}
void dibMainGame(){
    dibTableroV(&board_ply1);
    dibTableroV(&board_ply2);
}

input_celda getInputPly1_intern(){
    return checkCeldas(&board_ply1);
}


input_celda getInputPly2_intern(){
    return checkCeldas(&board_ply2);
}

void setCeldaPly1_intern(int x, int y, int estado){
    board_ply1.celdas[x][y].state = estado;

}
void setCeldaPly2_intern(int x, int y,int estado){
    board_ply2.celdas[x][y].state = estado;
}