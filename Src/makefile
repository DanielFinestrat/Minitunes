all: minitunes clean

OPTS=-Wall -g
OBJS=Player.o Song.o Collection.o Playlist.o Utils.o
CC=g++

minitunes: $(OBJS) minitunes.o
	$(CC) $(OPTS) $(OBJS) minitunes.o -o minitunes

minitunes.o: minitunes.cc Player.h Song.h Constants.h
	$(CC) $(OPTS) -c minitunes.cc

Utils.o: Utils.cc Utils.h Collection.h Playlist.h Constants.h
	$(CC) $(OPTS) -c Utils.cc

Playlist.o: Playlist.cc Playlist.h Song.h Collection.h Player.h Constants.h
	$(CC) $(OPTS) -c Playlist.cc

Collection.o: Collection.cc Collection.h Song.h Constants.h
	$(CC) $(OPTS) -c Collection.cc
	
Song.o: Song.cc Song.h Constants.h
	$(CC) $(OPTS) -c Song.cc

Player.o: Player.cc Player.h
	$(CC) $(OPTS) -c Player.cc


clean:
	rm -rf *.o
	rm -rf *~

