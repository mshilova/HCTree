#include <iostream>
#include "HCNode.hpp"

/* CS100 P3 - Implements the comparison operator 
 */

  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool HCNode::operator<(const HCNode& other) {
    return count > other.count;    
  }

