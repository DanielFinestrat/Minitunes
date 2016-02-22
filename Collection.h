//Daniel Finestrat Martinez, 2014

#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <iostream>
#include <vector>
#include "Song.h"

using namespace std;

class Collection{
	private:
	int idNextSong;
	vector<Song> songs;

	public:
	Collection(){
		this->idNextSong=1;
	}
	int findIdSong(int id) const;
	bool isSongInCollection(Song song) const;
	bool show() const;
	bool addSong();
	void editSong();
	void menuEdit(int posicion);
	void deleteSong();
	bool importJSON(string filename);
	bool read(ifstream &f);
	bool write(ofstream &f) const;
	Song getSongAt(int index) const;
	int size() const;
	void clear();
};

#endif
