#include "tareas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>



/*
 * Obtiene el número de la última tarea agregada en el archivo
 * 
 * Abre el archivo en modo lectura
 * Lee cada línea del archivo
 * Extrae el primer número de cada línea usando sscanf
 * Compara el número extraído contra el último guardado
 * Si es mayor, actualiza el último número
 * Al finalizar la lectura, devuelve el último número encontrado
*/
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


/* 
 * Agrega una nueva tarea al final del archivo
 *
 * Solicita al usuario los datos de la nueva tarea:
 * - Descripción
 * - Prioridad (número entre 1-3)
 * - Fecha de finalización (validando formato)
 * 
 * Obtiene el número de la última tarea con obtenerUltimoNumero()
 * Incrementa en 1 para asignar a la nueva tarea
 * 
 * Abre el archivo en modo append para escritura al final
 * Escribe la tarea en una nueva línea con el formato:
 *   numero,descripcion,prioridad,fecha,estado 
 * Cierra el archivo
 *
 * Imprime mensaje de éxito o error
*/ 
void agregarTarea(const char *nombreArchivo) // terminado
{
    // Obtener el número de la última tarea agregada
    int ultimoNumero = obtenerUltimoNumero(nombreArchivo);
    char descripcion[100];
    int prioridad1;
    char prioridad[20];
    char fecha[20];
    printf("Esta es la tarea numero %d\n", ultimoNumero + 1);
    printf("Ingrese la descripción de la tarea: ");
    scanf(" %99[^\n]", descripcion); // Lee la cadena hasta que encuentra en caracter de salto de linea

    // Limpia el búfer del teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Validación para que prioridad1 sea 1, 2 o 3
    do
    {
        printf("Ingrese el numero de la prioridad de la tarea : \n1. Alta\n2. Media\n3. Baja\n");
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


/*
 * Valida que un fecha tenga formato válido dd/mm/aaaa
 * 
 * Verifica con sscanf que tenga 3 enteros separados por /
 * Verifica rango de día, mes y año
 * Compara que no sea fecha anterior a hoy
 *
 * Retorna:
 * 1 si formato es válido
 * 0 si formato es inválido
*/
int validarFormatoFecha(const char *fecha) // terminado
{
    // Verifica que la fecha tenga el formato dd/mm/yyyy
    int dia, mes, anio;
    if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) == 3)
    {
        // Verifica rangos válidos para día, mes y año
        if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && anio >= 1900)
        {
            // Verifica que la fecha no sea anterior a la fecha actual
            time_t tiempoActual;
            struct tm *infoTiempo; // Estructura tm para checar el tiempo

            time(&tiempoActual);
            infoTiempo = localtime(&tiempoActual);

            int anioActual = infoTiempo->tm_year + 1900; /*La estructura tm tiene un miembro llamado
                                                         tm_year que representa el número de años transcurridos desde 1900.
                                                          Por lo tanto, para obtener el año actual, se suma 1900 al valor de tm_year.*/

            int mesActual = infoTiempo->tm_mon + 1; /*El miembro tm_mon de la estructura tm representa el número de meses
                                                     transcurridos desde enero (0) hasta diciembre (11).
                                                      Para obtener el mes actual, se suma 1 al valor de tm_mon.*/

            int diaActual = infoTiempo->tm_mday; // El miembro tm_mday de la estructura tm representa el día del mes (1-31).

            return (anio > anioActual || (anio == anioActual && (mes > mesActual || (mes == mesActual && dia >= diaActual))));
        }
    }
    return 0;
}


