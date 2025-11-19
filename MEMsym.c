#include <stdio.h>

#define TAM_LINEA 8
#define TAM_RAM 4096

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
    unsigned char Simul_RAM[TAM_RAM];

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

    // Abrir fichero Binario y guardarlo en Simul_RAM
    FILE *fBin = fopen("/MEGATRONIX/CONTENTS_RAM.bin", "rb");

    if(fBin == NULL){
        printf("Ha ocurrido un error al intentar abrir el fichero binario");
    }

    size_t lineasLeidas = fread(Simul_RAM, sizeof(unsigned char), TAM_RAM, fBin); 
    fclose(fBin);

    //Abrir fichero de texto
    FILE *fTxt = fopen("dirs_memoria.txt", "r");

    if(fTxt == NULL){
        printf("Ha ocurrido un error al intentar abrir el fichero de texto");
    }

    //char *fgets(char *str, int n, FILE *stream)

    fclose(fTxt);
}

// void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]){}

void VolcarCACHE(T_CACHE_LINE *tbl) {

}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque) {

}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque) {
    
}