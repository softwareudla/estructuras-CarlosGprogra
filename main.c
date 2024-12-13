#include "funciones.h"

int main() {
    Libro biblioteca[MAX_LIBROS];
    int cantidadLibros = 0;
    int opcion;

    do {
        mostrarMenu();
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        if (cantidadLibros == 0 && opcion != 1 && opcion != 6) {
            printf("Debe registrar al menos un libro para realizar esta accion.\n");
            continue;
        }

        switch (opcion) {
            case 1:
                registrarLibro(biblioteca, &cantidadLibros);
                break;
            case 2:
                mostrarLibros(biblioteca, cantidadLibros);
                break;
            case 3:
                buscarLibro(biblioteca, cantidadLibros);
                break;
            case 4:
                actualizarEstado(biblioteca, cantidadLibros);
                break;
            case 5:
                eliminarLibro(biblioteca, &cantidadLibros);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}
