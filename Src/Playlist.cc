//Daniel Finestrat Martinez, 2014

#include "Playlist.h"
#include "Utils.h"

Playlist::Playlist(Collection *collection) {
	pcollection=collection;
}

int Playlist::size() const{
	int size;
	size = this->idSong.size();
	return (size);
}

void Playlist::print(int position) const{
	Song song;
	int i;

	if(position==-1){												//Si la playlist no se esta reproduciendo, position es -1.
		for(i=0;i<this->size();i++){
			song=this->songFromPositionInPlaylist(i);
			song.printPlaylist();
			cout<<endl;
		}
	}else{															//Si se esta reproduciendo, position se corresponde a una posicion del vector playlist.
		for(i=0;i<this->size();i++){

			if(position==i){									//La cancion que se reproduce se marca con un '>'.
				cout<<">";
			}

			song=this->songFromPositionInPlaylist(i);
			song.printPlaylist();
			cout<<endl;
		}
	}
}

Song Playlist::songFromPositionInPlaylist(int i) const{

	Song song;
	int id, posicion;

	id=this->idSong[i];
	posicion=pcollection->findIdSong(id);
	song=pcollection->getSongAt(posicion);

	return(song);
}

void Playlist::manage(){
	char op;
	bool salir=false;

	do{
		cout<<"1- Add songs"<<endl
			<<"2- Remove songs"<<endl
			<<"3- Clear"<<endl
			<<"q- Back to main menu"<<endl
			<<"Option: ";

		cin>>op;
		Utils::limpiabuffer();

		switch(op){
		case '1':
			this->addSongs();
			break;
		case '2':
			this->removeSongs();
			break;
		case '3':
			this->clearSongs();
			break;
		case 'q':
			salir=true;
			break;
		default:
			cout<<"Error: Unknown option"<<endl;
			break;
		}
	}while(salir!=true);
}

void Playlist::addSongs(){
	string listaID;
	int id, posicion;

	if(pcollection->size()<=0){								//Comprueba si la coleccion esta vacia.
		cout<<"Empty collection"<<endl;
	}else{
		pcollection->show();									//Te muestra tu coleccion.
		cout<<"Select songs (list separated by spaces): ";
		getline(cin,listaID);									//Pide string con las ID separadas por espacios.
		istringstream iss(listaID);								//String a buffer de entrada iss.
		while(iss>>id){											//El bucle va introduciendo cada id(hasta el espacio) en la variable id.
			posicion=pcollection->findIdSong(id);
			if(posicion==-1){
				cout<<"Error: Unknown song "<<id<<endl;			//Si la id no existe, saca el error.
			}else{
				this->idSong.push_back(id);						//Si si que existe, la mete en la playlist.
			}
		}
	}
}

void Playlist::removeSongs(){
	string listaID;
	int position=-1, id;
	bool existe=false;

	if(this->idSong.empty()){									//Comprueba que la playlist no este vacia.
		cout<<"Empty playlist"<<endl;
	}else{
		this->print(position);
		cout<<"Select songs  (list separated by spaces): ";
		//Utils::limpiabuffer();
		getline(cin,listaID);										//Pide string con las ID separadas por espacios.
		istringstream iss(listaID);									//String a buffer de entrada iss.
		while(iss>>id){												//El bucle va introduciendo cada id(hasta el espacio) en la variable id.
			existe=this->findIdSongInPlaylist(id);				//Comprobamos si existe.
			if(!existe){
				cout<<"Error: Song "<<id<<" not in playlist"<<endl;	//Si la id no existe, saca el error.
			}else{
				this->deletePlaylistSong(id);					//Si si que existe, la borra del playlist.
			}
		}
	}
}

bool Playlist::findIdSongInPlaylist(int id){				//Recorre la playlist para ver si existe la cancion con el ID que se le pasa.

	unsigned i;
	bool existe=false;

	for(i=0;i<this->idSong.size();i++){
		if(this->idSong[i]==id){
			existe=true;
		}
	}

	return(existe);
}

void Playlist::deletePlaylistSong(int id){				//Elimina todas las canciones con el mismo identificador.

	unsigned i;

	for(i=0;i<this->idSong.size();i++){
		if(id==this->idSong[i]){
			this->idSong.erase(this->idSong.begin()+i);
			i--;													//Para que no se salte una cancion.
		}
	}
}

