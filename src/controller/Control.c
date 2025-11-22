#include "Control.h"


void Iniciar_juego(){
    Com_InterfazGrafica();
    while (!WindowShouldClose()) {
        DibInterface();
    }

    // Cierra la ventana
    CloseWindow();
}