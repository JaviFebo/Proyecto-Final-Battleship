#include "Control.h"
#include <stdio.h>
#include <stdlib.h>

void checkWin(void);

estado_juego_t estado;
int playerSelecting = 0;
int cantidad_aciertos_1 = 0;
int cantidad_aciertos_2 = 0;
int ganador = 0;  

Estados_tablero_e tableroply1[10][10];
Estados_tablero_e tableroply2[10][10];

// Estructura para representar un barco
typedef struct {
    int x, y;           // Posición inicial
    int longitud;         // Longitud del barco
    int horizontal;     // 1 = horizontal, 0 = vertical
    int colocado;         // ¿Ya fue colocado?
    int hits;           // Cuántas celdas han sido golpeadas
} Barco;

// Tamaños de los barcos: 5, 4, 3, 3, 2
const int TAMAÑO_BARCOS[5] = {5, 4, 3, 3, 2};
Barco barcos_ply1[5];
Barco barcos_ply2[5];

int barco_actual_1 = 0;
int barco_actual_2 = 0;

// Variables para el preview del barco
int preview_x = 0, preview_y = 0;
int preview_horizontal = 1;  // Orientación actual del preview

void comBarcos() {
    for(int i = 0; i < 5; i++) {
        barcos_ply1[i].longitud = TAMAÑO_BARCOS[i];
        barcos_ply1[i].colocado = 0;
        barcos_ply1[i].hits = 0;
        barcos_ply1[i].horizontal = 1;
        
        barcos_ply2[i].longitud = TAMAÑO_BARCOS[i];
        barcos_ply2[i].colocado = 0;
        barcos_ply2[i].hits = 0;
        barcos_ply2[i].horizontal = 1;
    }
}

// Verifica si un barco puede ser colocado en una posición
int puedeColocarBarco(Estados_tablero_e tablero[10][10], int x, int y, int longitud, int horizontal) {
    if(horizontal) {
        if(y + longitud > 10) return 0;  // Se sale del tablero
        for(int i = 0; i < longitud; i++) {
            if(tablero[x][y + i] == BARCO) return 0;  // Colisión con otro barco
        }
    } else {
        if(x + longitud > 10) return 0;  // Se sale del tablero
        for(int i = 0; i < longitud; i++) {
            if(tablero[x + i][y] == BARCO) return 0;  // Colisión con otro barco
        }
    }
    return 1;
}

// Coloca un barco en el tablero
void colocarBarco(Estados_tablero_e tablero[10][10], Barco* barco, int x, int y, int horizontal) {
    barco->x = x;
    barco->y = y;
    barco->horizontal = horizontal;
    barco->colocado = 1;
    
    if(horizontal) {
        for(int i = 0; i < barco->longitud; i++) {
            tablero[x][y + i] = BARCO;
        }
    } else {
        for(int i = 0; i < barco->longitud; i++) {
            tablero[x + i][y] = BARCO;
        }
    }
}

// Elimina un barco del tablero
void eliminarBarco(Estados_tablero_e tablero[10][10], Barco* barco) {
    if(!barco->colocado) return;
    
    if(barco->horizontal) {
        for(int i = 0; i < barco->longitud; i++) {
            tablero[barco->x][barco->y + i] = AGUA;
        }
    } else {
        for(int i = 0; i < barco->longitud; i++) {
            tablero[barco->x + i][barco->y] = AGUA;
        }
    }
    barco->colocado = 0;
}

// Verifica si un barco está completamente destruido
int barcoDestruido(Estados_tablero_e tablero[10][10], Barco* barco) {
    if(!barco->colocado) return 0;
    
    int hits = 0;
    if(barco->horizontal) {
        for(int i = 0; i < barco->longitud; i++) {
            if(tablero[barco->x][barco->y + i] == HIT) hits++;
        }
    } else {
        for(int i = 0; i < barco->longitud; i++) {
            if(tablero[barco->x + i][barco->y] == HIT) hits++;
        }
    }
    
    return hits == barco->longitud;
}

