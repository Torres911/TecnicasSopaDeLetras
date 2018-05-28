#include"Clases.h"


int main(){
	/* initialize random seed: */
	srand (time(NULL));
	GeneradorSopa gen;
	try{
		gen.leerArchivo();
	}
	catch(int a){
		a = 0;
		cout << "No se pudo leer el archivo." << endl;
		exit(1);
	}
	gen.limpiarTablero();
	gen.insertarPalabraDeArchivo();
	gen.llenarTablero();
	gen.imprimirTablero();
	try{
		gen.respuestaArchivo();
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	return 0;
}