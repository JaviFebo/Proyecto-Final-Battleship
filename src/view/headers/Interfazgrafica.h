#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

#include "Window.h"
#include "MainGame.h"
#include "SeleccionarWindow.h"
#include "VistaTablero.h"


typedef enum {
    MENU,
    MAIN_GAME,
    SELECTION
} estado_juego_t;

void Com_InterfazGrafica(void);



 //@brief dibuja toda la interfaz

void DibInterface(void);


//setea el modo de juego

void setGameMode(estado_juego_t);


 //Consigue la informacion del input de la pantalla de seleccion

input_celda getInputCeldaSelection(void);


 //Consigue la informacion del input del tablreo del jugaor 1

input_celda getInputCeldaPly1();


//Consigue la informacion del input

input_celda getInputCeldaPly2();

/*
 Setea una celda de la pantalla de selecion
 
 x es la fila de la celda, y es la columna de la celda 
 y estado: 0 agua, 1 boat, 2 hit, 3 miss, 4 selecting
 */

void setCeldaSelection(int x,int y,int estado);


 //Setea una celda del tablero del jugador 1

void setCeldaPly1(int x,int y,int estado);

 //Setea una celda del tablero del jugador 2
 
void setCeldaPly2(int x,int y,int estado);


#endif