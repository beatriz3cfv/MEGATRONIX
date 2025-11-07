#include <stdio.h>

#define TAM_LINEA 8

typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

// Funciones
// void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque);

// MAIN
int main(){
    // Inicializar datos
    int globaltime = 0, numfallos = 0;
    unsigned char Simul_RAM[4096];

    T_CACHE_LINE struct_lineas_cache[TAM_LINEA];

    for (int i = 0; i < TAM_LINEA; i++) {
        struct_lineas_cache[i].ETQ = 0xFF;
        for (int j = 0; j < TAM_LINEA; j++) {
            struct_lineas_cache[i].Data[j] = 0x23;
        }
    }

    for (int i = 0; i < TAM_LINEA; i++) {
        printf("ETQ: %02X\n", struct_lineas_cache[i].ETQ);
        for (int j = 0; j < TAM_LINEA; j++) {
            printf("%02X\n", struct_lineas_cache[i].Data[j]);
        }
    }

    // Abrir ficheros
}

// void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]){}

void VolcarCACHE(T_CACHE_LINE *tbl) {

}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque) {

}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque) {
    
}