// Muestra un barco destruido completo
void mostrarBarcoDestruido(Barco* barco, int player) {
    if(!barco->colocado) return;
    
    if(barco->horizontal) {
        for(int i = 0; i < barco->longitud; i++) {
            if(player == 1) {
                setCeldaPly1(barco->x, barco->y + i, 1);  // Mostrar como BARCO
            } else {
                setCeldaPly2(barco->x, barco->y + i, 1);  // Mostrar como BARCO
            }
        }
    } else {
        for(int i = 0; i < barco->longitud; i++) {
            if(player == 1) {
                setCeldaPly1(barco->x + i, barco->y, 1);  // Mostrar como BARCO
            } else {
                setCeldaPly2(barco->x + i, barco->y, 1);  // Mostrar como BARCO
            }
        }
    }
}

void seleccionPly1(){
    // Mostrar barcos ya colocados
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(tableroply1[i][j] == BARCO){
                setCeldaSeleccion(i, j, 1);
            } else {
                setCeldaSeleccion(i, j, 0);
            }
        }
    }
    
    // Mostrar preview del barco actual
    int longitud = TAMAÑO_BARCOS[barco_actual_1];
    int valid = puedeColocarBarco(tableroply1, preview_x, preview_y, longitud, preview_horizontal);
    
    if(preview_horizontal) {
        for(int i = 0; i < longitud && preview_y + i < 10; i++) {
            setCeldaSeleccion(preview_x, preview_y + i, valid ? 4 : 3);  // SELECTING o MISS si no válido
        }
    } else {
        for(int i = 0; i < longitud && preview_x + i < 10; i++) {
            setCeldaSeleccion(preview_x + i, preview_y, valid ? 4 : 3);  // SELECTING o MISS si no válido
        }
    }
    
    input_celda in_ = obtenerInputCeldaSeleccion();
    
    // Actualizar posición del preview con el mouse
    if(in_.x >= 0 && in_.y >= 0) {
        preview_x = in_.x;
        preview_y = in_.y;
    }
    
    // Mover con flechas del teclado
    if(IsKeyPressed(KEY_UP) && preview_x > 0) {
        preview_x--;
    }
    if(IsKeyPressed(KEY_DOWN) && preview_x < 9) {
        preview_x++;
    }
    if(IsKeyPressed(KEY_LEFT) && preview_y > 0) {
        preview_y--;
    }
    if(IsKeyPressed(KEY_RIGHT) && preview_y < 9) {
        preview_y++;
    }
    
    // Rotar con espacio
    if(IsKeyPressed(KEY_SPACE)) {
        preview_horizontal = !preview_horizontal;
        printf("Player 1: Barco rotado - %s\n", preview_horizontal ? "Horizontal" : "Vertical");
    }
    
    // Colocar con Enter
    if(IsKeyPressed(KEY_ENTER)) {
        if(puedeColocarBarco(tableroply1, preview_x, preview_y, longitud, preview_horizontal)) {
            colocarBarco(tableroply1, &barcos_ply1[barco_actual_1], preview_x, preview_y, preview_horizontal);
            barco_actual_1++;
            preview_x = 0;
            preview_y = 0;
            preview_horizontal = 1;
            printf("Player 1: Barco colocado! (%d/5)\n", barco_actual_1);
        } else {
            printf("Player 1: ¡No puedes colocar el barco ahí!\n");
        }
    }
    
    // Eliminar último barco con click derecho
    if(in_.click == 1 && barco_actual_1 > 0) {
        barco_actual_1--;
        eliminarBarco(tableroply1, &barcos_ply1[barco_actual_1]);
        printf("Player 1: Último barco eliminado\n");
    }
}

