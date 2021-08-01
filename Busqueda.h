#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#define BUSQ_BIN_NO_ENCONTRADO -1
#define BUSQ_SEQ_ARCHIVO_REG_NO_ENCONTRADO -1

#include "Archivo.h"
#include <cmath>

class Busqueda
{
	public:
		template <typename T>
		static int busqueda_binaria(T arr[], const unsigned int arr_length, T &elem) {
			int izq = 0;
		    int der = arr_length;
		    int centro = (izq + der) / 2;

		    while (izq <= der && elem != arr[centro]) {
		        if (elem > arr[centro]) {
		            izq = centro + 1;
		        } else {
		            der = centro - 1;
		        }

		        centro = (izq + der) / 2;
		    }

		    if (izq > der) {
		        return BUSQ_BIN_NO_ENCONTRADO;
		    } else {
		        return centro;
		    }
		}
		
		template <typename T>
		static int busq_seq_desord_archivos(TArchivo<T> &archivo, T &clave) {
			/*
			bool band = false;
			unsigned int i = 0;
			int cantidad = archivo.Contar();
			if (cantidad == ARCHIVO_ERR_ABRIR) {
				return cantidad;
			}
			int tam_bloq = sqrt(cantidad);
			
			while ((tam_bloq * (i + 1) <= cantidad - 1) && !band) {
				archivo.Acceder(tam_bloq * (i + 1));
				if (archivo.GetBuf() >= clave) {
					band = true;
				} else {
					i += 1;
				}
			}
			
			if (band) {
				if (archivo.GetBuf() == clave) {
					return i;
				}
			}
			*/

			bool band = false;
			int i = 0;
			int archivo_res = archivo.Acceder(i);
			while (archivo_res != ARCHIVO_ERR_EOF && !band) {
				if (*archivo.GetBuf() == clave) {
					band = true;
				} else {
					i += 1;
					archivo_res = archivo.Acceder(i);
				}
			}
			if (band) {
				return i;
			} else {
				return BUSQ_SEQ_ARCHIVO_REG_NO_ENCONTRADO;
			}
		}
};

#endif
