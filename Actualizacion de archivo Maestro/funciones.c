#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void grabarArchivos(FILE *b, FILE *t)
{
    tProducto prod[] = {
        {243, "Pera", 32, 34.5},
        {1283, "Manzana", 89, 56.7},
        {11, "Papa", 67, 56.8},
        {1676, "Batata", 78, 78.4},
        {198, "Chocolate", 45, 23.4}
    };

    tMovimiento mov[] = {
        {298, 45, 'v'},
        {243, 32, 'v'},
        {1676, 21, 'r'},
        {1799, 23, 'v'},
        {1444, 77, 'r'}
    };

    /*Grabado del array completo*/
    fwrite(prod, sizeof(prod), 1, b);
    /*Grabado del archivo de texto usando el array completo*/
    for(int i = 0; i < 5; i++)
    {
        fprintf(t, "%05d %03d %c\n", mov[i].id, mov[i].cant, mov[i].tipo);
    }

    fclose(b);
    fclose(t);

}

void actualizarMaster(void)
{
    tMovimiento temp_t;
    tProducto temp_b;

    FILE * b = fopen("master.dat","r+b");
    FILE * t = fopen("novedades.txt", "rt");
    FILE * n = fopen("mov_con_error.txt", "wt");

    int found;
    char cad[13];

    while(fgets(cad, 13, t))
    {
        found = 0;
        sscanf(cad, "%d %d %c", &temp_t.id, &temp_t.cant, &temp_t.tipo);
        fread(&temp_b, sizeof(tProducto), 1, b);
        while(!feof(b))
        {
            if(temp_b.id == temp_t.id)
            {
                /*Si se encontro coincidencia, marcamos un flag de encontrado y reemplazamos el dato entero*/
                found = 1;
                if(temp_t.tipo == 'v')
                    temp_b.cant-=temp_t.cant;
                else temp_b.cant+=temp_t.cant;
                fseek(b, -sizeof(tProducto), SEEK_CUR);
                fwrite(&temp_b, sizeof(tProducto), 1, b);
                fseek(b, 0L, SEEK_SET);
                break;
            }
            fread(&temp_b, sizeof(tProducto), 1, b);
        }
        fseek(b, 0L, SEEK_SET);
        if(found == 0)
        {
            fprintf(n, "%05d %02d %c\n", temp_t.id, temp_t.cant, temp_t.tipo);
        }
    }
    fclose(b);
    fclose(n);
    fclose(t);
}


void mostrarArchivo(FILE *b)
{
    tProducto temp;
    fread(&temp, sizeof(tProducto), 1, b);
    while(!feof(b))
    {
        printf("%05d | %-12s | %03d | %.2f\n", temp.id, temp.nombre, temp.cant, temp.precio);
        fread(&temp, sizeof(tProducto), 1, b);
    }

    fclose(b);
}
