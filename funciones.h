#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 20

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[20]; 
} Libro;

void registrarLibro(Libro *biblioteca, int *cantidadLibros);
void mostrarLibros(const Libro *biblioteca, int cantidadLibros);
void buscarLibro(const Libro *biblioteca, int cantidadLibros);
void actualizarEstado(Libro *biblioteca, int cantidadLibros);
void eliminarLibro(Libro *biblioteca, int *cantidadLibros);
void mostrarMenu();

#endif 