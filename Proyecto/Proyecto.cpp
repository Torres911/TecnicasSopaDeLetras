#include"Clases.h"


int main(){
	srand (time(NULL));
	GeneradorSopa gen;
	gen.leerArchivo();
	gen.limpiarTablero();
	gen.imprimirTablero();
	gen.insertarPalabraDeArchivo();
	gen.imprimirTablero();
	gen.llenarTablero();
	gen.imprimirTablero();
	return 0;
}