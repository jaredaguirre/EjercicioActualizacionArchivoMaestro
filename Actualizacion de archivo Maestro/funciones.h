#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

/*Estructura del archivo Maestro*/
typedef struct
{
    int id;
    char nombre[35];
    int cant;
    float precio;
}tProducto;

/*Estructura del archivo Movimiento*/
typedef struct
{
    int id,
        cant;
    char tipo; //venta o reposicion
}tMovimiento;

void grabarArchivos(FILE *, FILE *);
void actualizarMaster(void);
void mostrarArchivo(FILE *);

#endif // FUNCIONES_H_INCLUDED
