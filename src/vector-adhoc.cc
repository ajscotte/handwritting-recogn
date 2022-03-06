//========================================================================
// vector-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for vector.

#include "Vector.h"
#include <cstdio>

int main()
{
  Vector<int> vec;
  vec.push_back( 19 );
  vec.push_back( 95 );
  vec.push_back( 4 );
  vec.push_back( 23 );

  std::printf( "Value stored at index 0 is %d\n", vec.at( 0 ) );
  std::printf( "Value stored at index 1 is %d\n", vec.at( 1 ) );
  std::printf( "Value stored at index 2 is %d\n", vec.at( 2 ) );
  std::printf( "Value stored at index 3 is %d\n", vec.at( 3 ) );

  return 0;
}
