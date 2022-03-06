//========================================================================
// ece2400-stdlib.inl
//========================================================================
// Inline and/or template definitions for ECE 2400 standard library.

#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// less
//------------------------------------------------------------------------
// Return true if a is strictly less than b; false otherwise.

inline bool less( int a, int b )
{
  return a < b;
}

//------------------------------------------------------------------------
// distance
//------------------------------------------------------------------------
// Return the distance between the two given objects.

inline size_t distance( int a, int b )
{
  if ( a > b )
    return a - b;
  else
    return b - a;
}

//------------------------------------------------------------------------
// hash
//------------------------------------------------------------------------
// Return hash value of the given integer

inline size_t hash( int a )
{
  return a;
}
