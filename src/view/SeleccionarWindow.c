#include "SeleccionarWindow.h"


Tablero_v seleccion;
int setted[5] = {0, 0, 0, 0, 0};
void ComElegirVentana(){
    int tamaño_tablero = 11*16*SCALE;
    seleccion.posicion.x = WIDTH/2 - tamaño_tablero/2;
    seleccion.posicion.y = HEIGHT/2 - tamaño_tablero/2;
    comTableroV(&seleccion);
}

void DibVentanaSelec(){
    dibTableroV(&seleccion);
}

input_celda getInputSelection_intern(){
    return checkCeldas(&seleccion);
}

void setCeldaSeleccion_intern(int x, int y, int estado){
    seleccion.celdas[x][y].state = estado;
}

void setCeldaSelection_intern(int, int, int)
{
}
