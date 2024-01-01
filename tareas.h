#ifndef TAREAS_H
#define TAREAS_H

// Funciones para operar en la lista de tareas
void agregarTarea(const char *nombreArchivo);
void mostrarTareas(const char *nombreArchivo);
void marcarComoCompletada(const char *nombreArchivo, int numeroCompletar);
void guardarCompletadas(const char *nombreArchivo, const char *nombreArchivoCompletadas);
void eliminarTareaPorNumero(const char *nombreArchivo, int numeroEliminar);
void mostrarTareasPorFecha(const char *nombreArchivo);
void mostrarTareasPorPrioridad(const char *nombreArchivo);
void ajustarNumeracionAutomatica(const char *nombreArchivo) ;

int validarFormatoFecha(const char *fecha);
#endif // TAREAS_H