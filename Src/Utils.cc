//Daniel Finestrat Martinez, 2014

#include "Utils.h"

const char DATA[]="minitunes.dat";

bool Utils::saveData(const Collection &collection, const Playlist &playlist){
	bool guardada=false;
	ofstream f;

	if(collection.size()>0){
		f.open(DATA, ios::out | ios::binary);						//Abre el archivo binario.
		if(f.is_open()){
			guardada=true;
			playlist.write(f);								//Si lo ha conseguido abrir, llama a las funciones de escritura.
			collection.write(f);
			f.close();												//Luego lo cierra
		}else{
			cout<<"Error opening file "<<DATA<<endl;				//Si no consigue abrirlo, saca error.
		}
	}else{
		cout<<"Empty collection"<<endl;								//Si no hay canciones en la coleccion tambien saca error.
	}
	return(guardada);
}

bool Utils::loadData(Collection &collection, Playlist &playlist){
	bool cargada=false;
	ifstream f;

		f.open(DATA, ios::in | ios::binary);						//Abre el archivo binario (como lectura).
		if(f.is_open()){
			cargada=true;
			playlist.read(f);								//Si lo ha conseguido abrir, llama a las funciones de lectura.
			collection.read(f);
			f.close();												//Luego lo cierra
		}else{
			cout<<"Error opening file "<<DATA<<endl;				//Si no consigue abrirlo, saca error.
		}
	return(cargada);
}

bool Utils::manageArguments(int argc, char *argv[], Collection &collection, Playlist &playlist){
	bool escorrecto=true;

	if(argc<3 && strcmp(argv[1],"-d" )==0){							//Si el primer argumento es -d, carga minitunes.dat.
		Utils::loadData(collection, playlist);
	}else if(argc>2 && argc<4 && strcmp(argv[1],"-i")==0){			//Si el segundo argumento es -i y hay mas de dos argumentos, carga el fichero JSON.
		collection.importJSON(argv[2]);
	}else if(argc>1){
		escorrecto=false;
		cout<<"Syntax: ./minitunes [-d] [-i jsonfilename]"<<endl;	//Si no se usa la sintaxis adecuada, saca mensaje y sale del programa.
	}

	return(escorrecto);
}
