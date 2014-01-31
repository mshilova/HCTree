#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

/**
 * cse100, P3 - HCTree implementation file
 */ 

//helper function for the destructor
void HCTree::postOrderDes(HCNode* p) {
  if(p!=NULL)  {
    postOrderDes(p->c0);
    postOrderDes(p->c1);
    p->c0=NULL;
    delete p;
    p=NULL;
  }
} 

// destructor
HCTree::~HCTree()  {
  HCTree::postOrderDes(root);
  root=NULL;
}


/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs)  {
  // use priority_queue, insert nodes into it, ranking by frequency
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
  for(int i=0; i<leaves.size(); i++)  {
    if(freqs[i]!=0)  {
      leaves[i] = new HCNode(freqs[i], (char)i, 0,0,0);
      // push nodes int the priority queue
      pq.push(leaves[i]);
    }
  }
  // build tree using huff alg
  // i.e. take two nodes out of the queue, combine them into a node, put it 
  while(pq.size() > 1)  {
  // create a new node where the left child is the lowest in the sorted 
  // list and the right is the second lowest in the sorted list
    HCNode* left = pq.top();
    pq.pop();
    HCNode* right = pq.top();
    pq.pop();

    int fr = left->count + right->count;
    HCNode* node = new HCNode(fr, 0, left, right,0);
    left->p = node;
    right->p = node;

    pq.push(node);
  }
  root= pq.top();
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const  {
 // Create a node point to leaf denoting desired symbol
  HCNode* curr = leaves[symbol];

  // Create a stack to keep track of 0's and 1's
  stack<int> code;
  //std::cout << ""<<std::endl;
  //std::cout << "In encode: Symbol: " << symbol << " " ;
  // While we are not at root keep progressing up the tree
  while (curr->p != NULL){
  // Push in a 0 is curr is a left child
  // Push in a 1 is curr is a right child
  // If it is neither then we have a problem..... 
    if((curr->p)->c0 == curr)  {
        code.push(0);
    }
    else if((curr->p)->c1 == curr)  {
       code.push(1);
    }
    else{
      std::cerr << " Problem with pointers in tree " << std::endl;
    }
    curr = curr->p;
  }
 // Write out the topmost element
 // Then pop it from the stack
 // We have finished writing out code once stack is empty
  int sizeStack = code.size();
  while (!code.empty()){
    out.writeBit(code.top());
    code.pop();
  }
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const  {
   
   // Start at the root of the tree
  HCNode* curr = root;
  int bit;

  // While you have two childern keep going down the tree
  // Huffman tree nodes either have 0 or 2 childern 
  // If they have 0 childern then they are a leaf node and
  // thus contain a nonzero symbol. 
  while(curr->c0 != NULL && curr->c1 != NULL){
    bit = in.readBit();
    // If bit is 0 go to the left
    // If bit is 1 go to the right
    // If bit is something else ERROR
    if(bit == 0) {
      curr = curr->c0;
    }
    else if (bit == 1 )  {
      curr = curr->c1;
    }
    else{
      std::cerr << "ERROR: Readbit returning a non 0 or 1 value " << std::endl;
      return -1;
      }
  }
  // return the symbol
  return curr->symbol;
}

