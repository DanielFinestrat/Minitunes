//Daniel Finestrat Martinez, 2014

#include <iostream>
#include <string.h>
#include "Player.h"
#include "Collection.h"
#include "Playlist.h"
#include "Utils.h"

using namespace std;

bool leermenu(int op, Collection &collection, Playlist &playlist){			//Lee la respuesta del menu principal y llama a la funcion correspondiente.

	bool continuar=true;
	string filename;
	char confirmacion;

	switch(op){
	case '1':
		collection.addSong();
		break;

	case '2':
		collection.editSong();
		break;

	case '3':
		collection.deleteSong();
		break;

	case '4':
		collection.show();
		break;

	case '5':
		playlist.manage();
		break;

	case '6':
		cout<<"Filename: ";
		getline(cin, filename);
		collection.importJSON(filename);
		break;

	case '7':
		playlist.saveXSPF();
		break;

	case '8':
		Utils::saveData(collection, playlist);
		break;

	case '9':
		if(collection.size()<=0){										//Si la coleccion esta vacia, entra directamente a la funcion.
			Utils::loadData(collection, playlist);
		}else{																//Si la coleccion no esta vacia, saca mensaje de confirmacion.
			cout<<"Delete previous collection? (Y/N): ";
			cin>>confirmacion;
			Utils::limpiabuffer();
			if(confirmacion=='Y'){
				Utils::loadData(collection, playlist);
			}
		}
		break;

	case '0':
		playlist.play();
		break;

	case 'q':
		continuar=false;
		break;

	default:
		cout<<"Error: Unknown option"<<endl;
		break;
	}

	return(continuar);
}

int main(int argc, char *argv[]){											//Muestra el menu y llama a leermenu() para leerlo.

	Collection collection;
	Playlist playlist(&collection);
	char op;
	bool continuar=true;

	if(argc>1){
		continuar=Utils::manageArguments(argc,argv,collection,playlist);
	}

	while(continuar==true){
		cout<<"--------------------------------"<<endl
			<<"----------- MiniTunes ----------"<<endl
			<<"--------------------------------"<<endl
			<<"1- Add song"<<endl
			<<"2- Edit song"<<endl
			<<"3- Delete song"<<endl
			<<"4- Show collection"<<endl
			<<"5- Manage playlist"<<endl
			<<"6- Import iTunes JSON data"<<endl
			<<"7- Export playlist to XSPF "<<endl
			<<"8- Save data"<<endl
			<<"9- Load data"<<endl
			<<"0- Play playlist"<<endl
			<<"q- Quit"<<endl
			<<"Option: ";
		cin>>op;
		Utils::limpiabuffer();

		continuar=leermenu(op,collection,playlist);

	}
	return 0;
}
