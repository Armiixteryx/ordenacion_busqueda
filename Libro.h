#ifndef LIBRO_H
#define LIBRO_H

#include <string.h>
#include <iostream>
#include "Archivo.h"

#define ARCHIVO_LIBRO_NOMBRE "libro.dat"
#define CADENA_MAX 40
#define CANTIDAD_LIBROS_MIN 1
#define LIBROS_ERR_MIN_CANT_ALCANZADA -1

class Libro
{
	public:
		Libro();
		Libro(const char * titulo, const char * cota, const char * autor, int cantidad_disponible);

		char * GetCota();
		char * GetTitulo();
		char * GetAutor();
		int GetCantidadDisponible();

		void SetCota(char * cota);
		void SetTitulo(char * titulo);
		void SetAutor(char * autor);
		void SetCantidadDisponible(int cantidad);
		
		void IncrementarCantidadDisponible();
		int DecrementarCantidadDisponible();

		static int AgregarDeConsola(TArchivo<Libro> * archivo);
		static int ModificarDeConsola(TArchivo<Libro> * archivo);
		static int EliminarDeConsola(TArchivo<Libro> * archivo);
		static int ConsultarConsola(TArchivo<Libro> * archivo);

		void HacerEncabezado();
		void Mostrar(long);
		
		static Libro GetDefault();
		bool IsDefault();
		
		// SOBRECARGAS //
		bool operator ==(const Libro &p) const;
		bool operator <(const Libro &b) const;
		bool operator >(const Libro &b) const;
		bool operator <=(const Libro &b) const;
		bool operator >=(const Libro &b) const;
	protected:
		char cota[CADENA_MAX];
		char titulo[CADENA_MAX];
		char autor[CADENA_MAX];
		int cantidad_disponible;
};

#endif
