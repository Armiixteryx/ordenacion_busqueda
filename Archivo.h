#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <fstream>
#include <string.h>

#define CONSOLA_PAGINACION 6
#define ARCHIVO_ERR_ABRIR -10
#define ARCHIVO_ERR_NO_ENCONTRADO -1
#define ARCHIVO_ERR_EOF -11
#define ARCHIVO_ERR_NOT_FOUND -12

using namespace std;

// Plantilla de mantenimiento de archivos binarios derivada de fstream
// Proposito: Reusar el codigo fuente con distintos archivos en procesos de rutina o manrenimiento
template <class T>
class TArchivo:public fstream
{
    private:
        T buf;         // Registro o bloque de datos que almacena el archivo
        char nom[40];  // Nombre del archivo registrado en el almacenamiento secundario
    public:
        TArchivo(const char *no="SinNombre.dat"){ strcpy(nom,no);              }
        //TArchivo() {}
        char *Get_nomb()                  { return nom;                  }
        void  Reset()     { open(nom, ios::out | ios::binary ); close(); }
        int   Insertar( T nue );
        int   Listar();
        int   Actualizar( T mod );
        int   Buscar( T &bus );
        int   Acceder(int idx);
        int   Eliminar(T &registro);
        T *   GetBuf() { return &this->buf; }
        int   Resetear();
};

// Anade un registro al final del archivo
template <class T>
int TArchivo<T>::Insertar(T nue)
{
    open(nom, ios::out | ios::app | ios::binary );
    if ( fail() || bad() )
        return 0;
    write((char *)&nue, sizeof(nue));
    close();
    return 1;
}

// Busca un registro identificado por un campo clave en el archivo
template <class T>
int TArchivo<T>::Buscar(T &bus)
{
    int enc, i;
    open(nom, ios::binary | ios::in);
    if ( fail() || bad() )
        return ARCHIVO_ERR_ABRIR; // Senal de error abriendo el archivo
    enc=i=ARCHIVO_ERR_NO_ENCONTRADO;
    while(enc==ARCHIVO_ERR_NO_ENCONTRADO)
    {
        i++;
        read((char *)&buf, sizeof(buf));
        if (eof()) break;
        //T registro_eliminado = T::GetDefault();
        if (!buf.IsDefault()) {
        	if (buf==bus) {
            	enc= i;
            	bus= buf; // copia todos los campos del registro localizado en el archivo en el parametro
        	}             // pasado por referencia
    	}
    }
    close();
    return enc; // Devuelve -1 si no lo encontro o el numero de registro o posicion relativa del reg
}

template <class T>
int TArchivo<T>::Acceder(int idx)
{
	open(nom, ios::binary | ios::in);
	if ( fail() || bad() )
		return ARCHIVO_ERR_ABRIR;

	seekg(idx * sizeof(buf), ios::beg);
	read((char *)&buf, sizeof(buf));
	if (eof()) return ARCHIVO_ERR_EOF;

	if (buf.IsDefault()) return ARCHIVO_ERR_NO_ENCONTRADO;
	
	close();

	return 0;
}

// Realiza un listado en pantalla con los datos almacenados en los registros
template <class T>
int TArchivo<T>::Listar()
{
    open(nom, ios::binary | ios::in);
    if ( fail() || bad() )
        return ARCHIVO_ERR_ABRIR;
    buf.HacerEncabezado();

    long registro_contador = 0;

    while(true)
    {
        read((char *)&buf, sizeof(buf));
        if (eof()) break;
        if (buf.IsDefault()) continue; // Se consideran como eliminados
        registro_contador += 1;
        buf.Mostrar(registro_contador);

        if (registro_contador % CONSOLA_PAGINACION == 0) {
        	system("pause");
        	system("cls");
        	buf.HacerEncabezado();
		}
    }
    close();
    return 0;
}

// Modifica un registro del archivo posicionando y sobreescribiendo.
template <class T>
int TArchivo<T>::Actualizar(T mod)
{
    T aux=mod;
    int enc=Buscar(aux);
    if ( enc>=0 )
    {
        open(nom, ios::binary | ios::in | ios::out);
        if ( fail() || bad() )
            return ARCHIVO_ERR_ABRIR;
        seekg(enc*sizeof(mod), ios::beg);
        write((char *)&mod, sizeof(mod));
        close();
    }
    return enc;
}

template <class T>
int TArchivo<T>::Eliminar(T &registro) {
	T aux = registro;
	int enc = Buscar(aux);
	if (enc >= 0 ) {
		open(nom, ios::binary | ios::in | ios::out);
		if ( fail() || bad() )
			return ARCHIVO_ERR_ABRIR;

		seekg(enc * sizeof(registro), ios::beg);
		T stub = T::GetDefault();
		write((char *) &stub, sizeof(stub));
		close();
	}
	return enc;
}

template <class T>
int TArchivo<T>::Resetear() {
	open(nom, ios::binary | ios::out | ios::trunc);
	if ( fail() || bad() )
		return ARCHIVO_ERR_ABRIR;
	close();
	return 0;
}

#endif ARCHIVO_H