/*
 * Muestra todas las tareas pendientes en el archivo
 * 
 * Abre el archivo en modo lectura
 * Lee cada línea 
 * Extrae los campos número, descripción, prioridad y fecha con strtok
 * Imprime los campos en formato de tabla
 * 
 * Maneja errores en lectura de líneas
 *
 * Al finalizar cierra el archivo
*/
void mostrarTareas(const char *nombreArchivo) // terminado aunque quiero añadir un menu para mostrarlas dependiendo la prioridad o la fecha
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo != NULL)
    {
        printf("Lista de Tareas Pendientes:\n");
        printf("%-10s%-30s%-20s%-20s\n", "Numero", "Descripcion", "Prioridad", "Fecha de Entrega");

        char linea[200];
        while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL)
            {
                printf("%-10s%-30s%-20s%-20s\n", numero, descripcion, prioridad, fecha);
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


/*
 * Muestra las tareas con una fecha específica
 * 
 * Solicita al usuario una fecha y valida formato
 * Abre el archivo en modo lectura 
 * Lee cada línea comparando la fecha 
 * Imprime las tareas con fecha coincidente
 *
 * Maneja errores en lectura de líneas
 * 
 * Al finalizar cierra el archivo
*/
void mostrarTareasPorFecha(const char *nombreArchivo) {
    char fecha_consulta[20];
    FILE *archivo = fopen(nombreArchivo, "r");
    int encontradas = 0;

    if (archivo != NULL) {
        do {
            printf("Ingrese la fecha de finalización de la tarea (formato dd/mm/yyyy): ");
            scanf("%19s", fecha_consulta);

            if (!validarFormatoFecha(fecha_consulta)) {
                printf("Formato de fecha no válido. Inténtelo de nuevo.\n");
            }
        } while (!validarFormatoFecha(fecha_consulta));

        printf("\nLista de Tareas Pendientes:\n");
        printf("%-10s%-30s%-20s%-20s\n", "Numero", "Descripcion", "Prioridad", "Fecha de Entrega");

        char linea[200];
        while (fgets(linea, sizeof(linea), archivo) != NULL) {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL) {
                if (strcmp(fecha_consulta, fecha) == 0) {
                    printf("%-10s%-30s%-20s%-20s\n", numero, descripcion, prioridad, fecha);
                    encontradas = 1;
                }
            } else {
                printf("Error al leer la línea del archivo.\n");
            }
        }

        if (!encontradas) {
            printf("**No se encontraron tareas con la fecha especificada.**\n");
        }
    } else {
        printf("No se pudo abrir el archivo.\n");
    }

    fclose(archivo);
    printf("\n");
}


