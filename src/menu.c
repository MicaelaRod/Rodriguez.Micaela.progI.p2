#include <stdio.h>
#include <stdlib.h>
#include "entradas.h"
#include "menu.h"

int elegirOpcionMenuPrincipal(){
	int opcion;





		system("cls");
		printf(" Menu:     \n");
		printf("_____________________________________________\n");
		printf("  1. Cargar Archivo\n");
		printf("  2. Imprimir lista\n");
		printf("  3. Asignar Tiempos\n");
		printf("  4. Filtrar por tipo\n");
		printf("  5. Mostrar duraciones.\n");
		printf("  6. Guardar peliculas.\n");
		printf("  7. Salir\n");

	getInt("Ingrese opcion ", "ERROR.Ingrese opcion valida", &opcion);

	return opcion;
}

int menuPrincipal(LinkedList *listaMovies) {
	int todoOk = 0;
	int option;
	char salir = 'n';
	char path[40];

	int flagLoad = 0;
	int flagMapGenero = 0;
	int flagMapD = 0;
	int flagSort = 0;
	int flagSave = 0;

	LinkedList *listaMapeada = ll_newLinkedList();
	LinkedList *listaClonada = ll_newLinkedList();

	if (listaMovies != NULL) {
		do {
			option = elegirOpcionMenuPrincipal();
			switch (option) {
			case 1:
				if (!flagLoad) {
					if (controller_loadFromText(listaMovies)) {
						flagLoad = 1;
						printf("Archivo cargado con exito!\n");
					}
				} else {
					printf("Los datos ya se han cargado!.\n");
				}
//LISTO
				break;
			case 2:

				if (flagLoad) {
					controller_imprimirMovies(listaMovies);
				} else {
					printf("Primero debe cargar el archivo para mostrarlo.!\n");
				}
				//LISTO
				break;
			case 3:
				if (flagMapD) {
					printf("Ya fuaron cargados!\n");
				} else {
					if (flagLoad) {
						listaMapeada = controller_asignarD(listaMovies);

						if (listaMapeada != NULL) {
							printf("Tiempos asignados con exito!!\n\n");

							controller_imprimirMovies(listaMovies);
							flagMapD = 1;
						}
					} else {
						printf("Primero debe cargar la lista!\n");
					}
				}


//LISTO
				break;
			case 4:
				if (flagMapGenero && flagMapD) {
					controller_filtrarPorGenero(listaMovies);
				} else {
					printf("Primero debe cargar las duraciones en la lista!\n");
				}

				break;

			case 5:

				if (flagMapGenero && flagMapD) {
					listaClonada = controller_ordenar(listaMapeada);

					if (listaClonada != NULL) {
						flagSort = 1;
					}

				} else {
					printf("Primero debe cargar las duraciones en la lista!\n");
				}

				if (flagLoad) {
					controller_imprimirMovies(listaMovies);
				} else {
					printf("Primero debe cargar el archivo para mostrarlo.!\n");
				}



				break;
			case 6:

				if (flagSort) {
					utn_getString(path, 30,
							"Por favor, ingrese el nombre con el que desea guardar el archivo: ",
							"ERROR. Por favor, ingrese el nombre con el que desea guardar el archivo: ",
							9);
					strcat(path, ".csv");
					controller_saveAsText(path, listaClonada);
					flagSave = 1;
				}


				break;
			case 7:

				system("cls");
				if (flagSave)


					printf("No puede salir sin guardar los datos \n");

				salir = getConfirmation("Esta seguro que desea salir? (s/n): ",
						"ERROR. Esta seguro que desea salir? (s/n): ");


				break;


			default:
				printf("Ingreso una opcion invalida. Vuelva a intentarlo.\n");
				break;
			}

			printf("Presione una tecla para continuar...\n");
			fflush(stdin);
			getchar();

		} while (salir == 'n');

		todoOk = 1;
	}

	ll_deleteLinkedList(listaMapeada);

	return todoOk;
}

int menuGeneros() {
	int opcion;

	system("cls");
	printf("_______________________________________\n");
	printf("      Generos:       \n");
	printf("_______________________________________\n");
	printf("1. Drama\n");
	printf("2. Comedia\n");
	printf("3. Accion\n");
	printf("4. Terror\n");

	getInt("Por favor ingrese el ID del genero que desea: ",
			"Ingrese nombre valido ", &opcion);

	return opcion;
}


