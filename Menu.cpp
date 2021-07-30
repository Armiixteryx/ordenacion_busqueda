#include "Menu.h"
#include <iostream>
#include "Utils.h"

using namespace std;

Menu::Menu() {
}

int Menu::menu_principal() {
	cout << "Ordenacion y busqueda" << endl;
	Utils::imprimir_separador('=');
	cout << "1. Listar libros." << endl;
	cout << "2. Cargar libros en RAM." << endl;
	cout << "3. Ordenar libros en RAM." << endl;
	cout << "4. Ordenar libros en archivo." << endl;
	cout << "5. Busqueda binaria en libros en RAM." << endl;
	cout << "6. Busqueda secuencial en libros en archivo." << endl;
	cout << "7. Salir." << endl;
	cout << "Su opcion: ";
	
	//int opcion = opcion

	return 0;
}

