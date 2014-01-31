#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "HCTree.hpp"
#include "HCNode.hpp"

/*
 * Application to read compressed fills and out put uncompressed files
 */

using namespace std;

int main( int argc, char** argv){
  // Check the input
  if( argc != 3 ){
    cout << " Please enter two valid file names " << endl;
    return -1; 
  }

  char* compressed = argv[1];
  char* uncompressed = argv[2];

  // Open compressed file
  ifstream in;
  in.open(compressed, ios::binary);
  BitInputStream bin(in);

  // Read Header - Note header is in binary
  cout << "Reading header from file \"" << compressed <<"\"...";

  vector<int> v(256,0);

   // Find out how many symbols are in the tree
   int count;
   in.read(reinterpret_cast<char*>(&count), sizeof(int));

   // Fill in the frequency vector v
   // Count the size of file
   int fsize = 0; 
   unsigned char symbol;
   int freq;
   for(int i=0; i<count; i++){
    in.read(reinterpret_cast<char*>(&symbol), sizeof(char));
    in.read(reinterpret_cast<char*>(&freq), sizeof(int));
    v[symbol] = freq;
    fsize += freq;
   }

  cout << "done. " << endl;
  cout<<"Uncompressed file will have "<<count<<" unique symbols and size "
                                              <<fsize << " bytes." <<endl;
  

  // Build Tree from Table 
  cout << "Building Huffman code tree... " ;
  HCTree myTree;

  if(count != 0)
      myTree.build(v);

  cout << "done." << endl;

  ofstream out;
  out.open(uncompressed, ios::binary);
  cout<< "Writing to file \"" <<uncompressed<<"\"... ";
  for (int i=0; i<fsize; i++){
      symbol = myTree.decode(bin); 
      out << symbol;
  }
  cout<<"done."<<endl;
  // Close files
  out.close();
  in.close();

  int csize=0;
  ifstream uncom;
  uncom.open(compressed, ios::binary);
  while(uncom.good())  {
    uncom.get();
    if(!uncom.good()) break;
    csize++;
  }
  cout<<"uncompressed size is "<<csize<<endl;
  double ratio = (double) fsize/csize;
  cout<<"Uncompression ratio: "<<ratio<<endl;

return 0;
};
