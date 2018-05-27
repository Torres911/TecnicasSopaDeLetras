#include"Clases.cpp"


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
	GeneradorSopa gen;
	try{
		gen.leerArchivo(words_list);
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	gen.limpiarTablero();
	gen.insertarPalabraDeArchivo();
	gen.llenarTablero();
	gen.imprimirTablero();
	try{
		gen.respuestaArchivo(output_file);
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	return 0;
}