void selectionPly2(){
    // Mostrar barcos ya colocados
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(tableroply2[i][j] == BARCO){
                setCeldaSeleccion(i, j, 1);
            } else {
                setCeldaSeleccion(i, j, 0);
            }
        }
    }
    
    // Mostrar preview del barco actual
    int longitud = TAMAÑO_BARCOS[barco_actual_2];
    int valid = puedeColocarBarco(tableroply2, preview_x, preview_y, longitud, preview_horizontal);
    
    if(preview_horizontal) {
        for(int i = 0; i < longitud && preview_y + i < 10; i++) {
            setCeldaSeleccion(preview_x, preview_y + i, valid ? 4 : 3);
        }
    } else {
        for(int i = 0; i < longitud && preview_x + i < 10; i++) {
            setCeldaSeleccion(preview_x + i, preview_y, valid ? 4 : 3);
        }
    }
    
    input_celda in_ = obtenerInputCeldaSeleccion();
    
    if(in_.x >= 0 && in_.y >= 0) {
        preview_x = in_.x;
        preview_y = in_.y;
    }
    
    // Mover con flechas del teclado
    if(IsKeyPressed(KEY_UP) && preview_x > 0) {
        preview_x--;
    }
    if(IsKeyPressed(KEY_DOWN) && preview_x < 9) {
        preview_x++;
    }
    if(IsKeyPressed(KEY_LEFT) && preview_y > 0) {
        preview_y--;
    }
    if(IsKeyPressed(KEY_RIGHT) && preview_y < 9) {
        preview_y++;
    }
    
    if(IsKeyPressed(KEY_SPACE)) {
        preview_horizontal = !preview_horizontal;
        printf("Player 2: Barco rotado - %s\n", preview_horizontal ? "Horizontal" : "Vertical");
    }
    
    if(IsKeyPressed(KEY_ENTER)) {
        if(puedeColocarBarco(tableroply2, preview_x, preview_y, longitud, preview_horizontal)) {
            colocarBarco(tableroply2, &barcos_ply2[barco_actual_2], preview_x, preview_y, preview_horizontal);
            barco_actual_2++;
            preview_x = 0;
            preview_y = 0;
            preview_horizontal = 1;
            printf("Player 2: Barco colocado! (%d/5)\n", barco_actual_2);
        } else {
            printf("Player 2: ¡No puedes colocar el barco ahí!\n");
        }
    }
    
    if(in_.click == 1 && barco_actual_2 > 0) {
        barco_actual_2--;
        eliminarBarco(tableroply2, &barcos_ply2[barco_actual_2]);
        printf("Player 2: Último barco eliminado\n");
    }
}

void mainPly1(){
    input_celda in_ = getInputCeldaPly2(); 
    if(in_.click == 0 && in_.x >= 0 && in_.y >= 0 && 
       (tableroply2[in_.x][in_.y] != HIT && tableroply2[in_.x][in_.y] != MISS)){
        
        if(tableroply2[in_.x][in_.y] == BARCO){
            tableroply2[in_.x][in_.y] = HIT;
            cantidad_aciertos_1++;
            printf("Player 1: HIT! (%d aciertos)\n", cantidad_aciertos_1);
            checkWin();
            if(cantidad_aciertos_1 >= 17){
                printf("¡PLAYER 1 GANA!\n");
            }
        }
        else{
            tableroply2[in_.x][in_.y] = MISS;
            printf("Player 1: MISS\n");
            playerSelecting = 1;
        }
    }

    // Actualizar visualización
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(tableroply2[i][j] == AGUA){
                setCeldaPly2(i, j, 0);
            }
            else if(tableroply2[i][j] == MISS){
                setCeldaPly2(i, j, 3);
            }
        }
    }
    
    // Mostrar barcos destruidos completos
    for(int b = 0; b < 5; b++) {
        if(barcoDestruido(tableroply2, &barcos_ply2[b])) {
            mostrarBarcoDestruido(&barcos_ply2[b], 2);
        } else {
            // Mostrar solo HITs de barcos no destruidos
            if(barcos_ply2[b].colocado) {
                if(barcos_ply2[b].horizontal) {
                    for(int i = 0; i < barcos_ply2[b].longitud; i++) {
                        if(tableroply2[barcos_ply2[b].x][barcos_ply2[b].y + i] == HIT) {
                            setCeldaPly2(barcos_ply2[b].x, barcos_ply2[b].y + i, 2);
                        }
                    }
                } else {
                    for(int i = 0; i < barcos_ply2[b].longitud; i++) {
                        if(tableroply2[barcos_ply2[b].x + i][barcos_ply2[b].y] == HIT) {
                            setCeldaPly2(barcos_ply2[b].x + i, barcos_ply2[b].y, 2);
                        }
                    }
                }
            }
        }
    }
}

