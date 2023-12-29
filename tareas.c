#include "tareas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Función para obtener el número de la última tarea agregada
int obtenerUltimoNumero(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    int ultimoNumero = 0;

    if (archivo != NULL)
    {
        char linea[100];
        while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
            int numero;
            if (sscanf(linea, "%d,", &numero) == 1)
            {
                ultimoNumero = numero;
            }
        }

        fclose(archivo);
    }

    return ultimoNumero;
}

void agregarTarea(const char *nombreArchivo)
{
    // Obtener el número de la última tarea agregada
    int ultimoNumero = obtenerUltimoNumero(nombreArchivo);

    // Incrementar el contador de tareas leídas hasta el momento
    int contador = ultimoNumero + 1;

    char descripcion[100];
    int prioridad1;
    char prioridad[20];
    char fecha[20];

    printf("Ingrese la descripción de la tarea: ");
    scanf(" %99[^\n]", descripcion); // Lee la cadena hasta que encuentra en caracter de salto de linea

    // Limpia el búfer del teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    // Validación para que prioridad1 sea 1, 2 o 3
    do
    {
        printf("Ingrese el numero de la prioridad de la tarea %d: \n1. Alta\n2. Media\n3. Baja\n", contador);
        if (scanf("%d", &prioridad1) != 1 || (prioridad1 < 1 || prioridad1 > 3))
        {
            printf("Por favor, ingrese un valor válido (1, 2 o 3).\n");

            // Limpia el búfer del teclado en caso de entrada no válida
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            prioridad1 = 0; // Reinicia prioridad1 para que el bucle continúe
        }
        else
        {
            // Convertir la prioridad a cadena
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
        }
    } while (prioridad1 < 1 || prioridad1 > 3);

    // Limpia el búfer del teclado
    // fflush(stdin);
    while ((c = getchar()) != '\n' && c != EOF)
        ;

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

    FILE *archivo = fopen(nombreArchivo, "a"); // Abre el archivo para escritura al final
    if (archivo != NULL)
    {
        fprintf(archivo, "%d,%s,%s,%s,%d\n", (obtenerUltimoNumero(nombreArchivo) + 1), descripcion, prioridad, fecha, 0);

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
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL)
            {
                int estadoInt = atoi(estado); // transforma la cadena estado en entero
                if (estadoInt == 0)
                {
                    printf("%s. %s,     PRIORIDAD: %s,      FECHA DE ENTREGA: %s\n",numero, descripcion, prioridad, fecha);                }
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
