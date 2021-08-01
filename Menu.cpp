#include "Menu.h"
#include <iostream>
#include "Utils.h"
#include <vector>
#include "Archivo.h"
#include "Libro.h"
#include "Ordenamiento.h"
#include "Busqueda.h"
#include <ctime>
#include <string>
#include <cstdlib>

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
		cout << "7. Generar libros aleatorios." << endl;
		cout << "8. Listar libros en RAM." << endl;
		cout << "9. Salir." << endl;
		cout << "Su opcion (1-9): ";

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
	
	libros_vec.clear();

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
			t = clock();
			Ordenamiento::shell_sort(&libros_vec[0], libros_vec.size());
			break;
		case MENU_ORD_ARCHIVO_QUICKSORT:
			t = clock();
			Ordenamiento::quick_sort_recursivo(&libros_vec[0], libros_vec.size());
			break;
	}

	t = clock() - t;

	cout << "Los libros en RAM han sido ordenados!" << endl;
	cout << "Duracion (segs): " << ((float) t) / CLOCKS_PER_SEC << endl;
	cout << "Duracion (cpu clocks): " << t << endl;
	cout << "Importante: Puede ver los libros ordenados en el menu: 8. Listar libros en RAM." << endl;
	system("pause");
	return 0;
}

int Menu::busq_bin_ram(vector<Libro> &libros_vec) {
	system("cls");
	cout << "BUSQUEDA BINARIA - RAM" << endl;
	Utils::imprimir_separador('=');
	
	char cota[CADENA_MAX] = "";

	cout << "Ingrese la cota a buscar: ";
	cin.getline(cota, CADENA_MAX);

	Libro libro_busq;
	libro_busq.SetCota(cota);

	int busq_result = Busqueda::busqueda_binaria<Libro>(&libros_vec[0], libros_vec.size(), libro_busq);
	
	if (busq_result == BUSQ_BIN_NO_ENCONTRADO) {
		cout << "Cota no encontrada" << endl;
	} else {
		cout << "Cota encontrada en posicion: " << busq_result << endl;
	}

	system("pause");

	return 0;
}

int Menu::busq_seq_archivos() {
	// No implementado...
	return 0;
}

///////////////////////////////// === /////////////////////////////////////////