void mainPly2(){
    input_celda in_ = getInputCeldaPly1(); 
    if(in_.click == 0 && in_.x >= 0 && in_.y >= 0 && 
       (tableroply1[in_.x][in_.y] != HIT && tableroply1[in_.x][in_.y] != MISS)){
        
        if(tableroply1[in_.x][in_.y] == BARCO){
            tableroply1[in_.x][in_.y] = HIT;
            cantidad_aciertos_2++;
            printf("Player 2: HIT! (%d aciertos)\n", cantidad_aciertos_2);
            checkWin();
            if(cantidad_aciertos_2 >= 17){
                printf("¡PLAYER 2 GANA!\n");
            }
        }
        else{
            tableroply1[in_.x][in_.y] = MISS;
            printf("Player 2: MISS\n");
            playerSelecting = 0;
        }
    }

    // Actualizar visualización
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(tableroply1[i][j] == AGUA){
                setCeldaPly1(i, j, 0);
            }
            else if(tableroply1[i][j] == MISS){
                setCeldaPly1(i, j, 3);
            }
        }
    }
    
    // Mostrar barcos destruidos completos
    for(int b = 0; b < 5; b++) {
        if(barcoDestruido(tableroply1, &barcos_ply1[b])) {
            mostrarBarcoDestruido(&barcos_ply1[b], 1);
        } else {
            // Mostrar solo HITs de barcos no destruidos
            if(barcos_ply1[b].colocado) {
                if(barcos_ply1[b].horizontal) {
                    for(int i = 0; i < barcos_ply1[b].longitud; i++) {
                        if(tableroply1[barcos_ply1[b].x][barcos_ply1[b].y + i] == HIT) {
                            setCeldaPly1(barcos_ply1[b].x, barcos_ply1[b].y + i, 2);
                        }
                    }
                } else {
                    for(int i = 0; i < barcos_ply1[b].longitud; i++) {
                        if(tableroply1[barcos_ply1[b].x + i][barcos_ply1[b].y] == HIT) {
                            setCeldaPly1(barcos_ply1[b].x + i, barcos_ply1[b].y, 2);
                        }
                    }
                }
            }
        }
    }
}

void setUp(){
    comBarcos();
    barco_actual_1 = 0;
    barco_actual_2 = 0;
    cantidad_aciertos_1 = 0;
    cantidad_aciertos_2 = 0;
    playerSelecting = 0;
    preview_x = 0;
    preview_y = 0;
    preview_horizontal = 1;
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            tableroply1[i][j] = AGUA;
            tableroply2[i][j] = AGUA;
        }
    }
}

void checkWin(void) {
    if (cantidad_aciertos_1 >= 17) {
        ganador = 1;
        estado = GAME_OVER;
        return;
    }

    if (cantidad_aciertos_2 >= 17) {
        ganador = 2;
        estado = GAME_OVER;
        return;
    }
}


void Iniciar_juego(){
    Com_InterfazGrafica();
    setUp();
    estado = SELECTION;
    
    printf("=== CONTROLES ===\n");
    printf("Selección: Mouse O flechas para mover\n");
    printf("           ESPACIO para rotar\n");
    printf("           ENTER para colocar\n");
    printf("           Click derecho para eliminar último barco\n");
    printf("Juego:     Click izquierdo para atacar\n\n");
    
    while (!WindowShouldClose()) {

    setGameMode(estado);

    // SI EL JUEGO TERMINÓ
    if (estado == GAME_OVER) {
        DibInterface();
        if (IsKeyPressed(KEY_ENTER)) break;
        continue;
    }

    DibInterface();


        if(estado == SELECTION){
            if(barco_actual_1 < 5){
                seleccionPly1();
            }
            else{
                if(barco_actual_2 < 5){
                    selectionPly2();
                }
                else {
                    estado = MAIN_GAME;
                    printf("\n¡Comienza la batalla!\n");
                }
            }
        }
        if(estado == MAIN_GAME){
            if(playerSelecting){
                mainPly2();
            }
            else{
                mainPly1();
            }
        }
    }

    CloseWindow();
}