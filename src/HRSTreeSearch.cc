//========================================================================
// HRSTreeSearch.cc
//========================================================================
// Definitions for HRSTreeSearch

#include "HRSTreeSearch.h"
#include "Image.h"
#include "Tree.h"
#include "Vector.h"
//------------------------------------------------------------------
// HRSTreeSearch
//------------------------------------------------------------------
// constructor
HRSTreeSearch::HRSTreeSearch( unsigned int K ) : m_tree( K, less_intensity )
{
  m_k = K;
}

//------------------------------------------------------------------
// HRSTreeSearch::train
//------------------------------------------------------------------
// adds values to tree for reference
void HRSTreeSearch::train( const Vector<Image>& vec )
{
  // adds value to tree
  for ( size_t i = 0; i < vec.size(); i++ ) {
    m_tree.add( vec[i] );
  }
}

//------------------------------------------------------------------
// HRSTreeSearch::classify
//------------------------------------------------------------------
// finds closest value to image
Image HRSTreeSearch::classify( const Image& img )
{
  // calls tree find closest function
  return m_tree.find_closest( img, distance_euclidean );
}