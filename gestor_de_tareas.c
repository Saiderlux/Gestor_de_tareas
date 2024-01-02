// programa para hacer listas y guardarlas en un archivo de texto
#include "tareas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuPrincipal(const char *nombreArchivo);
void menuConsultar(const char *nombreArchivo);
void marcarTareaCompletada(const char *nombreArchivo);

int main()
{
    const char *nombreArchivo = "tareas.txt";
    menuPrincipal(nombreArchivo);
    return 0;
}

void menuPrincipal(const char *nombreArchivo)
{

    int opcion;
    int numero;

    do
    {

        printf("\n*** MENU PRINCIPAL ***\n");
        printf("1. Añadir tarea\n");
        printf("2. Marcar tarea completada\n");
        printf("3. Consultar tareas\n");
        printf("4. Eliminar tarea\n");
        printf("5. Salir\n");

        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarTarea(nombreArchivo);
            break;

        case 2:
            marcarTareaCompletada(nombreArchivo);
            break;

        case 3:
            menuConsultar(nombreArchivo);
            break;

        case 4:
            printf("Introduce el número de la tarea que deseas eliminar\n");
            scanf("%d", &numero);
            eliminarTareaPorNumero(nombreArchivo,numero);
            ajustarNumeracionAutomatica(nombreArchivo);
            break;

        case 5:
            printf("\nSaliendo...\n");
            break;

        default:
            printf("\nOpcion no valida\n");
        }

    } while (opcion != 5);
}

void menuConsultar(const char *nombreArchivo)
{
    const char *nombreArchivoCompletadas = "tareas_completadas.txt";
    int opcion;

    do
    {

        printf("\n** CONSULTAR TAREAS **\n");
        printf("1. Mostrar tareas pendientes\n");
        printf("2. Mostrar pendientes por prioridad\n");
        printf("3. Mostrar prendientes por fecha\n");
        printf("4. Mostrar tareas completadas\n");
        printf("5. Regresar\n");

        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarTareas(nombreArchivo);
            break;

        case 2:
            mostrarTareasPorPrioridad(nombreArchivo);
            break;

        case 3:
            mostrarTareasPorFecha(nombreArchivo);
            break;

        case 4:
            mostrarTareas(nombreArchivoCompletadas);
            break;

        case 5:
            printf("\nRegresando...\n");
            break;
        default:
            printf("\nOpcion no valida\n");
        }

    } while (opcion != 5);
}

void marcarTareaCompletada(const char *nombreArchivo)
{
    char opcion;
    const char *nombreArchivoCompletadas = "tareas_completadas.txt";
    do
    {
        printf("\n");
        // Mostrar las tareas disponibles
        mostrarTareas(nombreArchivo);

        // Código para solicitar número y llamar funciones
        printf("Ingrese el número de la tarea que desea marcar como completada (S para salir): ");
        scanf(" %c", &opcion);

        if (opcion != 'S' && opcion != 's')
        {
            int numero = atoi(&opcion);
            if (numero > 0)
            {
                // Marcar la tarea como completada
                marcarComoCompletada(nombreArchivo, numero);

                // Guardar las tareas completadas
                guardarCompletadas(nombreArchivo, nombreArchivoCompletadas);

                // Ajustar la numeración automática
                ajustarNumeracionAutomatica(nombreArchivo);
            }
            else
            {
                printf("Opción no válida. Ingrese un número de tarea válido o 'S' para salir.\n");
            }
        }

    } while (opcion != 'S' && opcion != 's');
}