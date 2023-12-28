// programa para hacer listas y guardarlas en un archivo de texto
#include "tareas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    const char *nombreArchivo = "tareas.txt";

    agregarTarea(nombreArchivo);
    mostrarTareas(nombreArchivo);

    return 0;
}
