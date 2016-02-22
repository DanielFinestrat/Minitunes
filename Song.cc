//Daniel Finestrat Martinez, 2014

#include "Utils.h"

Song::Song(const SongBin &songbin){
	this->setId(songbin.id);
	this->setTitle(songbin.title);
	this->setArtist(songbin.artist);
	this->setAlbum(songbin.album);
	this->setGenre(songbin.genre);
	this->setUrl(songbin.url);
}

Song::Song(string JSONline){
	string searchField, campo;

	searchField="\"trackName\":\"";							//Guarda la cadena correspondiente.
	campo=getFieldFromJSONline(searchField, JSONline);		//Consigue el campo.
	this->setTitle(campo);									//Lo escribe.

	searchField="\"collectionName\":\"";
	campo=getFieldFromJSONline(searchField, JSONline);
	this->setAlbum(campo);

	searchField="\"artistName\":\"";
	campo=getFieldFromJSONline(searchField, JSONline);
	this->setArtist(campo);

	searchField="\"primaryGenreName\":\"";
	campo=getFieldFromJSONline(searchField, JSONline);
	this->setGenre(campo);

	searchField="\"previewUrl\":\"";
	campo=getFieldFromJSONline(searchField, JSONline);
	this->setUrl(campo);
}

Song::Song(int id, string title, string artist, string album, string genre, string url){
	this->id = id;
	this->title = title;
	this->artist = artist;
	this->album = album;
	this->genre = genre;
	this->url = url;
}

string Song::getFieldFromJSONline(string searchField, string JSONline){

	int i, principio, final;
	string campo="";

	principio=JSONline.find(searchField);					//Busca y guarda la posicion del primer caracter(principio).

	if(principio!=-1){										//Si la encuentra, sigue con el proceso.
		principio+=searchField.length();
		final=JSONline.find("\"",principio);				//Busca y guarda la posicion del ultimo caracter(final).
		for(i=principio; i<final; i++){						//Asigna al campo artist desde "principio" hasta "final". Si no la ha encontrado, se salta este paso.
			campo+=JSONline[i];
		}
	}

	return(campo);
}

bool Song::isEqual(const Song &song) const{
	bool equal = false;

	if(this->getTitle()==song.getTitle() && this->getArtist()==song.getArtist()){
		equal=true;
	}
	return(equal);
}

void Song::printPlaylist() const{
	cout<<this->getId()<<": "<<this->getTitle()<<" ("<<this->getArtist()<<")";
}

void Song::printXSPF(ofstream &f) const{
	f<<"\t\t<track>"<<endl
	 <<"\t\t\t<title>"<<this->getTitle()<<"</title>"<<endl
	 <<"\t\t\t<creator>"<<this->getArtist()<<"</creator>"<<endl
	 <<"\t\t\t<album>"<<this->getAlbum()<<"</album>"<<endl
	 <<"\t\t\t<location>"<<this->getUrl()<<"</location>"<<endl
	 <<"\t\t\t<meta rel=\"genre\">"<<this->getGenre()<<"</meta>"<<endl
	 <<"\t\t</track>"<<endl;
}

SongBin Song::toBinary() const{

	SongBin songbin;

	songbin.id=this->getId();

	strncpy(songbin.title, this->getTitle().c_str(), kTITLE-1);			//Copia el máximo de caracteres.
	songbin.title[kTITLE-1]='\0';									//Cierra la cadena.

	strncpy(songbin.artist, this->getArtist().c_str(), kARTIST-1);
	songbin.artist[kARTIST-1]='\0';

	strncpy(songbin.album, this->getAlbum().c_str(), kALBUM-1);
	songbin.album[kALBUM-1]='\0';

	strncpy(songbin.genre, this->getGenre().c_str(), kGENRE-1);
	songbin.genre[kGENRE-1]='\0';

	strncpy(songbin.url, this->getUrl().c_str(), kURL-1);
	songbin.url[kURL-1]='\0';

	return(songbin);
}

ostream& operator<< (ostream &os, const Song& song) {
	os << song.id<<" | "<<song.title<<" | "<<song.artist<<" | "<<song.album<<" | "<<song.genre;
	return os;
}

istream& operator>> (istream &is, Song& song) {
	string aux;

	//Utils::limpiabuffer();
	cout<<"Title: ";
	getline(is,aux);
	song.setTitle(aux);

	cout<<"Artist: ";
	getline(is,aux);
	song.setArtist(aux);

	cout<<"Album: ";
	getline(is,aux);
	song.setAlbum(aux);

	cout<<"Genre: ";
	getline(is,aux);
	song.setGenre(aux);

	cout<<"Url: ";
	getline(is,aux);
	song.setUrl(aux);

	return (is);
}
