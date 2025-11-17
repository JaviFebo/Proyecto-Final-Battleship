//Dificultad facil para el juego(tablero 5x5 y 3 barcos para usar y derribar)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void iniciarTablero(int tablero[][5])
{
    int fila, columna;
    for(fila = 0; fila < 5; fila++)
        for(columna = 0; columna < 5; columna++)
            tablero[fila][columna] = -1; // -1 significa agua
}

void mostrarTablero(int tablero[][5])
{
    int fila, columna;

    printf("\t1 \t2 \t3 \t4 \t5");
    printf("\n");

    for(fila = 0; fila < 5; fila++ ){
        printf("%d", fila + 1);
        for(columna = 0; columna < 5; columna++ ){
            if(tablero[fila][columna] == -1){
                printf("\t~"); // agua
            } 
            else if(tablero[fila][columna] == 0){
                printf("\t*"); // fallo
            } 
            else if(tablero[fila][columna] == 1){
                printf("\tX"); // acierto
            }
        }
        printf("\n");
    }
}

void iniciarBarcos(int barcos[][2])
{
    srand(time(NULL));
    int barco, anterior;

    for(barco = 0; barco < 3; barco++){
        barcos[barco][0] = rand() % 5; // fila
        barcos[barco][1] = rand() % 5; // columna

        // Verifica que no se repitan las posiciones
        for(anterior = 0; anterior < barco; anterior++){
            if( barcos[barco][0] == barcos[anterior][0] &&
                barcos[barco][1] == barcos[anterior][1] )
            {
                // si se repite, genera otra posicion hasta que no coincida
                do {
                    barcos[barco][0] = rand() % 5;
                    barcos[barco][1] = rand() % 5;
                } while( barcos[barco][0] == barcos[anterior][0] &&
                         barcos[barco][1] == barcos[anterior][1] );
            }
        }
    }
}

void pedirDisparo(int disparo[2])
{
    printf("Fila: ");
    scanf("%d", &disparo[0]);
    disparo[0]--; // ajustar indice

    printf("Columna: ");
    scanf("%d", &disparo[1]);
    disparo[1]--; // ajustar indice
}

int aciertaBarco(int disparo[2], int barcos[][2])
{
    int barco;

    for(barco = 0; barco < 3; barco++){
        if(disparo[0] == barcos[barco][0] && disparo[1] == barcos[barco][1]){
            printf("Le diste a un barco con el disparo (%d,%d)\n", disparo[0] + 1, disparo[1] + 1);
            return 1;
        }
    }
    return 0;
}

void pista(int disparo[2], int barcos[][2], int intento)
{
    int filaCoincide = 0,
        columnaCoincide = 0,
        i;

    // cuenta cuántos barcos hay en la misma fila / columna
    for(i = 0; i < 3; i++){
        if(barcos[i][0] == disparo[0])
            filaCoincide++;

        if(barcos[i][1] == disparo[1])
            columnaCoincide++;
    }

    printf("\nPista %d:\nfila %d -> %d barcos\ncolumna %d -> %d barcos\n",
           intento, disparo[0] + 1, filaCoincide,
           disparo[1] + 1, columnaCoincide);
}

void actualizarTablero(int disparo[2], int barcos[][2], int tablero[][5])
{
    if(aciertaBarco(disparo, barcos))
        tablero[disparo[0]][disparo[1]] = 1; // acierto
    else
        tablero[disparo[0]][disparo[1]] = 0; // fallo
}

int main() {

    int tablero[5][5];
    int barcos[3][2];
    int disparo[2];
    int intentos = 0, aciertos = 0;

    iniciarTablero(tablero);
    iniciarBarcos(barcos);

    printf("\n");

    do{
        mostrarTablero(tablero);
        pedirDisparo(disparo);
        intentos++;

        if(aciertaBarco(disparo, barcos)){
            pista(disparo, barcos, intentos);
            aciertos++;
        } else {
            pista(disparo, barcos, intentos);
        }

        actualizarTablero(disparo, barcos, tablero);

    } while(aciertos != 3);

    printf("\n\nJuego finalizado.\nDerribaste los tres barcos en %d intentos.\n", intentos);
    mostrarTablero(tablero);

    return 0;
}
