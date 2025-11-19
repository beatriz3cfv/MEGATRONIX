#include <stdio.h>

#define TAM_LINEA 8
#define TAM_RAM 4096
#define BITS_ETQ 5
#define BITS_LINEA 3
#define BITS_PALABRA 4
#define BITS_BUS 12

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
    int *globaltime = 0, *numfallos = 0;
    unsigned char Simul_RAM[TAM_RAM];
    char lineaMem[256];
    int *ETQ = 0, int *bloque = 0, int *linea = 0, int *palabra = 0;

    T_CACHE_LINE struct_lineas_cache[TAM_LINEA];

    for (int i = 0; i < TAM_LINEA; i++) {
        struct_lineas_cache[i].ETQ = 0xFF;
        for (int j = 0; j < TAM_LINEA; j++) {
            struct_lineas_cache[i].Data[j] = 0x23;
        }
    }

    /*for (int i = 0; i < TAM_LINEA; i++) {
        printf("ETQ: %02X\n", struct_lineas_cache[i].ETQ);
        for (int j = 0; j < TAM_LINEA; j++) {
            printf("%02X\n", struct_lineas_cache[i].Data[j]);
        }
    }*/

    // Abrir fichero Binario y guardarlo en Simul_RAM
    FILE *fBin = fopen("accesos_memoria_y CONTENTS_RAM/CONTENTS_RAM.bin", "rb");

    if(fBin == NULL){
        perror("Error al abrir el binario");
        printf("Ha ocurrido un error al intentar abrir el fichero binario\n");
        return -1;
    }

    size_t lineasLeidas = fread(Simul_RAM, sizeof(unsigned char), TAM_RAM, fBin); 
    fclose(fBin);

    //Abrir fichero de texto
    FILE *fTxt = fopen("accesos_memoria_y CONTENTS_RAM/accesos_memoria.txt", "r");

    if(fTxt == NULL){
        printf("Ha ocurrido un error al intentar abrir el fichero de texto\n");
        return -1;
    }

    //leer cada linea del fichero de direcciones de memoria
    while(fgets(lineaMem, sizeof(lineaMem), fTxt)){
        globaltime++;
        //printf("%s", lineaMem);

        //AQUI HAY MONTON D ERRORES PQ HAY Q CAMBIAR LINEAMEM A UN HEX

        *palabra = lineaMem & 0xF; //0xF -> 15 -> 1111, 4 bits, el valor maximo con 4 bits, lee de derecha a izq por eso son los ultimos 4 bits
        *linea = (lineaMem >> 4) & 0x7; //0x7 -> 111, 3 bits; lo de lineaMem >> 4 'quita' los ultimos 4 bits (los q leimos para palabra), ahora lo q lee seran los nuevos ultimos bits -> linea
        *ETQ = (lineaMem >> 7) & 0x1F; //0x1F -> 16 -> 1 1111, 5 bits

        printf("direccion: %s, etq: %d, linea: %d, palabra: %d", lineaMem, ETQ, linea, palabra);
    }

    fclose(fTxt);
}

// void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]){}

void VolcarCACHE(T_CACHE_LINE *tbl) {

}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque) {

}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque) {
    //esto aun no tengo ni idea, es un intento de entender que es cada cosa. se que el numfallos va fuera, es para acordarse de hacerlo

    //numfallos++;
    //printf(“T: %d, Fallo de CACHE %d, ADDR %04X Label %X linea %02X palabra %02X bloque %02X\n”, globaltime, numfallos, tbl, MRAM, ETQ, linea, bloque);
    //globaltime += 20;
}