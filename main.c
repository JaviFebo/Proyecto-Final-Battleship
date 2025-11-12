#include "raylib.h"
#include "juego.h"

/* Guía macros:
 * (Si no se espeficica el valor van de 0 en adelante en orden)
 *
 * === Tablero ===
 * TAMANO_TABLERO 10
 * CANTIDAD_BARCOS 5
 *
 * === Coordenadas en X ===
 * A, B, C, D, E, F, G, H, I, J
 *
 * === Estado de celda ===
 * AGUA, BARCO, ACIERTO, FALLO, INDF
 *
 * === Numeración de barcos ===
 * BARCO1, BARCO2, BARCO3, BARCO4, BARCO5
 *
 * === Orientación de barco ===
 * HORIZONTAL, VERTICAL
 *
 * === Longitud Barcos ===
 * LON_BARCO1 = 2
 * LON_BARCO2 = 3
 * LON_BARCO3 = 3
 * LON_BARCO4 = 4
 * LON_BARCO5 = 5
 */

int main (void) {
	struct Barco Barco1 = {A, 0, LON_BARCO1, VERTICAL};
	struct Barco Barco2 = {A, 0, LON_BARCO2, VERTICAL};
	struct Barco Barco3 = {A, 0, LON_BARCO3, VERTICAL};
	struct Barco Barco4 = {A, 0, LON_BARCO4, VERTICAL};
	struct Barco Barco5 = {A, 0, LON_BARCO5, VERTICAL};

	struct Tablero TableroJugador1;
	struct Tablero TableroJugador2;

	int turno = 1;

	return 0;
}
