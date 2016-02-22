//Daniel Finestrat Martinez, 2014

#ifndef _SONG_H_
#define _SONG_H_

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int kTITLE=30;
const int kARTIST=60;
const int kALBUM=60;
const int kGENRE=30;
const int kURL=255;

typedef struct{
	int id;
	char title[kTITLE];
	char artist[kARTIST];
	char album[kALBUM];
	char genre[kGENRE];
	char url[kURL];
}SongBin;

class Song{

	friend ostream& operator<< (ostream &os, const Song& song);
	friend istream& operator>> (istream &is, Song& song);

	private:
	int id;
	string title;
	string artist;
	string album;
	string genre;
	string url;

	public:
	Song(){};
	Song(int id, string title, string artist, string album, string genre, string url);
	Song(string JSONline);
	Song(const SongBin &songbin);

	int getId() const{
		return(id);
	};
	string getTitle() const{
		return(title);
	};
	string getArtist() const{
		return(artist);
	};
	string getAlbum() const{
		return(album);
	};
	string getGenre() const{
		return(genre);
	};
	string getUrl() const{
		return(url);
	};

	void setId(int id){
		this->id = id;
	}
	void setTitle(string title){
		this->title = title;
	};
	void setArtist(string artist){
		this->artist = artist;
	};
	void setAlbum(string album){
		this->album = album;
	};
	void setGenre(string genre){
		this->genre = genre;
	};
	void setUrl(string url){
		this->url = url;
	};

	string getFieldFromJSONline(string searchField, string JSONline);
	bool isEqual(const Song &song) const;
	void printPlaylist() const;
	void printXSPF(ofstream &f) const;
	SongBin toBinary() const;
};

#endif
