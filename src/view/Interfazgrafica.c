#include "Interfazgrafica.h"

estado_juego_t estado;

void Com_InterfazGrafica(void){
    comWindow();
    comMainGame();
    ComElegirVentana();
}

void DibInterface(void){
    estado = SELECTION;

        BeginDrawing();
        ClearBackground(BLACK);  // Fondo negro
        switch (estado){
        case MAIN_GAME:
            dibMainGame();
            break;
        
        case SELECTION:
            DibVentanaSelec();
            break;

        default:
            break;
        }

        EndDrawing();
}

void setGameMode(estado_juego_t newEstado){
    estado = newEstado;
}

input_celda getInputCeldaSelection(){
    return getInputSelection_intern();
}

input_celda getInputCeldaPly1(){
    return getInputPly1_intern();
}

input_celda getInputCeldaPly2(){
    return getInputPly2_intern();
}

void setCeldaSelection(int x,int y,int estado){
    setCeldaSelection_intern(x, y, estado);
}

void setCeldaPly1(int x,int y,int estado){
    setCeldaPly1_intern(x, y, estado);
}

void setCeldaPly2(int x,int y,int estado){
    setCeldaPly2_intern(x, y, estado);
}