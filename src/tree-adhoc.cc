//========================================================================
// tree-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for tree.

#include "Tree.h"
#include "ece2400-stdlib.h"
#include <cstdio>
// template <typename DistFunc>

int main()
{
  Tree<int, IntCmpFuncType> tree( 2, less );

  for ( int v : {20, 74, 5, 6, 100, 300, 1, 9, 15} ) {
    std::printf( "%d\n", v );
    tree.add( v );
  }
  std::printf( "\n" );

  for ( int v : {21, 74, 5, 6, 100, 300, 1, 9, 500} ) {
    std::printf( "%d\n", tree.find_closest( v, distance ) );
  }
  std::printf( "Tree\n" );
  // tree.print();
  // Tree<int, IntCmpFuncType> tree2=tree;
  // std::printf( "Tree2\n" );
  // tree2.print();

  // std::printf( "\n" );

  return 0;
}
