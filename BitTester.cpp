#include <iostream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

int main(int argc, char** argv){

  ofstream out(argv[1]) ; 
  BitOutputStream bos(out);
  
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(1);
// Should print out A
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(1);

  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(1);
// Should print out A
  
 // Should print out B  
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);

 // Should print out B  
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);



 // Should print out B  
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(0);
  bos.writeBit(1);
  bos.writeBit(0);


  cout << endl;
  return 0;
}

