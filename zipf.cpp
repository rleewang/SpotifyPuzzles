#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Song {
  string name;
  long actualPlays;
  long predictedPlays;
  double quality;
  int trackNumber;
};

bool compareQuality(Song* lhs, Song* rhs) {
  return (lhs->quality > rhs->quality);
}

void sort(vector<Song*>& songs, bool (*compare) (Song*, Song*)){
  //Insertion sort
  //Sorting needs to maintain relative ordering
  Song* tempSong, *compareSong;
  long j;

  for(long i = 1; i < songs.size(); i++) {
    compareSong = songs[i];
    j = i;
    while(j > 0 && compare(songs[j], songs[j-1])) {
      tempSong = songs[j];
      songs[j] = songs[j-1];
      songs[j-1] = tempSong;
      j--;
    }
    songs[j] = compareSong;
  }
}

bool validName(string name) {
  if(name.length() > 30) {
    return false;
  }

  for(int i = 0; i < name.length(); i++) {
    //characters fall in 0-9
    if( (name[i] > 47 && name[i] < 58)
	//characters fall in a-z
	|| (name[i] > 96 && name[i] < 123)
	//character is _
	|| (name[i] == 95) ) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

int main() {
  /*
  Input contains integers n, m s.t. n in [1, 50000] and m in [1, n]
  n is the number of songs in the album
  m is the number of songs to select
  Followed by n lines of input each containing int f_i and string s_i
  f_i is the number of times the ith song was listened to
  s_i is the name of the song {a-z, 0-9, _}

  Outputs is a list of the m songs with the highest quality q_i in decreasing order of quality
  If two songs have the same quality, give precedence to the one appearing first on the album
  */
  
  //Zipf's Law: q_i = f_i/z_i (f_i plays / z_i expected plays)
  //z_i is 1/i
  
  //numSongs = n, numToSelect = m
  long numSongs, numToSelect;
  std::cin >> numSongs >> numToSelect;
  
  if(numSongs < 1 || numSongs > 50000 || numToSelect > numSongs || numToSelect < 1) {
    return 0;
  }

  Song* inputSong;
  vector<Song*> songs;

  for(long i = 0; i < numSongs; i++) {
    inputSong = new Song();
    std::cin >> inputSong->actualPlays >> inputSong->name;
    inputSong->trackNumber = i+1;
 
    if(!validName(inputSong->name) 
       || inputSong->actualPlays < 0 || inputSong->actualPlays > 1000000000000) {
      i--;
      delete inputSong;
      continue;
    }
    songs.push_back(inputSong);
  }

  long firstPlays = songs[0]->actualPlays;
  Song* song;

  //Calculate predicted plays via zipf's law now that songs have been sorted by highest play frequency
  for(long i = 0; i < numSongs; i++) {
    song = songs[i];
    song->predictedPlays = (long ) ceil((double) firstPlays / song->trackNumber);
    song->quality = (double) song->actualPlays / (double) song->predictedPlays;
    //song->quality = song->actualPlays * song->trackNumber;
  }
  
  //Now sort by quality for selection
  sort(songs, &compareQuality);

  //Print out selected # of top quality songs
  for(long i = 0; i < numToSelect; i++) {
    //std::cout << ptrSong->name << " " << ptrSong->quality << std::endl;
    std::cout << songs[i]->name << std::endl;
    //std::cout << songs[i]->name << " has " << songs[i]->actualPlays << " plays & "
    //	      << songs[i]->predictedPlays << " predicted plays with quality of "
    //	      << songs[i]->quality << std::endl;
  }

  return 0;
}
