#include <iostream>
#include "Menu.h"
#include "Archivo.h"
#include "Libro.h"
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	srand(time(NULL));

	Menu menu;

	int opcion_menu = 0;
	
	vector<Libro> libros_vec;

	while (opcion_menu != MENU_PRINCIPAL_SALIR) {
		opcion_menu = menu.menu_principal();
		switch (opcion_menu) {
			case MENU_PRINCIPAL_LISTAR:
				menu.listar_libros();
				break;
			case MENU_PRINCIPAL_CARGAR_RAM:
				menu.cargar_libros_ram(libros_vec);
				break;
			case MENU_PRINCIPAL_ORDENAR_RAM:
				menu.ordenamiento_ram(libros_vec);
				break;
			case MENU_PRINCIPAL_ORDENAR_ARCHIVO:
				break;
			case MENU_PRINCIPAL_BUSQ_BIN_RAM:
				menu.busq_bin_ram(libros_vec);
				break;
			case MENU_PRINCIPAL_BUSQ_SEQ_ARCHIVO:
				menu.busq_seq_archivos();
				break;
			case MENU_PRINCIPAL_GENERAR_LIBROS:
				menu.generar_libros_random(libros_vec);
				break;
			case MENU_PRINCIPAL_LISTAR_LIBROS_RAM:
				menu.listar_libros_ram(libros_vec);
			case MENU_PRINCIPAL_SALIR:
				break;
		}
	}

	return 0;
}

