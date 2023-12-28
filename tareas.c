#include "tareas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void agregarTarea(const char *nombreArchivo)
{
    char descripcion[100];
    int prioridad1;
    char prioridad[20];
    char fecha[20];

    printf("Ingrese la descripción de la tarea: ");
    scanf(" %99[^\n]", descripcion); // Lee la cadena hasta que encuentra en caracter de salto de linea

    // Limpia el búfer del teclado
    fflush(stdin);

    printf("Ingrese el numero de la prioridad de la tarea: \n1. Alta\n2. Media\n3. Baja\n");
    scanf("%d", &prioridad1);

    switch (prioridad1)
    {
    case 1:
        strcpy(prioridad, "Alta");
        break;
    case 2:
        strcpy(prioridad, "Media");
        break;
    case 3:
        strcpy(prioridad, "Baja");
        break;
    default:
        break;
    }

    // Limpia el búfer del teclado
    // fflush(stdin);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Lo que hace este do/while es pedir una fecha hasta que se ingrese una con el formato correcto
    do
    {
        printf("Ingrese la fecha de finalización de la tarea (formato dd/mm/yyyy): ");
        scanf("%19s", fecha);

        if (!validarFormatoFecha(fecha))
        {
            printf("Formato de fecha no válido. Inténtelo de nuevo.\n");
        }
    } while (!validarFormatoFecha(fecha));

    FILE *archivo = fopen(nombreArchivo, "a");//Abre el archivo para escritura al final
    if (archivo != NULL)
    {
        fprintf(archivo, "%s,%s,%s,0\n", descripcion, prioridad, fecha);
        fclose(archivo);
        printf("Tarea agregada correctamente.\n");
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

int validarFormatoFecha(const char *fecha)
{
    // Verifica que la fecha tenga el formato dd/mm/yyyy
    int dia, mes, anio;
    if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) == 3)
    {
        // Verifica rangos válidos para día, mes y año
        return (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && anio >= 1900);
    }
    return 0;
}

// Función para mostrar todas las tareas en el archivo
void mostrarTareas(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo != NULL)
    {
        printf("Lista de Tareas Pendientes:\n");
        char linea[100];
        while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
            char *descripcion = strtok(linea, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL)
            {
                int estadoInt = atoi(estado);//transforma la cadena estado en entero
                if (estadoInt == 0)
                {
                    printf("Descripción: %s, Prioridad: %s, Fecha de Entrega: %s, Estado: %s\n", descripcion, prioridad, fecha, estado);
                }
            }
            else
            {
                printf("Error al leer la línea del archivo.\n");
            }
        }
        fclose(archivo);
        printf("\n");
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}



// Función para marcar una tarea como completada en el archivo
void marcarComoCompletada(const char *nombreArchivo, const char *descripcion)
{
    // Implementa la lógica para marcar una tarea como completada
}

// Función para eliminar una tarea del archivo
void eliminarTarea(const char *nombreArchivo, const char *descripcion)
{
    // Implementa la lógica para eliminar una tarea
}
