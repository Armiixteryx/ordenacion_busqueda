#include "Menu.h"
#include <iostream>
#include "Utils.h"

using namespace std;

Menu::Menu() {
}

int Menu::menu_principal() {
	int opcion = 0;

	do {
		system("cls");
		cout << "Ordenacion y busqueda" << endl;
		Utils::imprimir_separador('=');
		cout << "1. Listar libros." << endl;
		cout << "2. Cargar libros en RAM." << endl;
		cout << "3. Ordenar libros en RAM." << endl;
		cout << "4. Ordenar libros en archivo." << endl;
		cout << "5. Busqueda binaria en libros en RAM." << endl;
		cout << "6. Busqueda secuencial en libros en archivo." << endl;
		cout << "7. Salir." << endl;
		cout << "Su opcion (1-7): ";
		
		cin >> opcion;
		cin.ignore();

		if (opcion < MENU_PRINCIPAL_LISTAR || opcion > MENU_PRINCIPAL_SALIR) {
			cout << "Opcion incorrecta. Intente nuevamente." << endl;
			system("pause");
		}
	} while (opcion < MENU_PRINCIPAL_LISTAR || opcion > MENU_PRINCIPAL_SALIR);

	return opcion;
}

