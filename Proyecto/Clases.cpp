#include"Clases.h"
GeneradorSopa::GeneradorSopa(){
	valorDefecto = 'x'; //Sets the null char to a lowercase x
}

char GeneradorSopa::generarCharRandom(){
	return 'A' + rand()%26; //leet way to generate a random character
}

//Sets all values in grid to a null character
void GeneradorSopa::limpiarTablero(){
	for(int i=0;i<tamanoTablero;i++){
		for(int k=0;k<tamanoTablero;k++){
			tablero[i][k] = valorDefecto; //Every empty value will be a lowercase x
		}
	}
}

//Checks if word can be inserted in the grid at the given inicio point
bool GeneradorSopa::puedeEntrar(const char* palabra, puntoInicial inicio, Direccion d){
	int i = 0;
	puntoInicial nuevoPunto = inicio;
	while(i < (int)strlen(palabra)) //Iterates through the word char array
	{
		//Attempt to shift the point
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
	for(int i=0;i<tamanoTablero;i++){
		for(int k=0;k<tamanoTablero;k++){
			if(tablero[i][k] == valorDefecto){
				tablero[i][k] = generarCharRandom(); //Set every null value to a random character
			}
		}
	}
}

//Prints the grid to stdout
void GeneradorSopa::imprimirTablero(){
	printf("Generated Puzzle:\n");
	for(int i=0;i<tamanoTablero;i++){
		for(int k=0;k<tamanoTablero;k++){
			if(k == 0){
				printf("\t%c ",tablero[i][k]); //Puts a tab at the first column to make it look pretty
			}
			else if(k == tamanoTablero-1){
				printf("%c\n",tablero[i][k]); //Append a newline if it is on the last column
			}
			else{
				printf("%c ",tablero[i][k]);
			}
		}
	}
}

//Shifts the point depending on the direction
puntoInicial GeneradorSopa::puntoPivote(puntoInicial inicio, Direccion d){
	int i = inicio.i;
	int k = inicio.k;
	puntoInicial nuevoPunto;
	switch(d){
		case arriba:
			nuevoPunto.i = i-1; //Move arriba a row
			nuevoPunto.k = k;   //Column stays the same
			break;
		case abajo:
			nuevoPunto.i = i+1;  //Move abajo a row
			nuevoPunto.k = k;    //Column stays the same
			break;
		case izquierda:
			nuevoPunto.i = i; //Row stays the same
			nuevoPunto.k = k-1; //Column moves izquierda
			break;
		case derecha:
			nuevoPunto.i = i; //Row stays the same
			nuevoPunto.k = k+1; //Column moves derecha
			break;
		case arriba_izquierda:
			nuevoPunto.i = i-1; //Row moves arriba
			nuevoPunto.k = k-1; //Column moves izquierda
			break;
		case arriba_derecha:
			nuevoPunto.i = i-1; //Row moves arriba
			nuevoPunto.k = k+1; //Column moves derecha
			break;
		case abajo_izquierda:
			nuevoPunto.i = i+1; //Row moves abajo
			nuevoPunto.k = k-1; //Column moves to izquierda
			break;
		case abajo_derecha:
			nuevoPunto.i = i+1; //Row moves abajo
			nuevoPunto.k = k+1; //Column moves derecha
			break;
		default:
			nuevoPunto.i = i; //Row stays the same
			nuevoPunto.k = k; //Column stays the same
			break;
	}
	//Handle out of bounds errors
	if(nuevoPunto.i < -1 || nuevoPunto.i > tamanoTablero || nuevoPunto.k < -1 || nuevoPunto.k > tamanoTablero)
	{
		throw "Out of Bounds";
	}
	return nuevoPunto;
}


void GeneradorSopa::insertarPalabra(const char* palabra){
	puntoInicial inicio;
	Direccion d;
	do{
		inicio.i = rand() % tamanoTablero; //set to a random row
		inicio.k = rand() % tamanoTablero; //set to a random column
		d = Direccion(rand() % 8); //get a random direction
	}
	while(!puedeEntrar(palabra,inicio,d));
	int i = 0;
	puntoInicial nuevoPunto = inicio;
	while(i < (int)strlen(palabra))
	{
		tablero[nuevoPunto.i][nuevoPunto.k] = (char)toarribaper(palabra[i]);
		nuevoPunto = puntoPivote(nuevoPunto,d);
		i++;
	}
}

void GeneradorSopa::leerArchivo(char* filename){
	ifstream palabrasArchivo(filename);
	string palabra;
	int line = 0;
	if(palabrasArchivo.is_open()){
		printf("Reading file '%s'\n",filename);
		while(getline(palabrasArchivo,palabra)){
			palabras[line] = palabra;
			line++;
			if(line == 8){
				throw "Words list can not have more than 7 words";
			}
			if(palabra.length() < 2 || palabra.length() > tamanoTablero-1){
				throw "Words must be at least two characters and no more than the grid size";
			}
		}
	}
	else{
		throw "Cannot open words list file";
	}
}

void GeneradorSopa::insertarPalabraDeArchivo(){
	//Iterate through all of the indexes in the array and insert them into the grid
	for(int i=0;i<(int)(sizeof(palabras)/sizeof(palabras[0]));i++){
		string palabra = palabras[i];
		insertarPalabra(palabra.c_str()); //Convert the word (std::string) into a useable char* array
	}
}

void GeneradorSopa::respuestaArchivo(char* filename){
	ofstream output(filename);
	char c;
	if(output.is_open()){
		printf("Writing to file '%s'\n",filename);
		for(int i=0;i<tamanoTablero;i++){
			for(int k=0;k<tamanoTablero;k++){
				if(k == tamanoTablero-1){
					c = tablero[i][k];
					output.put(c);
					output.put('\n');	//Append a newline if it is on the last column
				}
				else{
					c = tablero[i][k];
					output.put(c);
				}
		}}
	}
	else{
		throw "Cannot create output file";
	}
}