/*
 * Muestra las tareas con una prioridad específica
 * 
 * Solicita al usuario un número de prioridad (1-3)
 * Convierte el número a cadena de prioridad
 * Abre el archivo en modo lectura
 * Lee cada línea comparando la prioridad
 * Imprime las tareas con prioridad coincidente
 *
 * Maneja errores en lectura de líneas y prioridad no válida
 *
 * Al finalizar cierra el archivo
*/  
void mostrarTareasPorPrioridad(const char *nombreArchivo) // terminado
{
    int numPrioridad;
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo != NULL)
    {
        printf("Ingrese el número de prioridad a consultar (1: Alta, 2: Media, 3: Baja): ");
        if (scanf("%d", &numPrioridad) != 1 || numPrioridad < 1 || numPrioridad > 3)
        {
            printf("Prioridad no válida.\n");
            fclose(archivo);
            return;
        }

        char prioridadBuscada[20]; // Para almacenar la prioridad correspondiente al número

        // Asignar la cadena correspondiente a la prioridad seleccionada
        switch (numPrioridad)
        {
        case 1:
            strcpy(prioridadBuscada, "Alta");
            break;
        case 2:
            strcpy(prioridadBuscada, "Media");
            break;
        case 3:
            strcpy(prioridadBuscada, "Baja");
            break;
        default:
            break;
        }

        printf("Lista de Tareas Pendientes:\n");
        printf("%-10s%-30s%-20s%-20s\n", "Numero", "Descripcion", "Prioridad", "Fecha de Entrega");

        char linea[200];
        int tareasEncontradas = 0;

        while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL)
            {
                // Comparar prioridad en el archivo con la prioridad buscada
                if (strcmp(prioridad, prioridadBuscada) == 0)
                {
                    printf("%-10s%-30s%-20s%-20s\n", numero, descripcion, prioridad, fecha);
                    tareasEncontradas = 1;
                }
            }
            else
            {
                printf("Error al leer la línea del archivo.\n");
            }
        }

        if (!tareasEncontradas)
        {
            printf("No hay tareas con esa prioridad.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
    printf("\n");
}


/*
 * Marca una tarea como completada cambiando su estado a 1
 * 
 * Abre el archivo original y uno nuevo temporal en modo escritura
 * Lee cada línea del original
 * Si el número coincide con el indicado, cambia estado a 1
 * Escribe la línea modificada o original al temporal
 *
 * Al finalizar, cierra archivos, elimina original y renombra temporal
*/
void marcarComoCompletada(const char *nombreArchivo, int numeroCompletar)
{
    FILE *archivoEntrada = fopen(nombreArchivo, "r");
    FILE *archivoTemporal = fopen("temporal.txt", "w");

    if (archivoEntrada != NULL && archivoTemporal != NULL)
    {
        char linea[200];

        while (fgets(linea, sizeof(linea), archivoEntrada) != NULL)
        {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL)
            {
                int numeroTarea = atoi(numero);

                if (numeroTarea == numeroCompletar)
                {
                    // Cambiar el estado a completado (puedes ajustar el valor según tus necesidades)
                    fprintf(archivoTemporal, "%d,%s,%s,%s,%d\n", numeroTarea, descripcion, prioridad, fecha, 1);
                }
                else
                {
                    // Mantener la tarea sin cambios
                    fprintf(archivoTemporal, "%d,%s,%s,%s,%s", numeroTarea, descripcion, prioridad, fecha, estado);
                }
            }
            else
            {
                printf("Error al leer la línea del archivo.\n");
            }
        }

        fclose(archivoEntrada);
        fclose(archivoTemporal);

        remove(nombreArchivo);
        rename("temporal.txt", nombreArchivo);
        printf("Tarea marcada como completada correctamente.\n");
    }
    else
    {
        printf("No se pudo abrir algún archivo.\n");
    }
}


/*
 * Mueve las tareas completadas a otro archivo 
 * 
 * Abre el original, uno temporal y el de completadas en modo escritura
 * Lee cada línea verificando estado completado (distinto de 0)
 * Escribe la tarea al archivo de completadas con nueva numeración incremental
 * Escribe las pendientes al temporal con misma numeración
 *
 * Al finalizar, cierra archivos, elimina original y renombra temporal
*/
void guardarCompletadas(const char *nombreArchivo, const char *nombreArchivoCompletadas) {
    FILE *archivoEntrada = fopen(nombreArchivo, "r");
    FILE *archivoSalida = fopen("temporal.txt", "w");
    FILE *archivoCompletadas = fopen(nombreArchivoCompletadas, "a");

    if (archivoEntrada != NULL && archivoSalida != NULL && archivoCompletadas != NULL) {
        int nuevaNumeracionCompletadas = obtenerUltimoNumero(nombreArchivoCompletadas) + 1;

        char linea[200];
        while (fgets(linea, sizeof(linea), archivoEntrada) != NULL) {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estadoStr = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estadoStr != NULL) {
                int estado = atoi(estadoStr);

                if (estado != 0) {
                    // Mover la tarea al archivo de tareas completadas
                    fprintf(archivoCompletadas, "%d,%s,%s,%s,%d\n", nuevaNumeracionCompletadas, descripcion, prioridad, fecha, estado);
                    nuevaNumeracionCompletadas++;
                } else {
                    // Mantener la tarea en el archivo original con nueva numeración
                    fprintf(archivoSalida, "%d,%s,%s,%s,%d\n", obtenerUltimoNumero(nombreArchivo) + 1, descripcion, prioridad, fecha, estado);
                }
            } else {
                printf("Error al leer la línea del archivo.\n");
            }
        }

        fclose(archivoEntrada);
        fclose(archivoSalida);
        fclose(archivoCompletadas);

        // Actualizar el archivo original con las tareas pendientes
        remove(nombreArchivo);
        rename("temporal.txt", nombreArchivo);

        printf("Tareas completadas movidas correctamente al archivo de tareas completadas.\n");
    } else {
        printf("No se pudo abrir algún archivo.\n");
    }
}


