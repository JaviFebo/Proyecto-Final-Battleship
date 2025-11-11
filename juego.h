#ifndef JUEGO_H
#define JUEGO_H

#define TAMANO_TABLERO 10
#define CANTIDAD_BARCOS 5

typedef enum {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J
} CoordXCelda;

typedef enum {
        AGUA,
        BARCO,
        ACIERTO,
        FALLO
} EstadoCelda;

struct Barco {
        int pos_x;
        int pos_y;
        int longitud;
        int orientacion;
};

typedef enum {
        HORIZONTAL,
        VERTICAL
} OrientacionBarco;

typedef enum {
        BARCO1,
        BARCO2,
        BARCO3,
        BARCO4,
        BARCO5
} NumeracionBarco;

typedef enum {
        LON_BARCO1 = 2,
        LON_BARCO2 = 3,
        LON_BARCO3 = 3,
        LON_BARCO4 = 4,
        LON_BARCO5 = 5
} LongitudBarco;

struct Tablero {
        EstadoCelda celdas [TAMANO_TABLERO][TAMANO_TABLERO];
        struct Barco barcos [CANTIDAD_BARCOS];
};

void InitTablero (struct Tablero *tablero);

void ColocarBarco (struct Tablero *tablero, int num_barco, int x, int y);

int Atacar (struct Tablero *tablero, int x, int y);

void SiguienteTurno (struct Tablero *tablero, int turno);

void ImpTablero (struct Tablero *tablero);

extern struct Tablero TableroJugador1;
extern struct Tablero TableroJugador2;

extern struct Barco Barco1;
extern struct Barco Barco2;
extern struct Barco Barco3;
extern struct Barco Barco4;
extern struct Barco Barco5;

extern int turno;

#endif

