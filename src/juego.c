#include "juego.h"
struct Barco Barco1 = {A, 0, LON_BARCO1, VERTICAL};
struct Barco Barco2 = {A, 0, LON_BARCO2, VERTICAL};
struct Barco Barco3 = {A, 0, LON_BARCO3, VERTICAL};
struct Barco Barco4 = {A, 0, LON_BARCO4, VERTICAL};
struct Barco Barco5 = {A, 0, LON_BARCO5, VERTICAL};

struct Tablero TableroJugador1;
struct Tablero TableroJugador2;

int turno = 1;

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

        return INDF;
}

void SiguienteTurno (struct Tablero *tablero, int turno) {
	int x; //Por definir función para obtener este valor
	int y; //Por definir función para obtener este valor
	if (turno % 2 != 0) {
		int ataque = Atacar (&TableroJugador1, x, y);
		if (ataque == ACIERTO || ataque == INDF) SiguienteTurno (&TableroJugador1, turno);
	} else {
		int ataque = Atacar (&TableroJugador2, x, y);
		if (ataque == ACIERTO ataque == INDF) SiguienteTurno (&TableroJugador2, turno);
	}
	turno++;
}

bool JugadorGana (struct Tablero *tablero) {
	for (int i = 0; i < TAMANO_TABLERO; i++) {
                for (int j = 0; j < TAMANO_TABLERO; j++) {
                        if (tablero -> celdas [i][j] == BARCO) {
			       return false;	       
		}
	}
	return true;
}
