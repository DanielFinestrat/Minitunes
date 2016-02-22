//Daniel Finestrat Martinez, 2014

#ifndef _PLAYERC_H_
#define _PLAYERC_H_

#include <iostream>
#include <fstream>

using namespace std;

class Player{
  private:
    fstream fifo;

  public:
    Player(){};
    void playSong(string link);
    void pauseResumeSong();
    ~Player();
};

#endif
