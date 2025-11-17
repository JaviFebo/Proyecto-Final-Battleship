//Dificultad media para el juego(tablero 7x7 y 5 barcos)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void iniciarTablero(int tablero[][7])
{
    int fila, columna;
    for(fila = 0; fila < 7; fila++)
        for(columna = 0; columna < 7; columna++)
            tablero[fila][columna] = -1;
}

void mostrarTablero(int tablero[][7])
{
    int fila, columna;

    printf("\t1 \t2 \t3 \t4 \t5 \t6 \t7\n");

    for(fila = 0; fila < 7; fila++){
        printf("%d", fila + 1);
        for(columna = 0; columna < 7; columna++){
            if(tablero[fila][columna] == -1){
                printf("\t~");   // Agua
            }else if(tablero[fila][columna] == 0){
                printf("\t*");   // Fallo
            }else if(tablero[fila][columna] == 1){
                printf("\tX");   // Acierto
            }
        }
        printf("\n");
    }
}

void iniciarBarcos(int barcos[][2])
{
    srand(time(NULL));
    int barco, anterior;

    for(barco = 0; barco < 5; barco++){
        barcos[barco][0] = rand() % 7;
        barcos[barco][1] = rand() % 7;

        for(anterior = 0; anterior < barco; anterior++){
            if(barcos[barco][0] == barcos[anterior][0] &&
               barcos[barco][1] == barcos[anterior][1])
            {
                do{
                    barcos[barco][0] = rand() % 7;
                    barcos[barco][1] = rand() % 7;
                }while(barcos[barco][0] == barcos[anterior][0] &&
                       barcos[barco][1] == barcos[anterior][1]);
            }
        }
    }
}

void pedirDisparo(int disparo[2])
{
    printf("Fila: ");
    scanf("%d", &disparo[0]);
    disparo[0]--;

    printf("Columna: ");
    scanf("%d", &disparo[1]);
    disparo[1]--;
}

int acertarBarco(int disparo[2], int barcos[][2])
{
    int barco;

    for(barco = 0; barco < 5; barco++){
        if(disparo[0] == barcos[barco][0] &&
           disparo[1] == barcos[barco][1])
        {
            printf("¡Acertaste un barco con el disparo (%d, %d)!\n",
                   disparo[0] + 1, disparo[1] + 1);
            return 1;
        }
    }
    return 0;
}

void pista(int disparo[2], int intento)
{
    printf("\nPista %d: Disparo realizado en fila %d, columna %d\n",
           intento, disparo[0] + 1, disparo[1] + 1);
}

void actualizarTablero(int disparo[2], int barcos[][2], int tablero[][7])
{
    if(acertarBarco( disparo, barcos ))
        tablero[disparo[0]][disparo[1]] = 1;   // Acierto
    else
        tablero[disparo[0]][disparo[1]] = 0;   // Fallo
}

int main()
{
    int tablero[7][7];
    int barcos[5][2];
    int disparo[2];
    int intentos = 0, aciertos = 0;

    iniciarTablero(tablero);
    iniciarBarcos(barcos);

    do{
        mostrarTablero(tablero);
        pedirDisparo(disparo);
        intentos++;

        if(acertarBarco(disparo, barcos)){
            aciertos++;
        }

        pista(disparo, intentos);
        actualizarTablero(disparo, barcos, tablero);

    }while(aciertos != 5);

    printf("\n\nJuego terminado. Acertaste los cinco barcos en %d intentos.\n",
           intentos);

    mostrarTablero(tablero);

    return 0;
}

