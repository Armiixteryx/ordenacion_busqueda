#include "Menu.h"
#include <iostream>
#include "Utils.h"
#include <vector>
#include "Archivo.h"
#include "Libro.h"
#include "Ordenamiento.h"
#include <ctime>

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

int Menu::listar_libros() {
	system("cls");
	string nombre_archivo;
	cout << "Ingrese nombre del archivo (default: " << ARCHIVO_LIBRO_NOMBRE << "): ";
	getline(cin, nombre_archivo);
	if (nombre_archivo.empty()) {
		nombre_archivo = ARCHIVO_LIBRO_NOMBRE;
	}
	TArchivo<Libro> archivo_libro(nombre_archivo.c_str());
	int result = archivo_libro.Listar();
	if (result == ARCHIVO_ERR_ABRIR) {
		cout << "Error al abrir archvo: " << nombre_archivo;
		cout << ": El archivo no se ha encontrado." << endl;
		system("pause");
		return ARCHIVO_ERR_ABRIR;
	}
	system("pause");
	
	return 0;
}

int Menu::cargar_libros_ram(vector<Libro> &libros_vec) {
	system("cls");
	cout << "CARGAR LIBROS EN RAM" << endl;
	Utils::imprimir_separador('=');
	
	string nombre_archivo;
	cout << "Ingrese nombre del archivo (default: " << ARCHIVO_LIBRO_NOMBRE << "): ";
	getline(cin, nombre_archivo);
	if (nombre_archivo.empty()) {
		nombre_archivo = ARCHIVO_LIBRO_NOMBRE;
	}
	TArchivo<Libro> archivo(nombre_archivo.c_str());

	int idx = 0;

	bool fin = false;

	while (!fin) {
		switch (archivo.Acceder(idx)) {
			case ARCHIVO_ERR_ABRIR:
				cout << "Error al abrir archvo: " << nombre_archivo;
				cout << ": El archivo no se ha encontrado." << endl;
				system("pause");
				break;
			case ARCHIVO_ERR_EOF:
				fin = true;
				break;
			case 0:
				libros_vec.push_back(*archivo.GetBuf());
				idx += 1;
				break;
		}
	}

	cout << "Libros cargados: " << libros_vec.size() << endl;
	system("pause");

	return 0;
}

int Menu::ordenamiento_ram(vector<Libro> &libros_vec) {
	int opcion = 0;
	do {
		system("cls");
		cout << "ORDENAR LIBROS EN RAM" << endl;
		Utils::imprimir_separador('=');
		if (libros_vec.empty()) {
			cout << "Por favor, cargue primero los libros en RAM" << endl;
			system("pause");
			return MENU_ORD_ARCHIVO_NO_CARGADO;
		}
		system("cls");
		cout << "ORDENAMIENTO EN RAM" << endl;
		Utils::imprimir_separador('=');
		cout << "Seleccione el metodo de ordenamiento a usar." << endl;
		cout << "1. ShellSort." << endl;
		cout << "2. QuickSort." << endl;
		cout << "Su opcion (1-2): ";

		cin >> opcion;
		cin.ignore();

		if (opcion < MENU_ORD_ARCHIVO_SHELLSORT || opcion > MENU_ORD_ARCHIVO_QUICKSORT) {
			cout << "Opcion no valida. Intente nuevamente." << endl;
			system("pause");
		}
	} while (opcion < MENU_ORD_ARCHIVO_SHELLSORT || opcion > MENU_ORD_ARCHIVO_QUICKSORT);
	
	clock_t t;

	switch (opcion) {
		case MENU_ORD_ARCHIVO_SHELLSORT:
			{
				/*
				int testcase[] = {15, 67, 8, 16, 44, 27, 12, 35, 56, 21, 13, 28, 60, 36, 7, 10};
				const int testcase_length = sizeof(testcase) / sizeof(testcase[0]);
				//Ordenamiento::shell_sort(testcase, testcase_length);
				Ordenamiento::quick_sort_recursivo(testcase, testcase_length);
				cout << "DEBUG SHOWCASE: Ordenado: ";
				for (int i = 0; i < testcase_length; i++) {
					cout << testcase[i] << " ";
				}
				cout << endl;
				system("pause");
				*/
				t = clock();
				Ordenamiento::shell_sort(&libros_vec[0], libros_vec.size());
				break;
			}
		case MENU_ORD_ARCHIVO_QUICKSORT:
			t = clock();
			Ordenamiento::quick_sort_recursivo(&libros_vec[0], libros_vec.size());
			break;
	}

	t = clock() - t;

	cout << "Los libros en RAM han sido ordenados!" << endl;
	cout << "Duracion (segs): " << ((float) t) / CLOCKS_PER_SEC << endl;
	cout << "Duracion (cpu clocks): " << t << endl;
	system("pause");
	return 0;
}

