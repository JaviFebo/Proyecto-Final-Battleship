#include "Interfazgrafica.h"
#include <stdio.h>

extern int ganador;
static void dibGameOver(void);
estado_juego_t estado_;

void Com_InterfazGrafica(void){
    comWindow();
    comMainGame();
    comElegirVentana();
}

void DibInterface(void){

        BeginDrawing();
        ClearBackground(SKYBLUE);  // Fondo celeste
        switch (estado_){
        case MAIN_GAME:
            dibMainGame();
            break;
        
        case SELECTION:
            dibVentanaSelec();
            break;

        case GAME_OVER:
            dibGameOver();
            break;
        default:
            break;
        }

        EndDrawing();
}

void setGameMode(estado_juego_t estadoNuevo){
    estado_ = estadoNuevo;
}

input_celda obtenerInputCeldaSeleccion(){
    return getInputSeleccion_intern();
}

input_celda getInputCeldaPly1(){
    return getInputPly1_intern();
}

input_celda getInputCeldaPly2(){
    return getInputPly2_intern();
}

void setCeldaSeleccion(int x,int y,int estado){
    setCeldaSeleccion_intern(x, y, estado);
}

void setCeldaPly1(int x,int y,int estado){
    setCeldaPly1_intern(x, y, estado);
}

void setCeldaPly2(int x,int y,int estado){
    setCeldaPly2_intern(x, y, estado);
}

static void dibGameOver(void) {
    const char* msg;

    if (ganador == 1) msg = "¡Jugador 1 GANA!";
    else if (ganador == 2) msg = "¡Jugador 2 GANA!";
    else msg = "Fin del juego";

    int fontSize = 50;
    int w = MeasureText(msg, fontSize);

    DrawText(msg, (WIDTH - w) / 2, HEIGHT/2 - 40, fontSize, RED);

    DrawText("Presione ENTER para salir", 
             WIDTH/2 - 200, HEIGHT/2 + 20, 
             25, RAYWHITE);
}
