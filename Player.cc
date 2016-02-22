//Daniel Finestrat Martinez, 2014
 
#include "Player.h"
#include <sys/stat.h> // mkfifo
#include <unistd.h>   // unlink
#include <cstdio>     // remove
#include <cstdlib>    // system
 
const string path="/tmp/p2fifofile";
 
//Reproduce cancion de url
void Player::playSong(string link){
  
  if (fifo.is_open()) {
    fifo << "quit" << endl;
    fifo.close();
  }
   
  remove(path.c_str());
 
  //Creamos fichero comunicacion con mplayer
  if (link!=""){
    if (mkfifo(path.c_str(), 0666 ) < 0 ) { cout << "Error opening file " << path << endl; }
    else{
      string mplayercommand="mplayer -idle -slave -quiet -input file=" + path + " " + link + " >/dev/null 2>/dev/null&";
      system(mplayercommand.c_str());
      fifo.open(path.c_str());
      if (!fifo.is_open()) cout << "Error opening file " << path << endl;
    }
  }
  else cout << "No link for this song" << endl;
}
 
//Destructor
Player::~Player(){
   if (fifo.is_open()){
     fifo << "quit" << endl;
     fifo.close();
     unlink(path.c_str());
   }
}
 
//Pausa
void Player::pauseResumeSong(){
  if (fifo.is_open()) fifo << "pause" << endl;
}
