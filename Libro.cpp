#include "Libro.h"
#include <string.h>
#include <iostream>
#include "Archivo.h"
#include "Utils.h"

Libro::Libro()
{
	/*
	this->titulo[0] = '\0';
	this->cota[0] = '\0';
	this->autor = "";
	*/
	this->cantidad_disponible = CANTIDAD_LIBROS_MIN;
}

Libro::Libro(char * titulo, char * cota, char * autor, int cantidad_disponible)
{
	strcpy(this->titulo, titulo);
	strcpy(this->cota, cota);
	strcpy(this->autor, autor);
	this->SetCantidadDisponible(cantidad_disponible);
}

char * Libro::GetCota()
{
	return this->cota;
}

char * Libro::GetTitulo()
{
	return this->titulo;
}

char * Libro::GetAutor()
{
	return this->autor;
}

int Libro::GetCantidadDisponible()
{
	return this->cantidad_disponible;
}

void Libro::SetCota(char * cota)
{
	strcpy(this->cota, cota);
}

void Libro::SetTitulo(char * titulo)
{
	strcpy(this->titulo, titulo);
}

void Libro::SetAutor(char * autor)
{
	strcpy(this->autor, autor);
}

void Libro::SetCantidadDisponible(int cantidad)
{
	this->cantidad_disponible = cantidad;
}

void Libro::IncrementarCantidadDisponible()
{
	int cantidad = this->GetCantidadDisponible();
	this->SetCantidadDisponible(cantidad + 1);
}

int Libro::DecrementarCantidadDisponible()
{
	int cantidad = this->GetCantidadDisponible();
	if (cantidad == CANTIDAD_LIBROS_MIN) {
		return LIBROS_ERR_MIN_CANT_ALCANZADA;
	}

	this->SetCantidadDisponible(cantidad - 1);
	return 0;
}

int Libro::AgregarDeConsola(TArchivo<Libro> * archivo) {
	char datos_correctos = 's';
	char condicion_salida = 's';
	Libro nuevo_libro = Libro();

	do {
		std::cin.ignore();
		std::cout << "Ingrese nombre del libro: ";
		std::cin.getline(nuevo_libro.titulo, CADENA_MAX);

		std::cout << "Ingrese la cota del libro: ";
		std::cin.getline(nuevo_libro.cota, CADENA_MAX);
		
		std::cout << "Ingrese el autor del libro: ";
		std::cin.getline(nuevo_libro.autor, CADENA_MAX);

		system("cls");

		std::cout << "Nombre del libro: " << nuevo_libro.titulo << std::endl;
		std::cout << "Cota del libro: " << nuevo_libro.cota << std::endl;
		std::cout << "Autor del libro: " << nuevo_libro.autor << std::endl;
		std::cout << "Son estos datos correctos? (s/n): ";
		datos_correctos = (char) std::cin.get();

		if (datos_correctos == 's') {
			archivo->Insertar(nuevo_libro);
			std::cout << "Insertado!" << std::endl;
		} else {
			system("cls");
			continue;
		}

		std::cin.ignore();
		std::cout << "Agregar otro libro? (s/n): ";
		condicion_salida = (char) std::cin.get();

		system("cls");
	} while (condicion_salida == 's');

	return 0;
}

int Libro::EliminarDeConsola(TArchivo<Libro> * archivo) {
	char salir_confirmacion = 'n';
	
	Libro registro_eliminar = Libro::GetDefault();

	do {
		std::cin.ignore();

		std::cout << "Ingrese cota del libro: ";
		std::cin.getline(registro_eliminar.cota, CADENA_MAX);

		switch (archivo->Buscar(registro_eliminar)) {
			case ARCHIVO_ERR_NO_ENCONTRADO:
				std::cout << "Libro no encontrado." << std::endl;
				break;
			default:
				std::cout << "Titulo del libro: " << archivo->GetBuf()->GetTitulo() << std::endl;
				std::cout << "Autor del libro: " << archivo->GetBuf()->GetAutor() << std::endl;

				std::cout << "Proceder a eliminar? (s/n): ";

				if ((char) std::cin.get() == 's') {
					archivo->Eliminar(registro_eliminar);
					std::cout << "Eliminado!" << std::endl;
				}
				std::cin.ignore();
				break;
		}

		std::cout << "Eliminar otro libro? (s/n): ";
		salir_confirmacion = (char) std::cin.get();

		system("cls");
	} while (salir_confirmacion != 'n');

	return 0;
}

int Libro::ConsultarConsola(TArchivo<Libro> * archivo)
{
	char condicion_salida = 'n';
	Libro buscar_libro = Libro();

	do {
		std::cin.ignore();
		std::cout << "Ingrese la cota del libro: ";
		std::cin.getline(buscar_libro.cota, CADENA_MAX);
		switch (archivo->Buscar(buscar_libro)) {
			case ARCHIVO_ERR_NO_ENCONTRADO:
				std::cout << "Libro no encontrado." << std::endl;
				break;
			default:
				std::cout << "Nombre del libro: " << archivo->GetBuf()->GetTitulo() << std::endl;
				std::cout << "Autor del libro: " << archivo->GetBuf()->GetAutor() << std::endl;
				break;
		}

		std::cout << "Buscar otro libro? (s/n): ";
		condicion_salida = (char) std::cin.get();
		system("cls");
	} while (condicion_salida != 'n');

	std::cin.ignore();
	return 0;
}

void Libro::HacerEncabezado() {
	std::cout << "LISTADO DE LIBROS" << std::endl;
	Utils::imprimir_separador('=');
}

void Libro::Mostrar(long indice) {
	std::cout << "Libro #" << indice << std::endl;
	std::cout << "Titulo: " << this->titulo << std::endl;
	std::cout << "Cota: " << this->cota << std::endl;
	std::cout << "Autor: " << this->autor << std::endl;
	std::cout << std::endl;
}

int Libro::ModificarDeConsola(TArchivo<Libro> * archivo) {
	char reintentar = 'n';

	do {
		std::cin.ignore();
		Libro actualizar_libro = Libro();

		std::cout << "Ingrese cota del libro para buscar: ";
		std::cin.getline(actualizar_libro.cota, CADENA_MAX);

		std::cout << "Ingrese nuevo titulo del libro: ";
		std::cin.getline(actualizar_libro.titulo, CADENA_MAX);

		std::cout << "Ingrese nuevo autor del libro: ";
		std::cin.getline(actualizar_libro.autor, CADENA_MAX);

		switch (archivo->Actualizar(actualizar_libro)) {
			case ARCHIVO_ERR_NO_ENCONTRADO:
				std::cout << "Libro no encontrado" << std::endl;
				break;
			default:
				std::cout << "Actualizado!" << std::endl;
				break;
		};

		std::cout << "Actualizar otro libro? (s/n): ";
		reintentar = (char) std::cin.get();
		system("cls");
	} while (reintentar != 'n');
	return 0;
}

Libro Libro::GetDefault() {
	const Libro stub = Libro("", "", "", 0);
	return stub;
}

// TODO: Esto solo compara this.cota
// Retrabajar para comparar toda la entidad.
bool Libro::IsDefault() {
	return *this == Libro::GetDefault();
}

bool Libro::operator== (const Libro &p) const {
	return strcmp(this->cota, p.cota) == 0;
}

