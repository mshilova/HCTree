#include <iostream>
#include <fstream>
#include "BitInputStream.hpp"

/**
 * All code for BitInputStream is implemented here.
 * See BitInputStream.hpp
 */

  /** Send the buffer to the output and clear it */
  void BitInputStream::fill() {
    buf = in.get();
    nbits=0;
  }

 /** 
  * Read the next bit from the bit buffer.
  * Fill the buffer from the input stream first if needed.
  * Return 1 if the bit read is 1 
  * Return 0 if the bit read is 0
  */
  int BitInputStream::readBit() {
    // If all bits in the buffer are read, fill the buffer first
    if(nbits==8)  {
      fill();
    }
    // Get the bit at the appriopriate location in the bit buffer and 
    // return the appropriate int
     int bit = buf >> (7-nbits);
     bit = 0x01 & bit;
   
    // Increment the index
    nbits++;
    return bit;
  }


