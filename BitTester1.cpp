#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <iostream>

using namespace std;

int main (int argc, char** argv)  {

  ifstream in(argv[1]);
  BitInputStream bin(in);

  BitOutputStream bout(cout);

  int bit;
  for(int i=0; i < 48; i++)  {
    bit =  bin.readBit();
    bout.writeBit(bit);
  }

  bout.flush();


  return 0;
}
