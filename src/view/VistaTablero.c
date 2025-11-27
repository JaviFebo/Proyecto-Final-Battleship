#include "VistaTablero.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

const char* miss_path  = "assets/miss.png";
const char* water_path =  "assets/water.png";
const char* boat_path =  "assets/boat.png";
const char* hit_path =  "assets/hit.png";
const char* select_path =  "assets/selecting.png";

Texture2D loadAndScale(char* filePath){
    Image img = LoadImage(filePath);
    ImageResize(&img,img.width*SCALE, img.height*SCALE);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

int isClickedIzq(Rectangle rect){
    Vector2 mouse = GetMousePosition();
    int collided = CheckCollisionPointRec(mouse, rect);
    int BotonIzq =IsMouseButtonPressed(MOUSE_LEFT_BUTTON); 
    return collided && BotonIzq;
}

int isClickedDer(Rectangle rect){
    Vector2 mouse = GetMousePosition();
    int collided = CheckCollisionPointRec(mouse, rect);
    int BotonDer =IsMouseButtonPressed(MOUSE_RIGHT_BUTTON); 
    return collided && BotonDer;
}
void comCeldaV(Celda_v* celda, Vector2 posicion){
    if(!celda) return;
    celda->boat = loadAndScale(boat_path);
    celda->hit = loadAndScale(hit_path);
    celda->miss = loadAndScale(miss_path);
    celda->water = loadAndScale(water_path);
    celda->selcting = loadAndScale(select_path);
    celda->posicion = posicion;
}


void comTableroV(Tablero_v* tablero){
       if (!tablero) return;

    const int CONTADOR = 10;
    const Vector2 base = tablero->posicion;

    //Columna de letras (vertical a la izquierda)
    Vector2 posLetras = (Vector2){ base.x, base.y + 16 * SCALE };
    int margenIzq = 0;  // ancho máximo de las letras para desplazar el tablero

    for (int i = 0; i < CONTADOR; i++) {
        char path[64];
        snprintf(path, sizeof(path), "assets/letters/%c.png", 'a' + i);

        tablero->cols[i].textura = loadAndScale(path);
        tablero->cols[i].posicion = posLetras;

        // Avanza hacia abajo usando la ALTURA real de cada letra
        posLetras.y += tablero->cols[i].textura.height;

        // Actualiza el margen izquierdo (por si las letras tienen distintos anchos)
        if (tablero->cols[i].textura.width > margenIzq) {
            margenIzq = tablero->cols[i].textura.width;
        }
    }

    //Fila de números (horizontal arriba)
    Vector2 posNumeros = (Vector2){ base.x + margenIzq, base.y };
    int MargenSuper = 0;   // alto máximo de los números para bajar el tablero

    for (int i = 0; i < CONTADOR; i++) {
        char path[64];
        snprintf(path, sizeof(path), "assets/numbers/number_%d.png", i + 1);

        tablero->filas[i].textura = loadAndScale(path);
        tablero->filas[i].posicion = posNumeros;

        // Avanza a la derecha usando el anxho real de cada número
        posNumeros.x += tablero->filas[i].textura.width;

        // Actualiza el margen superior
        if (tablero->filas[i].textura.height > MargenSuper) {
            MargenSuper = tablero->filas[i].textura.height;
        }
    }

    //Celdas del tablero 
    const Vector2 origenCuadricula = (Vector2){ base.x + margenIzq, base.y + MargenSuper };

    float celdaW = 0.0f, celdaH = 0.0f;
    Vector2 p = origenCuadricula;

    for (int i = 0; i < TAMAÑO_TABLERO; ++i) {
        p.x = origenCuadricula.x; // reinicia X al iniciar cada fila
        for (int j = 0; j < TAMAÑO_TABLERO; ++j) {
            comCeldaV(&(tablero->celdas[i][j]), p);

            // Cachea tamaño de celda tras la primera inicialización
            if (i == 0 && j == 0) {
                celdaW = (float) tablero->celdas[0][0].boat.width;
                celdaH = (float) tablero->celdas[0][0].boat.height;
            }

            // Avanza en X usando el ancho de celda conocido
            p.x += (celdaW > 0.0f) ? celdaW : (float) tablero->celdas[i][j].boat.width;
        }
        // Avanza en Y usando el alto de celda conocido
        p.y += (celdaH > 0.0f) ? celdaH : (float) tablero->celdas[i][0].boat.height;
    }
}


void dibColFil(Col_v* col){
    if(!col)return;

    int pos_x = col->posicion.x;
    int pos_y = col->posicion.y;
    
    DrawTexture(col->textura, pos_x, pos_y, WHITE);
}

void dibTableroV(Tablero_v* tablero){
    if(!tablero) return;
    for(int i = 0; i < TAMAÑO_TABLERO; ++i){
        for(int j = 0; j < TAMAÑO_TABLERO; ++j){
            dibCeldaV(&tablero->celdas[i][j]);
        }

        dibColFil(&tablero->filas[i]);
        dibColFil(&tablero->cols[i]);
    }
}    

void dibCeldaV(Celda_v* celda){
    if(!celda) return;
    int estado = celda->state;
    Texture2D textura;
    switch (estado)
    {
    case 0:textura = celda->water;break;
    case 1: textura = celda->boat; break;
    case 2: textura = celda->hit; break;
    case 3: textura = celda->miss; break;
    case 4: textura = celda->selcting;break;
    default: break;
    }

    DrawTexture(textura, celda->posicion.x, celda->posicion.y, WHITE);

}

Rectangle getCeldaRect(Celda_v* celda){
    Rectangle rect;
    if(!celda)return rect;
    rect.width = celda->boat.width;
    rect.height = celda->boat.height;
    rect.x = celda->posicion.x;
    rect.y = celda->posicion.y;
    return rect;
}


input_celda checkCeldas(Tablero_v* tablero){
    
    input_celda input = {
        .x = -1,
        .y = -1,
        .click = -1
    };
    if(!tablero) return input;
    for(int i = 0; i < TAMAÑO_TABLERO; ++i){
        for(int j = 0; j < TAMAÑO_TABLERO; ++j){
            Rectangle rect = getCeldaRect(&tablero->celdas[i][j]);
            if(isClickedIzq(rect)){
                printf("Clicked l\n");
                input.x = i;
                input.y = j;
                input.click = 0;
                return input;
            }
            if(isClickedDer(rect)){
                printf("Clicked r\n");
                input.x = i;
                input.y = j;
                input.click = 1;
                return input;
            }
        }
    }
    return input;
}