#ifndef MENU_H
#define MENU_H

#define MENU_PRINCIPAL_LISTAR 1
#define MENU_PRINCIPAL_CARGAR_RAM 2
#define MENU_PRINCIPAL_ORDENAR_RAM 3
#define MENU_PRINCIPAL_ORDENAR_ARCHIVO 4
#define MENU_PRINCIPAL_BUSQ_BIN_RAM 5
#define MENU_PRINCIPAL_BUSQ_SEQ_ARCHIVO 6
#define MENU_PRINCIPAL_GENERAR_LIBROS 7
#define MENU_PRINCIPAL_LISTAR_LIBROS_RAM 8
#define MENU_PRINCIPAL_SALIR 9

#define MENU_ORD_ARCHIVO_SHELLSORT 1
#define MENU_ORD_ARCHIVO_QUICKSORT 2
#define MENU_ORD_ARCHIVO_NO_CARGADO -1

#define MAX_LIBROS_GENERAR 60

#include <vector>
#include "Libro.h"
#include "Ordenamiento.h"

using namespace std;

class Menu
{
	public:
		Menu();
		int menu_principal();
		int listar_libros();
		int cargar_libros_ram(vector<Libro> &libros_vec);
		int ordenamiento_ram(vector<Libro> &libros_vec);
		int busq_bin_ram(vector<Libro> &libros_vec);
		int busq_seq_archivos();
		int generar_libros_random(vector<Libro> &libros_vec);
		int listar_libros_ram(vector<Libro> &libros_vec);
	protected:
};

#endif
