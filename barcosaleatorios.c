
// Creacion del codigo que controla la aparicion aleatoria de los barcos


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GRID_SIZE 10   // Tamaño del tablero

// Funcion para generar una fila aleatoria
	int random_row() {
    return rand() % GRID_SIZE;
}

// Funcion para generar una columna aleatoria
int random_col() {
    return rand() % GRID_SIZE;
}

// Funcion para colocar un barco en la cuadricula
bool lugar_barco(char barco, int size, char cuadricula[GRID_SIZE][GRID_SIZE]) {
    int row = random_row();
    int col = random_col();
    bool is_vertical = rand() % 2; // 0 = horizontal, 1 = vertical

    // Verificar si cabe en la cuadricula
    if (is_vertical) {
        if (row + size > GRID_SIZE)
            return false;

        // Verificar si el espacio esta libre
        for (int i = 0; i < size; i++) {
            if (cuadricula[row + i][col] != '~')
                return false;
        }

        // Colocar el barco
        for (int i = 0; i < size; i++) {
            cuadricula[row + i][col] = barco;
        }
    } else {
        if (col + size > GRID_SIZE)
            return false;

        // Verificar si el espacio esta libre
        for (int i = 0; i < size; i++) {
            if (cuadricula[row][col + i] != '~')
                return false;
        }

        // Colocar el barco
        for (int i = 0; i < size; i++) {
            cuadricula[row][col + i] = barco;
        }
    }

    return true;
}

// Inicializa el tablero con agua
void init_cuadricula(char cuadricula[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cuadricula[i][j] = '~'; // '~' representa agua
        }
    }
}

// Muestra la cuadricula
void print_cuadricula(char cuadricula[GRID_SIZE][GRID_SIZE]) {
    printf("  ");
    for (int j = 0; j < GRID_SIZE; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c ", cuadricula[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // Inicializa la semilla aleatoria

    char cuadricula[GRID_SIZE][GRID_SIZE];
    init_cuadricula(cuadricula);

    // Ejemplo de barcos: símbolo y tamaño
    char barcos[] = {'A', 'B', 'C'};
    int tamanos[] = {5, 4, 3};
    int num_barcos = 3;

    // Colocar los barcos
    for (int i = 0; i < num_barcos; i++) {
        bool lugar = false;
        while (!lugar) {
            lugar = lugar_barco(barcos[i], tamanos[i], cuadricula);
        }
    }

    // Mostrar el tablero final
    print_cuadricula(cuadricula);

    return 0;
}

	

