#ifndef TAREAS_H
#define TAREAS_H

// Funciones para operar en la lista de tareas
void agregarTarea(const char *nombreArchivo);
void mostrarTareas(const char *nombreArchivo);
void marcarComoCompletada(const char *nombreArchivo, const char *descripcion);
void eliminarTarea(const char *nombreArchivo, const char *descripcion);


// funciones para validar datos
int validarFormatoFecha(const char *fecha);

#endif // TAREAS_H