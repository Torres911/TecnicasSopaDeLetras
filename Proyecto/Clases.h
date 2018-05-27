#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<stdlib.h>
#include<cstdio.h>

const int tamanoTablero = 10;

using namespace std;

enum Direccion{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};
struct PuntoInicial{
	int i;
	int k;
};
class Generator{
	char tablero[tamanoTablero][tamanoTablero]; //Create a nxn grid
	char NULL_CHAR; //The character that represents a null value
	string palabras[7];
	public:
	Generator();
	char generateRandomChar(); //returns a random character
	bool canInsert(const char* word, puntoInicial start, direccion d); //Checks if the given word can be inserted at the start position facing direction d
	void insertWord(const char* word); //Place word at a random, valid location facing a random direction
	void clearGrid(); //Sets the grid to be all null values
	void fillGrid(); //Fills null values with random characters
	void printGrid(); //Prints the grid to stdout
	PuntoInicial shiftPoint(puntoInicial start, direccion d); //Returns the shifted point
	void readFile(char* filename);
	void insertWordsFromFile();
	void puzzleToFile(char* filename);
};