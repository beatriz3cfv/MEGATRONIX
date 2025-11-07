#include <stdio.h>

#define TAM_LINEA 8

typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

// Funciones

void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);

void VolcarCACHE(T_CACHE_LINE *tbl);

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque);

int main(){
    int globaltime = 0, numfallos = 0;
    unsigned char Simul_RAM[4096];



}

void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]){

}

void VolcarCACHE(T_CACHE_LINE *tbl){

}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque){

}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque){
    
}