void Playlist::clearSongs(){
	char confirmacion;

	if(this->idSong.empty()){									//Comprueba que la playlist no este vacia.
		cout<<"Empty playlist"<<endl;
	}else{
		cout<<"Clear playlist? (Y/N): ";
		cin>>confirmacion;
		Utils::limpiabuffer();
		if(confirmacion=='Y'){										//Si metes Y, se borra. Cualquier otra cosa no hace nada.
			this->idSong.clear();
		}
	}
}

bool Playlist::saveXSPF() const{
	bool guardada=true;
	string filename;
	int i;
	Song song;
	ofstream f;

	if(this->idSong.empty()){									//Si la playlist esta vacia, saca mensaje y no hace nada mas.
		cout<<"Empty playlist"<<endl;
		guardada=false;
	}else{
		cout<<"Filename: ";
		//Utils::limpiabuffer();
		getline(cin, filename);										//Pide el nombre del fichero a abrir.
		f.open(filename.c_str(),ios::out);							//Abre el fichero y lo asigna a "f".
		if(f.is_open()){

			f<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl					//Escribe la cabezera.
			<<"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">"<<endl
			<<"\t<title>MiniTunes playlist</title>"<<endl
			<<"\t<trackList>"<<endl;

			for(i=0;i<this->size();i++){									//Escribe las canciones por separado.
				song=this->songFromPositionInPlaylist(i);
				song.printXSPF(f);
			}

			f<<"\t</trackList>"<<endl												//Escribe el pie.
			 <<"</playlist>";

			f.close();												//Cierra el archivo.
		}else{														//Si no consigue abrirlo, saca error.
			cout<<"Error opening file "<<filename<<endl;
			guardada=false;
		}
	}

	return(guardada);
}

void Playlist::play() const{
	char command;
	int position=0;
	bool exit=false;
	string url;

	if(!this->idSong.empty()){
		this->print(position);								//Mostramos la playlist.
		url=this->getUrl(position);							//Obtenemos la URL de la cancion que queremos reproducir.
		Player player;
		player.playSong(url);												//Empezamos a reproducir la primera inmediatamente.

		do{
			cout<<"Command: ";
			cin>>command;													//Pedimos un comando a ejecutar.
			Utils::limpiabuffer();

			switch(command){
			case 'p':
				player.pauseResumeSong();
				break;

			case 's':
				if(position==(int)this->idSong.size()-1){						//Si se pasa, volvemos a la primera cancion.
					position=0;
				}else{
					position++;												//Si no, incrementamos posicion.
				}

				this->print(position);										//Volvemos a imprimir la playlist.
				url=this->getUrl(position);
				player.playSong(url);
				break;

			case 'a':
				if(position==0){
					position=this->idSong.size()-1;						//Si es la primera, vamos a la última.
				}else{
					position--;											//Si no, decrementamos posicion.
				}


				this->print(position);									//Volvemos a imprimir la playlist.
				url=this->getUrl(position);
				player.playSong(url);
				break;

			case 'q':
				exit=true;

				break;

			default:
				cout<<"Options:"<<endl
					<<"p: Pause/resume"<<endl
					<<"s: Next song"<<endl
					<<"a: Previous song"<<endl
					<<"q: Quit"<<endl;
				break;
			}
		}while(exit==false);
	}else{
		cout<<"Empty playlist"<<endl;
	}
}

string Playlist::getUrl(int position) const{

	string url;
	Song song;

	song=this->songFromPositionInPlaylist(position);
	url=song.getUrl();

	return(url);
}

bool Playlist::read(ifstream &f){
	bool abierto=false;
	unsigned i, numelement;
	unsigned idSong;

	if(f.is_open()){
		abierto = true;
		this->idSong.clear();										//Primero vaciamos la playlist.
		f.read((char *)&numelement, sizeof(numelement));				//Despues leemos el numero de canciones de la playlist.

		for(i=0;i<numelement;i++){
			f.read((char *)&idSong, sizeof(idSong));					//Guardamos todos los ID de la playlist.
			this->idSong.push_back(idSong);
		}
	}

	return(abierto);
}

bool Playlist::write(ofstream &f) const{
	bool abierto=false;
	unsigned i, listsize=this->idSong.size();					//Guardo el tamanyo de la playlist en una variable para que sea mas comodo.

	if(f.is_open()){
		abierto=true;
		f.write((const char *)&listsize, sizeof(listsize));		//Imprimo el tamanyo.
		for(i=0;i<listsize;i++){
			f.write((const char *)&this->idSong[i], sizeof(this->idSong[i]));	//Imprimo cada uno de los ID.
		}
	}
	return(abierto);
}
