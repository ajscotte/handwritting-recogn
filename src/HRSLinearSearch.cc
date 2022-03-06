//========================================================================
// HRSLinearSearch.cc
//========================================================================
// Handwritten recognition system that uses linear search.

#include "HRSLinearSearch.h"
#include "Image.h"
#include "VectorImage.h"
//------------------------------------------------------------------------
// HRSLinearSearch::HRSLinearSearch
//------------------------------------------------------------------------
// Default constructor for HRSLinearSearch.
HRSLinearSearch::HRSLinearSearch()
{
  // private member variable already initialized by its own class
}

//------------------------------------------------------------------------
// HRSLinearSearch::train
//------------------------------------------------------------------------
// Train the HRS. For HRSLinearSearch
void HRSLinearSearch::train( const VectorImage& vec )
{
  // uses operator = overload to copy data from vec
  m_Ivector = vec;
}
//------------------------------------------------------------------------
// HRSLinearSearch::classify
//------------------------------------------------------------------------
// Classify the given image. This function searchs through the entire
// training set and return the image that has the smallest euclidean distance
// from the given image.
Image HRSLinearSearch::classify( const Image& img )
{
  // calls find_closest to do a linear search
  return m_Ivector.find_closest( img );
}