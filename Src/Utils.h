//Daniel Finestrat Martinez, 2014

#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include "Playlist.h"
#include "Collection.h"

using namespace std;

class Utils{
	public:
	static void limpiabuffer(){												//Limpiar el buffer para los getline.
		while(cin.get()!='\n');
	}
	static bool saveData(const Collection &collection, const Playlist &playlist);
	static bool loadData(Collection &collection, Playlist &playlist);
	static bool manageArguments(int argc, char *argv[], Collection &collection, Playlist &playlist);
};

#endif
