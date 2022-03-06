//========================================================================
// vector-int-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for VectorInt.

#include "VectorInt.h"
#include <stdio.h>

int main()
{
  VectorInt vec;
  vec.push_back( 19 );
  vec.push_back( 95 );
  vec.push_back( 4 );
  vec.push_back( 23 );

  printf( "Value stored at index 0 is %d\n", vec.at( 0 ) );
  printf( "Value stored at index 1 is %d\n", vec.at( 1 ) );
  printf( "Value stored at index 2 is %d\n", vec.at( 2 ) );
  printf( "Value stored at index 3 is %d\n", vec.at( 3 ) );

  return 0;
}
