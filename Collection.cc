//Daniel Finestrat Martinez, 2014

#include "Collection.h"
#include "Utils.h"

int Collection::findIdSong(int id) const{
	int i;
	int posicion=-1;

	for(i=0;i<this->size();i++){
		if(this->getSongAt(i).getId()==id){
			posicion=i;
		}
	}
	return(posicion);
}

bool Collection::isSongInCollection(Song song) const{
	int i;
	bool repetida=false;

	for(i=0;i<this->size() && repetida != true;i++){							//Si coincide title y artist, se considera repetida.
		repetida=song.isEqual(this->getSongAt(i));
	}
	return(repetida);
}

bool Collection::show() const{
	Song song;
	string buscar;
	bool encontrado=false;
	int i;

	//Utils::limpiabuffer();
	cout<<"Search: ";
	getline(cin,buscar);

	for(i=0;i<this->size();i++){							//Hace las comprobaciones en todas las canciones.

		if(this->getSongAt(i).getTitle().find(buscar)!=string::npos ||
			this->getSongAt(i).getArtist().find(buscar)!=string::npos ||
			this->getSongAt(i).getAlbum().find(buscar)!=string::npos ||
			this->getSongAt(i).getGenre().find(buscar)!=string::npos){

			encontrado=true;
			song=this->getSongAt(i);
			cout<<song;
			cout<<endl;
		}
	}

	if(encontrado==false){											//Si no encuentra nada, encontrado es FALSE y saca el mensaje.
		cout<<"No results"<<endl;
	}

	return(encontrado);
}

bool Collection::addSong(){
	Song song;

	bool repetida=false,anyadida=true;
	cin>>song;												//Introduces la cancion.
	repetida=this->isSongInCollection(song);					//Compruebas si esta repetida.
	if(repetida==false){										//Si no esta repetida la introduce e incrementa idNextSong
		song.setId(this->idNextSong);
		this->idNextSong++;
		this->songs.push_back(song);
		anyadida=true;
	}else if(repetida==true){									//Si esta repetida no la introduce y saca el mensaje
		anyadida=false;
		cout<<"The song "<<song.getTitle()<<" is already in the collection"<<endl;
	}

	return(anyadida);
}

void Collection::editSong(){								//Seleccionas cancion y te lleva a menuEdit() para editar.

	bool encontrada;
	int id, posicion;

	encontrada=this->show();							//Muestra la coleccion.
	if(encontrada==true){
		cout<<"Select song: ";
		cin>>id;
		Utils::limpiabuffer();
		posicion=this->findIdSong(id);					//Te da la posicion segun la ID.
		if(posicion==-1){
			cout<<"Error: Unknown song "<<id<<endl;
		}else this->menuEdit(posicion);						//Si la encuentra, te lleva al menu de edicion.
	}
}

void Collection::menuEdit(int posicion){
	int op;
	string aux;

	do{
		cout<<"Edit (1-Title, 2-Artist, 3-Album, 4-Genre, 5-Url): ";
		cin>>op;
		Utils::limpiabuffer();
		if(op<1 || op>5) cout<<"Error: Unknown option"<<endl;
	}while(op<1 || op>5);													//Bucle de comprobacion

	//Utils::limpiabuffer();													//Limpia el buffer de entrada

	switch(op){
	case 1:
		cout<<"Title: ";
		getline(cin,aux);
		this->songs[posicion].setTitle(aux);
		break;

	case 2:
		cout<<"Artist: ";
		getline(cin,aux);
		this->songs[posicion].setArtist(aux);
		break;

	case 3:
		cout<<"Album: ";
		getline(cin,aux);
		this->songs[posicion].setAlbum(aux);
		break;

	case 4:
		cout<<"Genre: ";
		getline(cin,aux);
		this->songs[posicion].setGenre(aux);
		break;

	case 5:
		cout<<"Url: ";
		getline(cin,aux);
		this->songs[posicion].setUrl(aux);
		break;
	}
}

