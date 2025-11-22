#ifndef MODELO_TABLERO_H
#define MODELO_TABLERO_H

typedef enum{
    AGUA,
    BARCO,
    SELECTING,
    MISS,
    HIT
}Estados_Tablero_e;

int RevColision();

void LimpTablero(int);

void getPly1Tablero();

void getPly2Tablero();

void getPly1Barco(int);

void getPly2Barco(int);





#endif