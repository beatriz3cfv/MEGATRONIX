# Simulador de caché de mapeo directo en C

Simulador de una memoria caché de mapeo directo que lee una secuencia de
direcciones de memoria, registra aciertos y fallos y calcula el tiempo medio
de acceso.

## Configuración simulada
- RAM: 4096 bytes (direcciones de 12 bits)
- Caché: 8 líneas de 16 bytes (128 bytes)
- Dirección: `ETQ (5 bits) | línea (3 bits) | palabra (4 bits)`
- Tiempo: 1 ciclo por acierto, +20 ciclos por fallo (carga del bloque)

## Compilar y ejecutar
```bash
gcc -Wall -Wextra -o memsym MEMsym.c
./memsym
```

## Entrada y salida
- `data/CONTENTS_RAM.bin`: contenido inicial de la RAM
- `data/accesos_memoria.txt`: una dirección en hexadecimal por línea
- Por terminal: cada acceso (acierto o fallo), el estado de la caché tras
  cada uno y un resumen con accesos totales, fallos y tiempo medio
- `data/CONTENTS_CACHE.bin`: volcado final de la caché

Ejemplo (`examples/logcache.txt`):
```
T: 1, Fallo de CACHE 1, ADDR 022E Label 4 linea 02 palabra 0E bloque 22
Cargando el bloque 22 en la linea 02
T: 21, Acierto de CACHE, ADDR 022E Label 4 linea 02 palabra 0E DATO 6F
```

Los bytes leídos en cada acceso forman un mensaje de texto que se muestra
al final de la ejecución.
