#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

class Ordenamiento
{
	public:
		template <typename T>
		static void shell_sort(T arr[], const unsigned arr_length) {
			int ent = arr_length + 1;

		    while (ent > 1) {
		        ent = ent / 2;
		        bool band = true;

		        while (band) {
		            band = false;
		            int i = 0;

		            while ((i + ent) < arr_length) {
		                if (arr[i] > arr[i + ent]) {
		                    T aux = arr[i];
		                    arr[i] = arr[i + ent];
		                    arr[i + ent] = aux;
		                    band = true;
		                }
		                i += 1;
		            }
		        }
			}
		}
		
		template <typename T>
		static void quick_sort_recursivo(T arr[], const unsigned int arr_length) {
			Ordenamiento::quicksort_recursivo_reduce<T>(arr, 0, arr_length - 1);
		}

	private:
		template <typename T>
		static void quicksort_recursivo_reduce(T arr[], unsigned int inicio, unsigned int fin) {
			unsigned int izquierdo = inicio;
		    unsigned int derecho = fin;
		    unsigned int pos = inicio;
		    bool band = true;

		    while (band) {
		        band = false;

		        while (arr[pos] <= arr[derecho] && pos != derecho) {
		            derecho -= 1;
		        }

		        if (pos != derecho) {
		            T aux = arr[pos];
		            arr[pos] = arr[derecho];
		            arr[derecho] = aux;
		            pos = derecho;
		
		            while (arr[pos] >= arr[izquierdo] && pos != izquierdo) {
		                izquierdo += 1;
		            }

		            if (pos != izquierdo) {
		                band = true;
		                T aux = arr[pos];
		                arr[pos] = arr[izquierdo];
		                arr[izquierdo] = aux;
		                pos = izquierdo;
		            }
		        }
		    }

		    if ((pos - 1) > inicio) {
		        quicksort_recursivo_reduce<T>(arr, inicio, pos - 1);
		    }

		    if (fin > (pos + 1)) {
		        Ordenamiento::quicksort_recursivo_reduce<T>(arr, pos + 1, fin);
		    }
		}
};

#endif
