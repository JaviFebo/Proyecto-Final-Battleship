#include "juego.h"
#include <stdio.h>
#include <stdio.h>

struct Barco Barco1 = {A, 0, LON_BARCO1, VERTICAL};
struct Barco Barco2 = {A, 0, LON_BARCO2, VERTICAL};
struct Barco Barco3 = {A, 0, LON_BARCO3, VERTICAL};
struct Barco Barco4 = {A, 0, LON_BARCO4, VERTICAL};
struct Barco Barco5 = {A, 0, LON_BARCO5, VERTICAL};

struct Tablero TableroJugador1;
struct Tablero TableroJugador2;

void InitTablero (struct Tablero *tablero) {
        tablero -> barcos[0] = Barco1;
        tablero -> barcos[1] = Barco2;
        tablero -> barcos[2] = Barco3;
        tablero -> barcos[3] = Barco4;
        tablero -> barcos[4] = Barco5;

        for (int i = 0; i < TAMANO_TABLERO; i++) {
                for (int j = 0; j < TAMANO_TABLERO; j++) {
                        tablero -> celdas [i][j] = AGUA;
                }
        }
}

void ColocarBarco (struct Tablero *tablero, int num_barco, int x, int y) {
                tablero -> barcos[num_barco].pos_x = x;
                tablero -> barcos[num_barco].pos_y = y;

                if (tablero -> barcos[num_barco].orientacion == VERTICAL) {
                       for (int i = 0; i < tablero -> barcos[num_barco].longitud; i++) {
                               tablero -> celdas [y + i][x] = BARCO;
                        }

                } else if (tablero -> barcos[num_barco].orientacion == VERTICAL) {
                       for (int i = 0; i < tablero -> barcos[num_barco].longitud; i++) {
                               tablero -> celdas [y][x + i] = BARCO;
                        }
                }
}

int Atacar (struct Tablero *tablero, int x, int y) {
        if (tablero -> celdas [y][x] == AGUA) {
                tablero -> celdas [y][x] = FALLO;
                return FALLO;
        }

        if (tablero -> celdas [y][x] == BARCO) {
                tablero -> celdas [y][x] = ACIERTO;
                return ACIERTO;
        }

        return tablero -> celdas [y][x];
}

void ImpTablero (struct Tablero *tablero) {
        for (int i = 0; i < TAMANO_TABLERO; i++) {
                printf ("\n");
                for (int j = 0; j < TAMANO_TABLERO; j++) {
                        printf (" %d ", tablero -> celdas [i][j]);
                }
        }
        printf ("\n");
}

