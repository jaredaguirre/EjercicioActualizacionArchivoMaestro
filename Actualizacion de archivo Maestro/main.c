#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    /*Generamos los archivos*/
    FILE * pb = fopen("master.dat", "wb");
    FILE * pt = fopen("novedades.txt", "wt");

    grabarArchivos(pb, pt);

    pb = fopen("master.dat", "rb");
    mostrarArchivo(pb);

    actualizarMaster();

    pb = fopen("master.dat", "rb");
    mostrarArchivo(pb);
    fclose(pb);
    fclose(pt);
    return 0;
}
