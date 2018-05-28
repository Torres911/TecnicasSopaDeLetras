#include"Clases.h"

GeneradorSopa::GeneradorSopa(){
	valorDefecto = 'x'; //Sets the null char to a lowercase x
}

char GeneradorSopa::generarCharRandom(){
	return 'A' + rand()%26;
}

void GeneradorSopa::limpiarTablero(){
	FILE* output;
	output = fopen("O.txt", "w");
	for(int i=0;i<boardSize;i++){
		for(int k=0;k<boardSize;k++){
			tablero[i][k] = valorDefecto;
		}
	}
}

//Condición
bool GeneradorSopa::puedeEntrar(const char* palabra, PuntoInicial inicio, Direccion d){
	int i = 0;
	PuntoInicial nuevoPunto = inicio;
	while(i < (int)strlen(palabra))
	{
		try{
			if(tablero[nuevoPunto.i][nuevoPunto.k] == valorDefecto){
				nuevoPunto = puntoPivote(nuevoPunto,d);
				i++;
			}
			else{
				return false;
			}
		}
		catch(const char* msg) //Returns false if the out of bounds error occurs
		{
			/*cout << "Cannot insert one of the words.  Please try again or choose a new word." << endl;
			exit(1);*/
			return false;
		}
	}
	return true;
}

//Replaces empty tiles with a random character
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
		inicio.i = rand() % boardSize; //set to a random Fila
		inicio.k = rand() % boardSize; //set to a random Columna
		d = Direccion(rand() % 250); //get a random direction
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

void GeneradorSopa::leerArchivo(){
	FILE* palabrasArchivo;
	palabrasArchivo = fopen("Flores.txt", "r");
	char palabra[100];
	int line = 0;
	if(palabrasArchivo != NULL){
		while(line < 250){
			fgets(palabra, 100, palabrasArchivo);
			palabras[line] = palabra;
			line++;
			if(line == 250){
				throw "No se permiten mas de 250 palabras de entrada para la Sopa de Letras";
			}
			if(sizeof(palabra) < 2 || sizeof(palabra) > boardSize-1){
				throw "No pueden haber palabras de menos de 2 caracteres, ni mayor a 250 caracteres (Maximo del Tablero)";
			}
		}
	}
	else{
		throw "No se pudo abrir el archivo";
	}
}

void GeneradorSopa::insertarPalabraDeArchivo(){
	//Iterate through all of the indexes in the array and insert them into the grid
	for(int i = 0; i < (int)(sizeof(palabras) / sizeof(palabras[0])); i++){
		string palabra = palabras[i];
		insertarPalabra(palabra.c_str()); //Convert the word (std::string) into a useable char* array
	}
}

void GeneradorSopa::respuestaArchivo(){
	char c;
	FILE* output;
	output = fopen("O.txt", "w");
	if(output != NULL){
		for(int i = 0; i < boardSize; i++){
			for(int k = 0;k < boardSize; k++){
				if(k == boardSize-1){
					c = tablero[i][k];
					fputc(c, output);
					fputc('\n', output);	//Append a newline if it is on the last Columna
				}
				else{
					c = tablero[i][k];
					fputc(c, output);
				}
			}
		}
	}
	else{
		throw "No se pudo crear el archivo con la Sopa de Letras";
	}
}