#ifndef JUEGO_H
#define JUEGO_H

#define TAMANO_TABLERO 10
#define CANTIDAD_BARCOS 5
#define INDf 4;

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

/* Función para iniciar tablero
 * Recibe:
 * - Una dirección de una instancia de la estructura de tablero
 * Hace:
 * -Agrega cada instancia de la estructura de barco al tablero
 * -Inicia cada elemento del tablero en estado Agua
 */

void InitTablero (struct Tablero *tablero);

/* Función para colocar barco en tablero
 * Recibe:
 * - Una dirección de una instancia de la estructura de tablero
 * - Un número barco (Utilice el macro de NumeracionBarco)
 * - Coordenada en x
 * - Coordenada en y
 * Hace:
 * - Establece la posición inicial del barco (pos_x y pos_y) a las coordenadas ingresadas
 * - Establece las casillas del tablero en estado barco dependiendo de su orientación y longitud
 */

void ColocarBarco (struct Tablero *tablero, int num_barco, int x, int y);

/* Función para atacar una casilla
 * Recibe:
 * - Una dirección de una instancia de la estructura de tablero
 * - Coordenada en x
 * - Coordenada en y
 * Hace:
 * - Verifica si la celda en la coordenada (y,x) está en estado Agua o Barco
 * - Si está en estado Agua la pasa a estado Fallo, si está en estado Barco la pasa a estado Acierto
 * - Si no está ni en estado Agua ni en estado Barco, no tiene efecto
 * Regresa: 
 * - El estado de la casilla en la coordenada (y,x) después del ataque
 * - Indefinido si el ataque no tuvo efecto
 */

int Atacar (struct Tablero *tablero, int x, int y);

/* Función para pasar al siguiente turno
 * Recibe:
 * - Una dirección de una instancia de la estructura de tablero
 * - Un número de turno
 * Hace:
 * - Verifica si el turno es del jugador 1 (impar) o del jugador 2 (par)
 * - Ejecuta la función atacar en la coordenadas (x,y)
 * - Si el ataque es efectivo o indefinifo vuelve a repetir el turno
 * - Cuando termina el turno le agrega uno al contador de turnos
 */
void SiguienteTurno (struct Tablero *tablero, int turno);

extern struct Tablero TableroJugador1;
extern struct Tablero TableroJugador2;

extern struct Barco Barco1;
extern struct Barco Barco2;
extern struct Barco Barco3;
extern struct Barco Barco4;
extern struct Barco Barco5;

extern int turno;

#endif

