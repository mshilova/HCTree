#include "BitOutputStream.hpp"
#include <iostream>
#include <bitset>

/**
 * Implementation of BitOutputStream
 * See BitOutputStream.hpp
 */ 

/** 
 * Helper function. A the buffer gets full,
 * writing to the output file and resetting the file.
 * Called in writeBit.
 */ 
void BitOutputStream::flush(){
  out << (char) buf;
  buf = nbits = 0;
}

/**
 * Flush if the buffer is full, else
 * write the least significant bit of 
 * the parameter into the buffer at 
 * the current index.
 */ 
void BitOutputStream::writeBit(int i)  { 

  int temp  = i << (7-nbits);
  buf = buf | temp;
  nbits++;  // increment the index
  if(nbits == 8)  {
    flush();
  }
}
