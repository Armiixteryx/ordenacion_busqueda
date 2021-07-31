#include <iostream>
#include "Menu.h"

using namespace std;

int main(int argc, char** argv) {
	Menu menu;
	
	int opcion_menu = 0;
	
	while (opcion_menu != MENU_PRINCIPAL_SALIR) {
		opcion_menu = menu.menu_principal();
		switch (opcion_menu) {
			case MENU_PRINCIPAL_LISTAR:
				break;
			case MENU_PRINCIPAL_CARGAR_RAM:
				break;
			case MENU_PRINCIPAL_ORDENAR_RAM:
				break;
			case MENU_PRINCIPAL_ORDENAR_ARCHIVO:
				break;
			case MENU_PRINCIPAL_BUSQ_BIN_RAM:
				break;
			case MENU_PRINCIPAL_BUSQ_SEQ_ARCHIVO:
				break;
			case MENU_PRINCIPAL_SALIR:
				break;
		}
	}

	return 0;
}

