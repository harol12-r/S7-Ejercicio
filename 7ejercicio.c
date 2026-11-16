#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 5


char nombres[MAX_PRODUCTOS][30];
float tiempos[MAX_PRODUCTOS];
float recursosPorProd[MAX_PRODUCTOS];
int demandas[MAX_PRODUCTOS];
int cantidadProductos = 0;


void registrarProducto();
void mostrarProductos();
void buscarYEditarProducto();
void buscarYEliminarProducto();
void evaluarProduccion();

int main() {
    int opcion;

    do {
        printf("\n--- FABRICA DE COMPONENTES ELECTRONICOS ---\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar lista de productos\n");
        printf("3. Buscar y editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Evaluar tiempo, recursos y demanda\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                mostrarProductos();
                break;
            case 3:
                buscarYEditarProducto();
                break;
            case 4:
                buscarYEliminarProducto();
                break;
            case 5:
                evaluarProduccion();
                break;
            case 6:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nError: Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}


void registrarProducto() {
    if (cantidadProductos >= MAX_PRODUCTOS) {
        printf("\nError: Ya se han registrado los 5 productos maximos.\n");
        return;
    }

    
    while (getchar() != '\n');

    printf("\nIngrese el nombre del producto %d: ", cantidadProductos + 1);
    scanf("%s", nombres[cantidadProductos]);

 
    do {
        printf("Ingrese el tiempo de fabricacion por unidad (horas): ");
        scanf("%f", &tiempos[cantidadProductos]);
        if (tiempos[cantidadProductos] < 0) {
            printf("Error: El tiempo no puede ser negativo. Intente de nuevo.\n");
        }
    } while (tiempos[cantidadProductos] < 0);

    
    do {
        printf("Ingrese la cantidad de recursos necesarios por unidad: ");
        scanf("%f", &recursosPorProd[cantidadProductos]);
        if (recursosPorProd[cantidadProductos] < 0) {
            printf("Error: Los recursos no pueden ser negativos. Intente de nuevo.\n");
        }
    } while (recursosPorProd[cantidadProductos] < 0);

   
    do {
        printf("Ingrese la cantidad demandada (numero entero): ");
        scanf("%d", &demandas[cantidadProductos]);
        if (demandas[cantidadProductos] < 0) {
            printf("Error: La demanda no puede ser negativa. Intente de nuevo.\n");
        }
    } while (demandas[cantidadProductos] < 0);

    cantidadProductos++;
    printf("¡Producto registrado exitosamente!\n");
}

void mostrarProductos() {
    if (cantidadProductos == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\n%-15s | %-10s | %-18s | %-10s\n", "Nombre", "Tiempo/U", "Recursos/U", "Demanda");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < cantidadProductos; i++) {
        printf("%-15s | %-10.2f | %-18.2f | %-10d\n",
               nombres[i], tiempos[i], recursosPorProd[i], demandas[i]);
    }
}


void buscarYEditarProducto() {
    if (cantidadProductos == 0) {
        printf("\nNo hay productos para editar.\n");
        return;
    }

    while (getchar() != '\n');
    char nombreBuscado[30];
    printf("\nIngrese el nombre del producto que desea buscar para editar: ");
    scanf("%s", nombreBuscado);

    int encontrado = -1;
    for (int i = 0; i < cantidadProductos; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Producto encontrado. Ingrese los nuevos datos:\n");
    printf("Nuevo nombre: ");
    scanf("%s", nombres[encontrado]);

    do {
        printf("Nuevo tiempo de fabricacion por unidad: ");
        scanf("%f", &tiempos[encontrado]);
        if (tiempos[encontrado] < 0) printf("Error: No puede ser negativo.\n");
    } while (tiempos[encontrado] < 0);

    do {
        printf("Nuevos recursos por unidad: ");
        scanf("%f", &recursosPorProd[encontrado]);
        if (recursosPorProd[encontrado] < 0) printf("Error: No puede ser negativo.\n");
    } while (recursosPorProd[encontrado] < 0);

    do {
        printf("Nueva cantidad demandada: ");
        scanf("%d", &demandas[encontrado]);
        if (demandas[encontrado] < 0) printf("Error: No puede ser negativa.\n");
    } while (demandas[encontrado] < 0);

    printf("¡Producto actualizado con exito!\n");
}


void buscarYEliminarProducto() {
    if (cantidadProductos == 0) {
        printf("\nNo hay productos para eliminar.\n");
        return;
    }

    while (getchar() != '\n');
    char nombreBuscado[30];
    printf("\nIngrese el nombre del producto que desea eliminar: ");
    scanf("%s", nombreBuscado);

    int encontrado = -1;
    for (int i = 0; i < cantidadProductos; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = encontrado; i < cantidadProductos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        tiempos[i] = tiempos[i + 1];
        recursosPorProd[i] = recursosPorProd[i + 1];
        demandas[i] = demandas[i + 1];
    }

    cantidadProductos--;
    printf("¡Producto eliminado exitosamente!\n");
}


void evaluarProduccion() {
    if (cantidadProductos == 0) {
        printf("\nNo hay productos registrados para evaluar.\n");
        return;
    }

    float tiempoTotalReq = 0;
    float recursosTotalesReq = 0;

    for (int i = 0; i < cantidadProductos; i++) {
        tiempoTotalReq += tiempos[i] * demandas[i];
        recursosTotalesReq += recursosPorProd[i] * demandas[i];
    }

    float tiempoDisponible, recursosDisponibles;
    
    do {
        printf("\nIngrese el tiempo total disponible en la fabrica (horas): ");
        scanf("%f", &tiempoDisponible);
        if (tiempoDisponible < 0) printf("Error: El tiempo disponible no puede ser negativo.\n");
    } while (tiempoDisponible < 0);

    do {
        printf("Ingrese la cantidad total de recursos disponibles: ");
        scanf("%f", &recursosDisponibles);
        if (recursosDisponibles < 0) printf("Error: Los recursos disponibles no pueden ser negativos.\n");
    } while (recursosDisponibles < 0);

    printf("\n--- REPORTE DE EVALUACION DE PRODUCCION ---\n");
    printf("Tiempo total requerido: %.2f horas\n", tiempoTotalReq);
    printf("Recursos totales requeridos: %.2f\n", recursosTotalesReq);

    if (tiempoTotalReq <= tiempoDisponible && recursosTotalesReq <= recursosDisponibles) {
        printf("ESTADO: ¡La fabrica SI puede cumplir con la demanda con los limites actuales!\n");
    } else {
        printf("ESTADO: La fabrica NO puede cumplir con la demanda.\n");
        if (tiempoTotalReq > tiempoDisponible) {
            printf("- Faltan %.2f horas de tiempo de produccion.\n", tiempoTotalReq - tiempoDisponible);
        }
        if (recursosTotalesReq > recursosDisponibles) {
            printf("- Faltan %.2f unidades de recursos.\n", recursosTotalesReq - recursosDisponibles);
        }
    }
}