/*
 * Reenumera las tareas de manera automática
 *
 * Abre el original y uno nuevo temporal en modo escritura
 * Lee cada línea y escribe al temporal con numeración incremental
 * 
 * Al finalizar, cierra archivos, elimina original y renombra temporal
*/
void ajustarNumeracionAutomatica(const char *nombreArchivo) {
    FILE *archivoEntrada = fopen(nombreArchivo, "r");
    FILE *archivoSalida = fopen("temporal.txt", "w");

    if (archivoEntrada != NULL && archivoSalida != NULL) {
        int nuevaNumeracion = 1;

        char linea[200];
        while (fgets(linea, sizeof(linea), archivoEntrada) != NULL) {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estadoStr = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estadoStr != NULL) {
                int estado = atoi(estadoStr);

                // Mantener la tarea en el archivo original con nueva numeración
                fprintf(archivoSalida, "%d,%s,%s,%s,%d\n", nuevaNumeracion, descripcion, prioridad, fecha, estado);
                nuevaNumeracion++;
            } else {
                printf("Error al leer la línea del archivo.\n");
            }
        }

        fclose(archivoEntrada);
        fclose(archivoSalida);

        // Actualizar el archivo original con las tareas pendientes y nueva numeración
        remove(nombreArchivo);
        rename("temporal.txt", nombreArchivo);

        printf("Numeración del archivo ajustada automáticamente.\n");
    } else {
        printf("No se pudo abrir algún archivo.\n");
    }
}

/*
 * Elimina una tarea especificando su número 
 *
 * Abre el original y uno nuevo temporal en modo escritura
 * Lee cada línea del original
 * Si el número no coincide con el indicado, escribe la línea al temporal
 * Si coincide, omite escribirla
 *
 * Al finalizar, cierra archivos, verifica si se eliminó 
*  y en ese caso elimina original y renombra temporal
*/
void eliminarTareaPorNumero(const char *nombreArchivo, int numeroEliminar)
{
    FILE *archivoEntrada = fopen(nombreArchivo, "r");
    FILE *archivoSalida = fopen("temporal.txt", "w");

    if (archivoEntrada != NULL && archivoSalida != NULL)
    {
        char linea[200];
        int nuevaNumeracion = 1; // Nueva numeración que reemplazará al número eliminado

        while (fgets(linea, sizeof(linea), archivoEntrada) != NULL)
        {
            char *numero = strtok(linea, ",");
            char *descripcion = strtok(NULL, ",");
            char *prioridad = strtok(NULL, ",");
            char *fecha = strtok(NULL, ",");
            char *estado = strtok(NULL, ",");

            if (numero != NULL && descripcion != NULL && prioridad != NULL && fecha != NULL && estado != NULL)
            {
                int numeroTarea = atoi(numero);

                if (numeroTarea == numeroEliminar)
                {
                    // No escribir la línea, ya que se está eliminando
                }
                else
                {
                    // Escribir la línea con la nueva numeración
                    fprintf(archivoSalida, "%d,%s,%s,%s,%s", nuevaNumeracion, descripcion, prioridad, fecha, estado);
                    nuevaNumeracion++;
                }
            }
            else
            {
                printf("Error al leer la línea del archivo.\n");
            }
        }

        fclose(archivoEntrada);
        fclose(archivoSalida);

        if (nuevaNumeracion > 1) // Verificar si se eliminó alguna tarea
        {
            remove(nombreArchivo);
            rename("temporal.txt", nombreArchivo);
            printf("Tarea eliminada correctamente.\n");
        }
        else
        {
            remove("temporal.txt");
            printf("No se encontró una tarea con el número especificado.\n");
        }
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}
