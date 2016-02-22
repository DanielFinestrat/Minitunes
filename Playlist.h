//Daniel Finestrat Martinez, 2014

#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <iostream>
#include <vector>
#include <sstream>
#include "Player.h"
#include "Collection.h"
using namespace std;

class Playlist{

private:


public:
	vector<int> idSong;
	Collection *pcollection;
	Playlist(Collection *collection);
	int size() const;
	void print(int position) const;
	Song songFromPositionInPlaylist(int i) const;
	void manage();
	void addSongs();
	void removeSongs();
	bool findIdSongInPlaylist(int id);
	void deletePlaylistSong(int id);
	void clearSongs();
	bool saveXSPF() const;
	void play() const;
	string getUrl(int position) const;
	bool read(ifstream &f);
	bool write(ofstream &f) const;

};

#endif
