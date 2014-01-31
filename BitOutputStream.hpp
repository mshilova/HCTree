#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>
#include <fstream>

/**
 * A class that is designed to turn bits into bytes
 */ 

class BitOutputStream  {

private:
  char buf;          // one byte buffer of bits to write to output
  int nbits;         // number of bits that are written to buf
  std::ostream & out; // reference to the output stream 
 


public:
  BitOutputStream(std::ostream & os): out(os), buf(0), nbits(0) {
    // clearing buffer and index
  }
  

  /**
   * Write the least significant bit of the argument to the bit buffer,
   * and increment the bit buffer index.
   * But flush the buffer first, if it is full.
   */ 
  void writeBit(int i);


  /** send the buffer to the output, and clear it */
  void flush();  

};
#endif
