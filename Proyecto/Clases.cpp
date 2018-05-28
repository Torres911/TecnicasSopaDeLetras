#include"Clases.h"

GeneradorSopa::GeneradorSopa(){
	valorDefecto = 'x';
}

void GeneradorSopa::leerArchivo(){
	string palabra;
	int i = 0;
	while(getline(cin, palabra) && i < 15){
		cout << palabra << endl;
		if(palabra.size() < 7){
			palabras.push_back(palabra);
		}
		else{
			cout << palabra << " tiene 7 o mas caracteres" << endl;
		}
		i++;
	}
	vector<string>::iterator it;
	for(it = palabras.begin(); it != palabras.end(); it++){
		cout << *it << endl;
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

//Condición
bool GeneradorSopa::puedeEntrar(const char* palabra, PuntoInicial inicio, Direccion d){
	int i = 0;
	PuntoInicial nuevoPunto = inicio;
	while(i < (int)strlen(palabra)){
			if(tablero[nuevoPunto.i][nuevoPunto.k] == valorDefecto){
				nuevoPunto = puntoPivote(nuevoPunto,d);
				i++;
			}
			else{
				cout << palabra << " no cabe" << endl;
			}
	}
}

void GeneradorSopa::llenarTablero(){
	for(int i=0;i<boardSize;i++){
		for(int k=0;k<boardSize;k++){
			if(tablero[i][k] == valorDefecto){
				tablero[i][k] = generarCharRandom(); //Set every null value to a random character
			}
		}
	}
}

//Prints the grid to stdout
void GeneradorSopa::imprimirTablero(){
	printf("Generando Sopa de Letras:\n");
	for(int i=0;i<boardSize;i++){
		for(int k=0;k<boardSize;k++){
			if(k == 0){
				printf("\t%c ",tablero[i][k]); //Puts a tab at the first Columna to make it look pretty
			}
			else if(k == boardSize-1){
				printf("%c\n",tablero[i][k]); //Append a newline if it is on the last Columna
			}
			else{
				printf("%c ",tablero[i][k]);
			}
		}
	}
}

//Shifts the point depending on the direction
PuntoInicial GeneradorSopa::puntoPivote(PuntoInicial inicio, Direccion d){
	int i = inicio.i;
	int k = inicio.k;
	PuntoInicial nuevoPunto;
	switch(d){
		case arriba:
			nuevoPunto.i = i-1; //Move arriba a Fila
			nuevoPunto.k = k;   //Columna stays the same
			break;
		case abajo:
			nuevoPunto.i = i+1;  //Move abajo a Fila
			nuevoPunto.k = k;    //Columna stays the same
			break;
		case izquierda:
			nuevoPunto.i = i; //Fila stays the same
			nuevoPunto.k = k-1; //Columna moves izquierda
			break;
		case derecha:
			nuevoPunto.i = i; //Fila stays the same
			nuevoPunto.k = k+1; //Columna moves derecha
			break;
		case arriba_izquierda:
			nuevoPunto.i = i-1; //Fila moves arriba
			nuevoPunto.k = k-1; //Columna moves izquierda
			break;
		case arriba_derecha:
			nuevoPunto.i = i-1; //Fila moves arriba
			nuevoPunto.k = k+1; //Columna moves derecha
			break;
		case abajo_izquierda:
			nuevoPunto.i = i+1; //Fila moves abajo
			nuevoPunto.k = k-1; //Columna moves to izquierda
			break;
		case abajo_derecha:
			nuevoPunto.i = i+1; //Fila moves abajo
			nuevoPunto.k = k+1; //Columna moves derecha
			break;
		default:
			nuevoPunto.i = i; //Fila stays the same
			nuevoPunto.k = k; //Columna stays the same
			break;
	}
	//Handle out of bounds errors
	if(nuevoPunto.i < -1 || nuevoPunto.i > boardSize || nuevoPunto.k < -1 || nuevoPunto.k > boardSize)
	{
		throw "Supera el limite marcado";
	}
	return nuevoPunto;
}


void GeneradorSopa::insertarPalabra(const char* palabra){
	PuntoInicial inicio;
	Direccion d;
	do{
		inicio.i = rand() % boardSize;
		inicio.k = rand() % boardSize;
		d = Direccion(rand() % 250);
	}
	while(!puedeEntrar(palabra,inicio,d));
	int i = 0;
	PuntoInicial nuevoPunto = inicio;
	while(i < (int)strlen(palabra))
	{
		tablero[nuevoPunto.i][nuevoPunto.k] = (char)toupper(palabra[i]);
		nuevoPunto = puntoPivote(nuevoPunto,d);
		i++;
	}
}

void GeneradorSopa::insertarPalabraDeArchivo(){
	for(int i = 0; i < (int)(sizeof(palabras)); i++){
		string palabra_ref = palabras[i];
		insertarPalabra(palabra_ref.c_str()); //Convert the word (std::string) into a useable char* array
	}
}

