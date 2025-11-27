#include "SeleccionarWindow.h"


Tablero_v seleccion;
int setted[5] = {0, 0, 0, 0, 0};
void comElegirVentana(){
    int tamaño_tablero = 11*16*SCALE;
    seleccion.posicion.x = WIDTH/2 - tamaño_tablero/2;
    seleccion.posicion.y = HEIGHT/2 - tamaño_tablero/2;
    comTableroV(&seleccion);
}

void dibVentanaSelec(){
    dibTableroV(&seleccion);
}

input_celda getInputSeleccion_intern(){
    return checkCeldas(&seleccion);
}

void setCeldaSeleccion_intern(int x, int y, int estado){
    seleccion.celdas[x][y].state = estado;
}