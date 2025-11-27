#ifndef MODELO_TABLERO_H
#define MODELO_TABLERO_H

typedef enum{
    AGUA,
    BARCO,
    SELECTING,
    MISS,
    HIT
}Estados_tablero_e;

//Limpia uno de los talbreros

void limpTablero(int);

Estados_tablero_e** getPly1Tablero();

Estados_tablero_e** getPly2Tablero();







#endif