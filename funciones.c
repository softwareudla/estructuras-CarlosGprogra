#include "funciones.h"
#include <ctype.h>
#include <string.h>

int validarSoloLetras(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha(cadena[i]) && !isspace(cadena[i])) {
            return 0;
        }
    }
    return 1;
}

int pedirNumeroPositivo() {
    int numero, valido;
    do {
        valido = scanf("%d", &numero);
        getchar(); // Limpiar buffer

        if (!valido || numero < 0) {
            printf("Error Solo se permiten numeros positivos. Intentelo nuevamente.\n");
            while (getchar() != '\n'); // Limpiar buffer si hay caracteres no válidos
        }
    } while (!valido || numero < 0);
    return numero;
}

void registrarLibro(Libro *biblioteca, int *cantidadLibros) {
    if (*cantidadLibros >= MAX_LIBROS) {
        printf("No se pueden agregar mas libros. Limite alcanzado.\n");
        return;
    }

    Libro nuevoLibro;

    // Ingreso de ID del libro con validación para que sea un número positivo
    do {
        printf("Ingrese el ID del libro (solo numeros positivos): ");
        if (scanf("%d", &nuevoLibro.id) != 1 || nuevoLibro.id <= 0) {
            printf("Error El ID debe ser un numero positivo. Intentelo nuevamente.\n");
            while(getchar() != '\n'); // Limpiar el buffer de entrada
        } else {
            // Verificar que el ID no se repita
            int idExistente = 0;
            for (int i = 0; i < *cantidadLibros; i++) {
                if (biblioteca[i].id == nuevoLibro.id) {
                    printf("El ID ya existe. Intente con otro.\n");
                    idExistente = 1;
                    break;
                }
            }

            if (!idExistente) {
                break; // Salir del bucle si el ID es válido y no repetido
            }
        }
    } while (1);

    // Limpiar el buffer de entrada después de scanf
    while (getchar() != '\n');  // Limpiar el buffer para leer el siguiente fgets correctamente

    // Ingreso del título del libro
    printf("Ingrese el titulo del libro: ");
    fgets(nuevoLibro.titulo, sizeof(nuevoLibro.titulo), stdin);
    strtok(nuevoLibro.titulo, "\n");  // Eliminar salto de línea al final

    // Ingreso del autor con validación de solo letras
    do {
        printf("Ingrese el autor del libro (solo letras y espacios): ");
        fgets(nuevoLibro.autor, sizeof(nuevoLibro.autor), stdin);
        strtok(nuevoLibro.autor, "\n");  // Eliminar salto de línea

        if (!validarSoloLetras(nuevoLibro.autor)) {
            printf("Error: El nombre del autor solo puede contener letras y espacios. Intentelo nuevamente.\n");
        }
    } while (!validarSoloLetras(nuevoLibro.autor));

    // Ingreso del año de publicación con validación positiva
    do {
        printf("Ingrese el ano de publicacion (solo numeros positivos): ");
        if (scanf("%d", &nuevoLibro.anio) != 1 || nuevoLibro.anio <= 0) {
            printf("Error: El ano debe ser un numero positivo. Intentelo nuevamente.\n");
            while(getchar() != '\n'); // Limpiar el buffer de entrada
        } else {
            break;
        }
    } while (1);

    // Limpiar el buffer de entrada después de scanf
    while (getchar() != '\n');  // Limpiar el buffer para evitar problemas con futuros fgets

    // Establecer el estado del libro
    strcpy(nuevoLibro.estado, "Disponible");

    // Agregar el libro al arreglo y actualizar la cantidad
    biblioteca[*cantidadLibros] = nuevoLibro;
    (*cantidadLibros)++;

    printf("Libro registrado exitosamente.\n");
}




void mostrarLibros(const Libro *biblioteca, int cantidadLibros) {
    if (cantidadLibros == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-10s %-15s\n", "ID", "Titulo", "Autor", "Ano", "Estado");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < cantidadLibros; i++) {
        printf("%-5d %-30s %-20s %-10d %-15s\n",
               biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               biblioteca[i].anio,
               biblioteca[i].estado);
    }
}

void mostrarMenu() {
    printf("\n--- MENU ---\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado del libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
}

void buscarLibro(const Libro *biblioteca, int cantidadLibros) {
    int opcion;
    printf("Buscar por:\n1. ID\n2. Titulo\nSeleccione una opcion: ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1) {
        int id;
        printf("Ingrese el ID del libro: ");
        id = pedirNumeroPositivo();  // Validar que el ID no sea negativo

        for (int i = 0; i < cantidadLibros; i++) {
            if (biblioteca[i].id == id) {
                printf("\nLibro encontrado:\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAno: %d\nEstado: %s\n",
                       biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
                       biblioteca[i].anio, biblioteca[i].estado);
                return;
            }
        }
        printf("Libro no encontrado.\n");
    } else if (opcion == 2) {
        char titulo[100];
        printf("Ingrese el titulo del libro: ");
        fgets(titulo, sizeof(titulo), stdin);
        strtok(titulo, "\n");

        for (int i = 0; i < cantidadLibros; i++) {
            if (strcasecmp(biblioteca[i].titulo, titulo) == 0) {
                printf("\nLibro encontrado:\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAno: %d\nEstado: %s\n",
                       biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor,
                       biblioteca[i].anio, biblioteca[i].estado);
                return;
            }
        }
        printf("Libro no encontrado.\n");
    } else {
        printf("Opcion invalida.\n");
    }
}

void actualizarEstado(Libro *biblioteca, int cantidadLibros) {
    int id;
    printf("Ingrese el ID del libro a actualizar (solo numeros): ");
    id = pedirNumeroPositivo();  // Validar que el ID no sea negativo

    for (int i = 0; i < cantidadLibros; i++) {
        if (biblioteca[i].id == id) {
            if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
                strcpy(biblioteca[i].estado, "Prestado");
            } else {
                strcpy(biblioteca[i].estado, "Disponible");
            }
            printf("Estado actualizado exitosamente.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

void eliminarLibro(Libro *biblioteca, int *cantidadLibros) {
    int id;
    printf("Ingrese el ID del libro a eliminar (solo numeros): ");
    id = pedirNumeroPositivo();  // Validar que el ID no sea negativo

    for (int i = 0; i < *cantidadLibros; i++) {
        if (biblioteca[i].id == id) {
            for (int j = i; j < *cantidadLibros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            (*cantidadLibros)--; // Reducir la cantidad de libros
            printf("Libro eliminado exitosamente.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}