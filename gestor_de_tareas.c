// programa para hacer listas y guardarlas en un archivo de texto
#include "tareas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menuMostrar();

int main()
{   
    int numero;
    const char *nombreArchivo = "tareas.txt";
    const char *nombreArchivoCompletadas = "tareas_completadas.txt";
    /*
        printf("Introduce un numero.\n");
        scanf("%d", &numero);
        marcarComoCompletada(nombreArchivo, numero);
    */
    //guardarCompletadas(nombreArchivo, nombreArchivoCompletadas);
   ajustarNumeracionAutomatica(nombreArchivo);
   
    return 0;
}

int menuMostrar()
{
    const char *nombreArchivo = "tareas.txt";
    int opcion;
    char fecha[20];
    char prioridad[20];

    do
    {
        // Menú de opciones
        printf("Menu de Opciones:\n");
        printf("1. Mostrar todas las tareas\n");
        printf("2. Mostrar tareas por fecha\n");
        printf("3. Mostrar tareas por prioridad\n");
        printf("0. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarTareas(nombreArchivo);
            break;
        case 2:

            mostrarTareasPorFecha(nombreArchivo);
            break;
        case 3:
           mostrarTareasPorPrioridad(nombreArchivo);
            break;
        case 0:
            printf("Saliendo del programa. ¡Hasta luego!\n");
            break;
        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
            break;
        }

    } while (opcion != 0);

    return 0;
}