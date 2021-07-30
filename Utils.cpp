#include "Utils.h"
#include <iostream>

using namespace std;

void Utils::imprimir_separador(char c) {
	for (int i = 0; i < WIN_CONSOLE_MAX_WIDTH; i++) {
		cout << c;
	}
	cout << endl;
}