void Collection::deleteSong(){

	Song song;
	bool encontrada;
	int id, posicion;
	char confirmacion;

	encontrada=this->show();;							//Muestra coleccion.

	if(encontrada==true){
		cout<<"Select song: ";
		cin>>id;
		Utils::limpiabuffer();
		posicion=this->findIdSong(id);					//Te da la posicion en el vector segun la ID.

		if(posicion==-1){
			cout<<"Error: Unknown song "<<id<<endl;
		}else{
			song=this->songs[posicion];
			cout<<"Delete ";
			cout<<song;
			cout<<"?(Y/N): ";
			cin>>confirmacion;
			Utils::limpiabuffer();

			if(confirmacion=='Y'){									//Confirmas con Y, cualquier otra respuesta no la elimina
				this->songs.erase(this->songs.begin()+posicion);

			}else cout<<"Song not deleted"<<endl;
		}
	}
}

bool Collection::importJSON(string filename){
	string JSONline;
	ifstream f;
	bool opened=true;
	Song song;
	bool repetida;
	string lineaConCancion="\"kind\":\"song\"";

	f.open(filename.c_str(),ios::in);

	if(f.is_open()){
		getline(f,JSONline);										//Introduzco la primera linea en el string JSONline.
		while(!f.eof()){											//Mientras  no sea el final del fichero.

			if(JSONline.find(lineaConCancion)!=string::npos){		//Tiene que tener esto para que haya una cancion en la JSONline.

				Song song(JSONline);								//Consigo la cancion de la linea.
				repetida=this->isSongInCollection(song);			//Compruebo si ya estaba en la coleccion.

				if(repetida){
					cout<<"The song "<<song.getTitle()<<" is already in the collection"<<endl;
				}else{												//Si no esta repetida la mete en la coleccion(actualiza el idNextSong).
					song.setId(this->idNextSong);
					this->idNextSong++;
					this->songs.push_back(song);
				}
			}
			getline(f,JSONline);
		}
		f.close();													//Se cierra el fichero.

	}else{
		cout<<"Error opening file "<<filename<<endl;
		opened=false;
	}
	//cout<<"opened tiene el estado "<<opened<<endl;
	return(opened);
}

bool Collection::read(ifstream &f){
	bool abierto=false;
	SongBin songbin;
	//Song song;

	this->clear();												//Primero vaciamos la coleccion.

	if(f.is_open()){
		abierto = true;
		f.read((char *)&this->idNextSong, sizeof(this->idNextSong));//Despues leemos el idNextSong.

		f.read((char *)&songbin, sizeof(songbin));					//Hacemos la primera lectura.
		while(!f.eof()){
			Song song(songbin);										//Las convertimos a el formato de nuestra coleccion.
			this->songs.push_back(song);							//Las guardamos.
			f.read((char *)&songbin, sizeof(songbin));				//Volvemos a leer.
		}
	}
	//cout<<"el estado de abierto(read) es "<<abierto<<endl;
	return(abierto);
}

bool Collection::write(ofstream &f) const{
	bool abierto=false;
	int i;
	SongBin songbin;

	if(f.is_open()){
		abierto=true;
		f.write((const char *)&this->idNextSong, sizeof(this->idNextSong));		//Primero escribo el idNextSong.
		for(i=0;i<this->size();i++){
			songbin=this->getSongAt(i).toBinary();								//Paso cada cancion a su formato correspondiente.
			f.write((const char *)&songbin, sizeof(songbin));					//Escribo cada cancion en el archivo.
		}
	}
	//cout<<"el estado de abierto(write) es "<<abierto<<endl;
	return(abierto);
}

Song Collection::getSongAt(int index) const{
	Song song;
	song = this->songs[index];
	return (song);
}

int Collection::size() const{
	int size;
	size = this->songs.size();
	return (size);
}

void Collection::clear(){
	this->songs.clear();
	this->idNextSong = 1;
}
