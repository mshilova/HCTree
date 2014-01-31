#include <iostream>
#include <fstream>
#include <vector>
#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"


/**
 * CSE100 P3
 * Application driver to read and compress input files
 */ 

  using namespace std;


int main(int argc, char** argv)  {

// Open the input file for reading
 if(argc != 3)  {
   // display error message if invalid number or arguments 
   cout<<"PLEASE ENTER TWO VALID FILES next time"<< endl;
   cout << "Correct input: infile outfile " << endl;
   return -1;
 }


  // var for arguments
  char* inFile = argv[1];
  char* outFile = argv[2];
  unsigned char symbol;  // symbol to keep track of
  ofstream out;  // reference to out file
  ifstream in; // referemce to input file
  // vector to hold counts of occurances
  vector<int> v(256,0);
  HCTree myTree; // Huffman Tree reference
  // integer to hold the number of distinct characters
  int count =0;
  // boolean to tell us if file was empty
  bool empty = true;
  // file size
  int fsize =0;
  // compressed file size
  int csize =0;
  // Compressed ratio
  double compressedratio =0;

 /*
  * First section of the program:
  * Open file - inFile
  * Create a vector holding the number of times each character appears in file
  * Read file incrementing v[index] where index = character being counted. 
  * Close file - inFile 
  * */

  // Reading the file
  in.open(inFile, ios::binary);

  cout << "Reading from file \""<< inFile << "\"...." ;
  // Go through file and count the number of times each byte shows up
  while(in.good())  {
      symbol = in.get();
      if( !in.good()) break; // Failure or end of file 
      if (v[symbol] == 0) count++; 
      v[symbol]++;
      fsize++;
      empty = false;
  }

  // Check to make sure that the entire file was visited
  if( !in.eof()) {
    cerr << "There was a problem reading the file. " << endl; 
    return -1;
  }
  cout << "done." << endl;
  cout << "Found " << count << " unique symbols in input file of size " 
       << fsize << "  bytes." << endl;
  
  // Close file - inFile
  in.close();

 /* 
  * Second section of the program:
  * Build Tree 
  */
  // Initialize and build tree

  cout << "Building Huffman code tree... " ;

  if(!empty){
    myTree.build(v);
  }
  cout << "done." << endl;


/* 
 * Third section of the program:
 * Open outfile
 * Insert Header
 * Encode each symbol - Code is in HSTree.cpp
 * Use BitOutputStream to get bit representation 
 * - Code is in BitOutputStream.cpp
 * Close out file
 */

  // Open file
  out.open(outFile, ios::binary);
  BitOutputStream bout(out);  // reference to BitOutputStream

  // Write header into out file - in binary
  // We are giving the header the following: 
  // Number of distinct characters in infile
  // For each distinct character we give the number and symbol 
  // i.e.
  // 4a1b1c2d1

  cout << "Writing to file \"" << outFile << "\"...." ; 
  
  out.write(reinterpret_cast<const char*>(&count), sizeof(int));
  for(int i=0; i<256; i++){
    if( v[i] !=0){
       out.write(reinterpret_cast<const char*>(&i), sizeof(char));
       out.write(reinterpret_cast<const char*>(&v[i]), sizeof(int));
    }
  }
 // out.flush();

 // Open inFile to begin reading again
 in.open(inFile, ios::binary);
 BitInputStream bin(in); // reference to BitInputSTream


 while(in.good()){
  symbol= in.get();
  if(!in.good()) break;
  myTree.encode(symbol, bout);
 }

 if( !in.eof()) {
   cerr << "There was a problem reading the file. " << endl; 
   return -1;
 }
 cout << "done." << endl;
 bout.flush();

 // Close files
 in.close(); 
 out.close(); 

/**
 * Reading compressed file and count it! 
 */
 
 // Open compressed file
 ifstream com;
 com.open(outFile, ios::binary);

 // Count number of bytes in compressed file
 while(com.good()){
  com.get();
  if( !com.good()) break;
  csize++;
 }
 
 cout << "Output File has size " << csize << " bytes." << endl;
 
 if( fsize == 0) compressedratio = 0; 
 else
 compressedratio = (double) csize/fsize;  
 
 cout << "Compression ratio: " << compressedratio << endl;

return 0;
};
