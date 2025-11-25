#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_LINEA 16
#define TAM_RAM 4096

typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

// Funciones
void LimpiarCACHE(T_CACHE_LINE tbl[TAM_LINEA]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque);
void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque);

// MAIN
int main(){
    // Inicializar datos
    int globaltime = 0, numfallos = 0, hit = 0, accesos = 0;
    int ETQ = 0, bloque = 0, linea = 0, palabra = 0;
    int itexto = 0; // index de caracteres dentro del texto
    unsigned char Simul_RAM[TAM_RAM];
    unsigned int hex = 0;
    char lineaMem[256];
    char texto[100];

    T_CACHE_LINE tbl[TAM_LINEA];
    LimpiarCACHE(tbl);

    // Abrir fichero Binario y guardarlo en Simul_RAM
    FILE *fBin = fopen("accesos_memoria_y CONTENTS_RAM/CONTENTS_RAM.bin", "rb");

    if(fBin == NULL){
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
        accesos++;
        //printf("%s", lineaMem);

        hex = (unsigned long) strtol(lineaMem, NULL, 16);
        ParsearDireccion(hex, &ETQ, &palabra, &linea, &bloque);

        //printf("direccion: %0X, etq: %d, linea: %d, palabra: %d, bloque: %d\n", hex, ETQ, linea, palabra, bloque);
        
    if(tbl[linea].ETQ == ETQ){
            // hit++;
            printf("T: %d, Acierto de CACHE, ADDR %04X Label %X linea %02X palabra %02X DATO %02X\n", globaltime, hex, ETQ, linea, palabra, tbl[linea].Data[palabra]);
            
        } else {
            numfallos++;
            printf("T: %d, Fallo de CACHE %d, ADDR %04X Label %X linea %02X palabra %02X bloque %02X\n", globaltime, numfallos, hex, ETQ, linea, palabra, bloque);
            globaltime += 20;

            printf("Cargando el bloque %X en la linea %02X\n", bloque, linea);
            TratarFallo(tbl, Simul_RAM, ETQ, linea, bloque);

            printf("T: %d, Acierto de CACHE, ADDR %04X Label %X linea %02X palabra %02X DATO %02X\n", globaltime, hex, ETQ, linea, palabra, tbl[linea].Data[palabra]);
        }

        if (itexto < 100) {
            texto[itexto++] = tbl[linea].Data[palabra];
            texto[itexto] = '\0';
        }
    }

    fclose(fTxt);

    VolcarCACHE(tbl);

    sleep(1);
    printf("Accesos totales: %d; Fallos: %d; Tiempo medio: %.2f \n", accesos, numfallos, (float) globaltime/accesos);
    
    //Debajo, otro mensaje con el texto leído carácter a carácter desde la caché
    printf("Texto leído: %s \n", texto);
    
    // Volcar la caché en el fichero .bin
    FILE *fConBin = fopen("accesos_memoria_y CONTENTS_RAM/CONTENTS_CACHE.bin", "wb");
    if(fBin == NULL){
        printf("Ha ocurrido un error al intentar abrir el fichero binario\n");
        return -1;
    }
    for (int i = 0; i < 8; i++) { // 8 lineas
        fwrite(tbl[i].Data, sizeof(unsigned char), TAM_LINEA, fConBin);
    }

    fclose(fConBin);
    return 0;
}

void LimpiarCACHE(T_CACHE_LINE tbl[TAM_LINEA]){
    for (int i = 0; i < 8; i++) { // numero de lineas
        tbl[i].ETQ = 0xFF;
        for (int j = 0; j < TAM_LINEA; j++) {
            tbl[i].Data[j] = 0x23;
        }
    }
}

void ParsearDireccion(unsigned int addr, int *ETQ, int *palabra, int *linea, int *bloque) {
    *palabra = addr & 0xF; //0xF -> 15 -> 1111, 4 bits, el valor maximo con 4 bits, lee de derecha a izq por eso son los ultimos 4 bits
    *linea = (addr >> 4) & 0x7; //0x7 -> 111, 3 bits; lo de lineaMem >> 4 'quita' los ultimos 4 bits (los q leimos para palabra), ahora lo q lee seran los nuevos ultimos bits -> linea
    *ETQ = (addr >> 7) & 0x1F; //0x1F -> 16 -> 1 1111, 5 bits

    *bloque = (addr >> 4) & 0xFF; //el bloque será (creo) la etiqueta mas la linea
}

void VolcarCACHE(T_CACHE_LINE *tbl) {
    for (int i = 0; i < 8; i++) { // 8 lineas
        printf("%02X   Datos: ", tbl[i].ETQ);

        for (int j = TAM_LINEA - 1; j >= 0; j--) { // de mayor a menor
            printf("%02X ", tbl[i].Data[j]);
        }
        printf("\n");
    } 
}

void TratarFallo(T_CACHE_LINE *tbl, char *MRAM, int ETQ, int linea, int bloque) {
    int direccion_inicio_RAM = bloque * TAM_LINEA;
    tbl[linea].ETQ = ETQ; // actualizar etiqueta

    for (int i = 0; i < TAM_LINEA; i++) {
        tbl[linea].Data[i] = MRAM[direccion_inicio_RAM + i]; // cada byte del bloque de ram a cada posicion de la linea de cache
    }

}