// Generar libros aleatorios.
//
// Lista de nombres obtenida de: https://github.com/RandomAPI/Randomuser.me-Node/blob/64fd050d99e1242a9bf219810bc54ecbdc1d76fb/api/.nextRelease/data/IE/lists
// (Licencia MIT).
//
// Procesamiento previo: https://play.rust-lang.org/?version=stable&mode=debug&edition=2018&gist=452044e18117058ee5e31b4fe6ca0c5d
int Menu::generar_libros_random(vector<Libro> &libros_vec) {
	system("cls");
	cout << "GENERAR LIBROS" << endl;
	Utils::imprimir_separador('=');

	libros_vec.clear();

	const char NOMBRES[][CADENA_MAX] = {"Sophie Reyes", "Susie Fowler", "Maurice Wright", "Herbert Coleman", "Miguel Howell", "Caitlin Wallace", "Neil Ellis", "Tracey Green", "Maxwell King", "Lee Nelson", "Cody May", "Shaun Boyd", "Eddie Spencer", "Rosalyn Anderson", "Earl Franklin", "Kathleen Cunningham", "Franklin Ryan", "Theodore Terry", "Chad Bishop", "Marvin Lewis", "Jeremiah Chapman", "Flenn Cox", "Allie Rice", "Christina Williams", "Lance Turner", "Samantha Woods", "Albert Parker", "George Chambers", "Jerry Jensen", "Olivia Newman", "Victoria Price", "Sam Payne", "Bradley Kennedy", "Rafael Crawford", "Seth Reid", "Charles Robinson", "Dale Snyder", "Marie Wilson", "Walter Burton", "Hanna Farragher", "Ross Meyer", "Sammy Carpenter", "Edgar Doyle", "Jessica Harvey", "Fernando Flores", "Josh Davis", "Ricky Matthews", "Thomas Knight", "Lisa Gardner", "Susanna Brooks", "Leo Brewer", "Clifford Hamilton", "Eugene Graham", "Karen Bradley", "Danny Robertson", "Vicky Murphy", "Gavin Bailey", "Ashley Henderson", "Katherine Simmons", "Liam Edwards", "Cory Riley", "Duane Davies", "Stephanie Mason", "Raymond Young", "Tom Shaw", "Alice Watson", "Aaron Perry", "Scarlett Stone", "Travis Carroll", "Donna Mccoy", "Rachel Stewart", "Ellen Lowe", "Jim Mitchell", "Claude Gibson", "Lewis Stanley", "Connor Reynolds", "Vincent Richards", "Milton Butler", "Hugh Watkins", "Brendan Montgomery", "Allen Lee", "Don Nguyen", "Amelia Elliott", "Frank Morris", "Willie Scott", "Brian Lawrence", "Chloe Craig", "Harold Nichols", "Andy Hoffman", "Darryl Jenkins", "Kenneth Rose", "Justin Reed", "Mitchell Andrews", "Morris Bates", "Tony Hill", "Frederick Williamson", "Sergio Pearson", "Nicholas Campbell", "Rich Willis", "Sebastian Holt", "Emma Oliver", "Julio Fuller", "Roger Ross", "Amanda Daniels", "Elmer Odonoghue", "Avery Meehan", "Sharron Soto", "Gerry Frazier", "Alex Hart", "Wayne Banks", "Mia Harper", "Caleb Evans", "Patricia Allen", "Jamie Hunt", "Abbey Sutton", "Charlotte Kelly", "Francis Obrien", "David Fitzpatrick", "Zoe Bowman", "Tracy Carter", "Cameron Burns", "Lucas Hicks", "Hunter Cooper", "Logan Foster", "Douglas Weaver", "Cathy Gray", "Judy Austin", "Virgil Fields", "Mike Thompson", "Dylan Fleming", "Tammy Cole", "Corey Perkins", "Bernard Ford", "Javier Mckinney", "Julian Patterson", "Brent Ray", "Jimmy Fisher", "Lloyd Hawkins", "Gordon Marshall", "Carol Ward", "Joey Bell", "Ernest Richardson", "Troy Miller", "Jeremy Mills", "Kelly Curtis", "Rebecca West", "Pat Henry", "Freddie Barnes", "Steven Black", "Randall Osullivan", "Marcus Steward", "Kyle Roberts", "Robert Neal", "Luis Dean", "Caroline Baker", "Amy Martinez", "Clayton Brady", "Vanessa Taylor", "Jeff Duncan", "Henry Long", "Julie Beck", "Susanne Hall", "Noah Gordon", "Austin Gilbert", "Sofia Clarke", "Tomothy Shelton", "Chris Hayes", "Harvey Warren", "Leslie Berry", "Joe Byrd", "Kirk George", "Marshall Griffin", "Johnni Harrison", "Jessie James", "Timothy Fox", "Jesse Hughes", "Sarah Hale", "Katie Silva", "Alexandra Caldwell", "Tyler Jackson", "Becky Carr", "Lauren Rhodes", "Alvin Simpson", "Mathew Lopez", "Phoebe Owens", "Jordan Day", "Ella Jennings", "Dwayne Sanders", "Jose Mitchelle", "Ron Lawson", "John Holland", "Kevin Simmmons", "Gilbert Martin", "Suzy Thomas", "Harry Johnston", "Leonard Jordan", "Brett Ferguson", "Isaiah Wheeler", "Terry Wells", "Nicole Cruz", "Christian Fitzgerald", "Kaitlin Collins", "Ed Lane", "Clyde Cook", "Patrick Fitzsimmons", "Judith Murray", "Edward Jones", "Emily Mcguinness", "Ivan Omahony", "Kurt Kelley", "Jake Larson", "Rick Dunne", "Barb Carlson", "Theo Porter", "Dean Clark", "Lillian Watts", "Nolan Horton", "Leah Wade", "Jay Myers", "Glen Hopkins", "Daniel Lucas", "Donald Walker", "Scott Pierce", "Gerald Little", "Sam Russell", "Leroy Freeman", "Nathaniel Graves", "Dave Tucker", "Enrique Smith", "Ava Brown", "Arthur Mendoza", "Jennifer Sims", "Angie Douglas", "Steve Palmer", "Shane Holmes", "Arron Jacobs", "Tyrone Stevens", "Phil Armstrong", "Keith Lambert", "Dan White", "Herman Harris", "Nelson Stephens", "Mandy Powell", "Guy Arnold", "Mark Johnson", "Isaac Rogers", "Nick Peters", "Craig Webb", "Eduardo Peterson", "Ray Hudson", "Joseph Davidson", "Jimmie Smythe", "Everett Bennett", "Zachary Otoole", "Paige Morrison", "Adrian Bryant", "Lily Wood", "Timmothy Phillips", "Abigail Adams", "Megan Lynch", "Bob Howard", "Peter Welch", "Ted Hanson", "Stanley Fletcher", "Gabriel Gregory", "Felix Olson", "Jorge Mcdonalid", "Kathy Garrett", "Jack Walters", "Ellie Miles", "Laura Morgan", "Arnold Sullivan", "Melissa Burke", "Kate Hunter", "Eleanor Lord", "Maddison Grant", "Wyatt Hansen", "Jen Moore"};
	const unsigned int NOMBRES_LENGTH = sizeof(NOMBRES) / sizeof(NOMBRES[0]);

	const char COTAS[][CADENA_MAX] = {"T00004887", "T00049099", "T00001756", "T00043651", "T00006838", "T00044726", "T00050341", "T00047679", "T00055137", "T00060882", "T00043032", "T00057235", "T00011786", "T00000701", "T00031386", "T00021908", "T00019295", "T00053663", "T00042796", "T00021209", "T00041859", "T00016907", "T00007901", "T00027345", "T00046259", "T00049035", "T00003619", "T00013943", "T00027387", "T00006205", "T00046589", "T00056563", "T00025782", "T00058140", "T00047726", "T00002922", "T00054493", "T00044568", "T00043584", "T00019660", "T00014243", "T00007079", "T00000899", "T00057001", "T00041046", "T00036957", "T00044698", "T00042888", "T00053839", "T00052337", "T00035327", "T00051396", "T00031750", "T00014301", "T00033895", "T00027819", "T00012494", "T00021270", "T00005717", "T00055891"};
	const unsigned int COTAS_LENGTH = sizeof(COTAS) / sizeof(COTAS[0]);
	vector<int> cotas_usadas;

	const char LIBROS[][CADENA_MAX] = {"L00012724", "L00043071", "L00018244", "L00027176", "L00063590", "L00055537", "L00050526", "L00002025", "L00024800", "L00026080", "L00013501", "L00036356", "L00046898", "L00026975", "L00031774", "L00036623", "L00024134", "L00007967", "L00021018", "L00038858", "L00018274", "L00063601", "L00060918", "L00043733", "L00064096", "L00024322", "L00033639", "L00043838", "L00037548", "L00061149", "L00035993", "L00029192", "L00064125", "L00054922", "L00009695", "L00015450", "L00013903", "L00058371", "L00019052", "L00002187", "L00000766", "L00007084", "L00044329", "L00030745", "L00053689", "L00047228", "L00046561", "L00023135", "L00019315", "L00056540", "L00052994", "L00004739", "L00047843", "L00043025", "L00000747", "L00023086", "L00046442", "L00035222", "L00046786", "L00000449"};
	const unsigned int LIBROS_LENGTH = sizeof(LIBROS) / sizeof(LIBROS[0]);

	for (int i = 0; i < MAX_LIBROS_GENERAR; i++) {
		const char * autor = NOMBRES[rand() % NOMBRES_LENGTH];

		int cota_generada = rand() % COTAS_LENGTH;

		// No repetir cotas en libros nuevos.
		int j = 0;
		while (j < cotas_usadas.size()) {
			if (cota_generada == cotas_usadas[j]) {
				cota_generada = rand() % COTAS_LENGTH;		
				j = 0;
			} else {
				j += 1;
			}
		}

		cotas_usadas.push_back(cota_generada);
		
		const char * cota = COTAS[cota_generada];
		
		const char * titulo = LIBROS[rand() % LIBROS_LENGTH];
		int cantidad_disponible = (rand() % 10) + 1;
		Libro libro(titulo, cota, autor, cantidad_disponible);
		libros_vec.push_back(libro);
	}

	cout << MAX_LIBROS_GENERAR << " libros generados!" << endl;

	string nombre_archivo;
	cout << "Ingrese nombre del archivo donde guardar los libros (default: " << ARCHIVO_LIBRO_NOMBRE << "): ";
	getline(cin, nombre_archivo);
	if (nombre_archivo.empty()) {
		nombre_archivo = ARCHIVO_LIBRO_NOMBRE;
	}
	TArchivo<Libro> archivo(nombre_archivo.c_str());

	int archivo_res = archivo.Resetear();
	
	switch (archivo_res) {
		case ARCHIVO_ERR_ABRIR:
			cout << "Error al abrir archvo: " << nombre_archivo;
			cout << ": El archivo no se ha encontrado." << endl;
			break;
		default:
			for (int i = 0; i < libros_vec.size(); i++) {
				int archivo_insert_res = archivo.Insertar(libros_vec[i]);
				if (archivo_insert_res == ARCHIVO_ERR_GENERAL) {
					cout << "Error al escribir registro #" << i + 1;
					cout << " en el archivo." << endl;
					system("pause");
					break;
				}
			}
			cout << "Libros guardados en archivo." << endl;
			break;
	}

	system("pause");

	return 0;
}

int Menu::listar_libros_ram(vector<Libro> &libros_vec) {
	system("cls");
	cout << "LISTAR LIBROS EN RAM" << endl;
	Utils::imprimir_separador('=');
	if (libros_vec.empty()) {
		cout << "Por favor, cargue primero los libros en RAM" << endl;
		system("pause");
		return MENU_ORD_ARCHIVO_NO_CARGADO;
	}

	for (int i = 0; i < libros_vec.size(); i++) {
		libros_vec[i].Mostrar(i + 1);

		if (i != 0 && i % 5 == 0) {
			system("pause");
		}
	}

	cout << "Libros mostrados!";
	system("pause");

	return 0;
}

