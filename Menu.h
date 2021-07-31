#ifndef MENU_H
#define MENU_H

#define MENU_PRINCIPAL_LISTAR 1
#define MENU_PRINCIPAL_CARGAR_RAM 2
#define MENU_PRINCIPAL_ORDENAR_RAM 3
#define MENU_PRINCIPAL_ORDENAR_ARCHIVO 4
#define MENU_PRINCIPAL_BUSQ_BIN_RAM 5
#define MENU_PRINCIPAL_BUSQ_SEQ_ARCHIVO 6
#define MENU_PRINCIPAL_SALIR 7

#define MENU_ORD_ARCHIVO_SHELLSORT 1
#define MENU_ORD_ARCHIVO_QUICKSORT 2

#include <vector>
#include "Libro.h"

using namespace std;

class Menu
{
	public:
		Menu();
		int menu_principal();
		int listar_libros();
		int cargar_libros_ram(vector<Libro> &libros_vec);
		int ordenamiento_ram(vector<Libro> &libros_vec);
	protected:
};

#endif
