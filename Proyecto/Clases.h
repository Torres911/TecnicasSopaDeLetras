#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
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
		char tablero[boardSize][boardSize]; //Create a nxn grid
		char valorDefecto; //The character that represents a null value
		vector<string> palabras;

	public:
		GeneradorSopa();
		char generarCharRandom(); //returns a random character
		bool puedeEntrar(string palabra, PuntoInicial inicio, Direccion d); //Checks if the given word can be inserted at the start position facing direction d
		void insertarPalabra(string palabra); //Place word at a random, valid location facing a random direction
		void limpiarTablero(); //Sets the grid to be all null values
		void llenarTablero(); //Fills null values with random characters
		void imprimirTablero(); //Prints the grid to stdout
		PuntoInicial puntoPivote(PuntoInicial inicio, Direccion d); //Returns the shifted point
		void insertarPalabraDeArchivo();
		void leerArchivo();
};

#endif