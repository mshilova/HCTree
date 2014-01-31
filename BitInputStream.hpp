#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

/*
 * A class file desiged to turn bytes into bits.
 */

 class BitInputStream {
  private: 
    char buf;             // one byte buffer of bits
    int nbits;            // how many bits have been read from buf
    std::istream & in;    // the input stream to use

  public:

    /** Initialize a BitInputStream that will use the given istream for input */
    BitInputStream(std::istream & is) : in(is) { 
      buf = 0;      // clear buffer
      nbits = 8;    // initialize bit index  
    }

   /** Fill the buffer from the input */
    void fill() ;

    /** Read the next bit from the bit buffer */
    int readBit();

};
#endif
