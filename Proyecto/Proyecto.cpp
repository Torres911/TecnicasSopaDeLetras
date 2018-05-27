#

const int tamanoTablero = 10;

Generator::Generator(){
	NULL_CHAR = 'x'; //Sets the null char to a lowercase x
}

char Generator::GenerateRandomChar(){
	return 'A' + rand()%26; //leet way to generate a random character
}

//Sets all values in grid to a null character
void Generator::ClearGrid(){
	for(int i=0;i<tamanoTablero;i++){
		for(int k=0;k<tamanoTablero;k++){
			tablero[i][k] = NULL_CHAR; //Every empty value will be a lowercase x
		}
	}
}

//Checks if word can be inserted in the grid at the given start point
bool Generator::CanInsert(const char* word, puntoInicial start, direccion d){
	int i = 0;
	puntoInicial nuevoPunto = start;
	while(i < (int)strlen(word)) //Iterates through the word char array
	{
		//Attempt to shift the point
		try{
			if(tablero[nuevoPunto.i][nuevoPunto.k] == NULL_CHAR){
				nuevoPunto = ShiftPoint(nuevoPunto,d);
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
void Generator::FillGrid(){
	for(int i=0;i<tamanoTablero;i++){
		for(int k=0;k<tamanoTablero;k++){
			if(tablero[i][k] == NULL_CHAR){
				tablero[i][k] = GenerateRandomChar(); //Set every null value to a random character
			}
		}
	}
}

//Prints the grid to stdout
void Generator::PrintGrid(){
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
puntoInicial Generator::ShiftPoint(puntoInicial start, direccion d){
	int i = start.i;
	int k = start.k;
	puntoInicial nuevoPunto;
	switch(d){
		case UP:
			nuevoPunto.i = i-1; //Move up a row
			nuevoPunto.k = k;   //Column stays the same
			break;
		case DOWN:
			nuevoPunto.i = i+1;  //Move down a row
			nuevoPunto.k = k;    //Column stays the same
			break;
		case LEFT:
			nuevoPunto.i = i; //Row stays the same
			nuevoPunto.k = k-1; //Column moves left
			break;
		case RIGHT:
			nuevoPunto.i = i; //Row stays the same
			nuevoPunto.k = k+1; //Column moves right
			break;
		case UP_LEFT:
			nuevoPunto.i = i-1; //Row moves up
			nuevoPunto.k = k-1; //Column moves left
			break;
		case UP_RIGHT:
			nuevoPunto.i = i-1; //Row moves up
			nuevoPunto.k = k+1; //Column moves right
			break;
		case DOWN_LEFT:
			nuevoPunto.i = i+1; //Row moves down
			nuevoPunto.k = k-1; //Column moves to left
			break;
		case DOWN_RIGHT:
			nuevoPunto.i = i+1; //Row moves down
			nuevoPunto.k = k+1; //Column moves right
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


void Generator::InsertWord(const char* word){
	puntoInicial start;
	direccion d;
	do{
		start.i = rand() % tamanoTablero; //set to a random row
		start.k = rand() % tamanoTablero; //set to a random column
		d = direccion(rand() % 8); //get a random direction
	}
	while(!CanInsert(word,start,d));
	int i = 0;
	puntoInicial nuevoPunto = start;
	while(i < (int)strlen(word))
	{
		tablero[nuevoPunto.i][nuevoPunto.k] = (char)toupper(word[i]);
		nuevoPunto = ShiftPoint(nuevoPunto,d);
		i++;
	}
}

void Generator::ReadFile(char* filename){
	ifstream wordsFile(filename);
	string word;
	int line = 0;
	if(wordsFile.is_open()){
		printf("Reading file '%s'\n",filename);
		while(getline(wordsFile,word)){
			palabras[line] = word;
			line++;
			if(line == 8){
				throw "Words list can not have more than 7 words";
			}
			if(word.length() < 2 || word.length() > tamanoTablero-1){
				throw "Words must be at least two characters and no more than the grid size";
			}
		}
	}
	else{
		throw "Cannot open words list file";
	}
}

void Generator::InsertWordsFromFile(){
	//Iterate through all of the indexes in the array and insert them into the grid
	for(int i=0;i<(int)(sizeof(palabras)/sizeof(palabras[0]));i++){
		string word = palabras[i];
		InsertWord(word.c_str()); //Convert the word (std::string) into a useable char* array
	}
}

void Generator::PuzzleToFile(char* filename){
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

int main(int argc, char* argv[]){
	/* initialize random seed: */
	srand (time(NULL));
	char* words_list;
	char* output_file;
	switch(argc){
		case 1:
			words_list = "words_list";
			output_file = "output";
			break;
		case 2:
			if(strcmp(argv[1],"--help") == 0){
				printf("Usage: ./generator <words list> <output file>\n");
				exit(1);
			}
			else{
			words_list = argv[1];
			output_file = "output";
			}
			break;
		case 3:
			words_list = argv[1];
			output_file = argv[2];
			break;
		default:
			printf("Usage: ./generator <words list> <output file>\n");
			exit(1);
	}
	Generator gen;
	try{
		gen.ReadFile(words_list);
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	gen.ClearGrid();
	gen.InsertWordsFromFile();
	gen.FillGrid();
	gen.PrintGrid();
	try{
		gen.PuzzleToFile(output_file);
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	return 0;
}