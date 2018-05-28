#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<cstdio>
#include<vector>

#ifndef CLASES_H
#define CLASES_H

const int boardSize = 10;

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
	private:
		char tablero[boardSize][boardSize];
		char valorDefecto;
		vector<string> palabras;

	public:
		GeneradorSopa();
		char generarCharRandom();
		bool puedeEntrar(string palabra, PuntoInicial inicio, Direccion d);
		void insertarPalabra(char* palabra);
		void limpiarTablero();
		void llenarTablero();
		void imprimirTablero();
		PuntoInicial puntoPivote(PuntoInicial inicio, Direccion d);
		void insertarPalabraDeArchivo();
		void leerArchivo();
};

#endif