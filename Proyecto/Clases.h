#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<stdlib.h>
#include<cstdio.h>

const int tamanoTablero = 10;

using namespace std;

enum Direccion{
	arriba,
	abajo,
	izquierda,
	derecha,
	arriba_izquierda,
	arriba_derecha,
	abajo_izquierda,
	abajo_derecha
};

struct PuntoInicial{
	int i;
	int k;
};

class GeneradorSopa{
	
	char tablero[tamanoTablero][tamanoTablero]; //Create a nxn grid
	char valorDefecto; //The character that represents a null value
	string palabras[7];
	
	public:
		GeneradorSopa();
		char generarCharRandom(); //returns a random character
		bool puedeEntrar(const char* palabra, puntoInicial inicio, Direccion d); //Checks if the given word can be inserted at the start position facing direction d
		void insertarPalabra(const char* palabra); //Place word at a random, valid location facing a random direction
		void limpiarTablero(); //Sets the grid to be all null values
		void llenarTablero(); //Fills null values with random characters
		void imprimirTablero(); //Prints the grid to stdout
		PuntoInicial puntoPivote(puntoInicial inicio, Direccion d); //Returns the shifted point
		void leerArchivo(char* filename);
		void insertarPalabraDeArchivo();
		void respuestaArchivo(char* filename);
};