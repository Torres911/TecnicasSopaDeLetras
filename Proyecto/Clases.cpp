#include"Clases.h"

GeneradorSopa::GeneradorSopa(){
	valorDefecto = 'x';
}

void GeneradorSopa::leerArchivo(){
	string palabra;
	int i = 0;
	while(getline(cin, palabra) && i < 15){
		if(palabra.size() < 9){
			palabras.push_back(palabra);
		}
		else{
			cout << palabra << " tiene 9 o mas caracteres" << endl;
		}
		i++;
	}
}

char GeneradorSopa::generarCharRandom(){
	return 'A' + rand()%26;
}

void GeneradorSopa::limpiarTablero(){
	for(int i = 0; i < boardSize; i++){
		for(int k = 0; k < boardSize; k++){
			tablero[i][k] = valorDefecto;
		}
	}
}

bool GeneradorSopa::puedeEntrar(string palabra, PuntoInicial inicio, Direccion d){
	int i = 0;
	PuntoInicial nuevoPunto = inicio;
	while(i < sizeof(palabra)){
			if(tablero[nuevoPunto.i][nuevoPunto.k] == valorDefecto){
				nuevoPunto = puntoPivote(nuevoPunto,d);
			}
			else{
				cout << palabra << " no cabe" << endl;
			}
			i++;
	}
}

void GeneradorSopa::llenarTablero(){
	for(int i=0;i<boardSize;i++){
		for(int k=0;k<boardSize;k++){
			if(tablero[i][k] == valorDefecto){
				tablero[i][k] = generarCharRandom();
			}
		}
	}
}

void GeneradorSopa::imprimirTablero(){
	for(int i=0;i<boardSize;i++){
		for(int k=0;k<boardSize;k++){
			if(k == 0){
				printf("\t%c ",tablero[i][k]);
			}
			else if(k == boardSize-1){
				printf("%c\n",tablero[i][k]);
			}
			else{
				printf("%c ",tablero[i][k]);
			}
		}
	}
}


PuntoInicial GeneradorSopa::puntoPivote(PuntoInicial inicio, Direccion d){
	int i = inicio.i;
	int k = inicio.k;
	PuntoInicial nuevoPunto;
	switch(d){
		case arriba:
			nuevoPunto.i = i-1;
			nuevoPunto.k = k;
			break;
		case abajo:
			nuevoPunto.i = i+1;
			nuevoPunto.k = k;
			break;
		case izquierda:
			nuevoPunto.i = i;
			nuevoPunto.k = k-1;
			break;
		case derecha:
			nuevoPunto.i = i;
			nuevoPunto.k = k+1;
			break;
		case arriba_izquierda:
			nuevoPunto.i = i-1;
			nuevoPunto.k = k-1;
			break;
		case arriba_derecha:
			nuevoPunto.i = i-1;
			nuevoPunto.k = k+1;
			break;
		case abajo_izquierda:
			nuevoPunto.i = i+1;
			nuevoPunto.k = k-1;
			break;
		case abajo_derecha:
			nuevoPunto.i = i+1;
			nuevoPunto.k = k+1;
			break;
		default:
			nuevoPunto.i = i;
			nuevoPunto.k = k;
			break;
	}

	if(nuevoPunto.i < -1 || nuevoPunto.i > boardSize || nuevoPunto.k < -1 || nuevoPunto.k > boardSize)
	{
		throw "Supera el limite marcado";
	}
	return nuevoPunto;
}


void GeneradorSopa::insertarPalabra(char* palabra){
	PuntoInicial inicio;
	Direccion d;
	do{
		inicio.i = rand() % boardSize;
		inicio.k = rand() % boardSize;
		d = Direccion(rand() % 8);
	}

	while(!puedeEntrar(palabra,inicio,d));
	int i = 0;
	PuntoInicial nuevoPunto = inicio;
	while(i < sizeof(palabra))
	{
		tablero[nuevoPunto.i][nuevoPunto.k] = (char)toupper(palabra[i]);
		nuevoPunto = puntoPivote(nuevoPunto,d);
		i++;
	}
}

void GeneradorSopa::insertarPalabraDeArchivo(){
	vector<string>::iterator it;
	string palabra_ref;
	imprimirTablero();
	for(it = palabras.begin(); it != palabras.end(); it++){
		palabra_ref = *it;
		char* char_ref;
		cout << palabra_ref << endl;
		for(int i = 0; i < palabra_ref.size(); i++){
			char_ref[i] = palabra_ref[i];
		}
		cout << char_ref << endl;
		insertarPalabra(char_ref);

	}
}