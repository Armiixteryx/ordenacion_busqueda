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
                    int aux = arr[i];
                    arr[i] = arr[i + ent];
                    arr[i + ent] = aux;
                    band = true;
                }
                i += 1;
            }
        }
		}
	}
	protected:
};

#endif
