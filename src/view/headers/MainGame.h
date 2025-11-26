#ifndef MAIN_GAME_H
#define MAIN_GAME_H
#include "VistaTablero.h"
#include "Compartido.h"



//Inicia los componentes para la parte principal del juego

void comMainGame();


void dibMainGame();

input_celda getInputPly1_intern();
input_celda getInputPly2_intern();

void setCeldaPly1_intern(int, int, int);
void setCeldaPly2_intern(int, int ,int);





#endif