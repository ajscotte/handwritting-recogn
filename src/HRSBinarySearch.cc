//========================================================================
// HRSBinarySearch.cc
//========================================================================
// Handwritten recognition system that uses linear search.

#include "HRSBinarySearch.h"
#include "IHandwritingRecSys.h"
#include "Image.h"
#include "VectorImage.h"
#include <cstddef>
#define K 100
//------------------------------------------------------------------------
// Search
//------------------------------------------------------------------------
// Linear search part for BinarySearch
// seaches K/2 indexes forward and backwards
// from the midpoint selected in the vector
const Image& Search( const Image& img, const VectorImage& vec, size_t begin,
                     size_t end )
{
  uint_t difference = distance( vec[0], img );
  int    begin1     = begin;
  int    end1       = end;
  int    idx        = 0;

  // iterates over vector from a midpoint in two directions to find the closest
  // Image to img
  for ( int i = begin; i < begin1 + ( K / 2 ); i++ ) {
    // forward iteration from midpoint that checks to see index is still
    // reachable
    if ( i < end1 ) {
      // compares to see if current image is closer to img than the last image
      uint_t compare1 = distance( vec[i], img );
      // replaces index of closest value when new value is found
      if ( difference > compare1 ) {
        difference = compare1;
        idx        = i;
      }
    }
    // backward iteration from midpoint that checks to see index is still
    // reachable
    if ( ( 2 * begin1 - i ) >= 0 ) {
      // compares to see if current image is closer to img than the last image
      uint_t compare2 = distance( vec[2 * begin1 - i], img );
      // replaces index of closest value when new value is found
      if ( difference > compare2 ) {
        difference = compare2;
        idx        = ( 2 * begin1 - i );
      }
    }
  }
  // returns appropriate value
  return vec[idx];
}
//------------------------------------------------------------------------
// binarySearch_h
//------------------------------------------------------------------------
// binary search helper function that carries out the recursive search
const Image& binarySearch_h( const Image& image, const VectorImage& vec,
                             size_t begin, size_t end,
                             const size_t absoluteEnd )
{
  size_t mid = ( ( end - begin ) / 2 ) + begin;
  // base case when size is zero or 1
  if ( ( end - begin ) == 1 || ( end - begin ) == 0 ) {
    return Search( image, vec, begin, absoluteEnd );
  }

  // gets the intensity values for comparison for the image
  // being compared and in the image vector
  int intensity    = image.get_intensity();
  int intensityMid = vec[mid].get_intensity();

  // if the midpoint intensity is less than  or equal to the
  // image intensity search the upper partition of the sorted ImageVector
  // based on the midpoint
  if ( intensityMid <= intensity ) {
    return binarySearch_h( image, vec, mid, end, absoluteEnd );
  }

  // otherwise search the bottom part of the partition based on the midpoint
  else {
    return binarySearch_h( image, vec, begin, mid, absoluteEnd );
  }
}

//------------------------------------------------------------------------
// HRSBinarySearch::HRSBinarySearch()
//------------------------------------------------------------------------
// Default constructor for HRSBinarySearch.
HRSBinarySearch::HRSBinarySearch()
{
  // private member variable already constructed based on its own class
}
//------------------------------------------------------------------------
// HRSBinarySearch::train
//------------------------------------------------------------------------
// Train the HRS. For HRSBinarySearch, stores a copy of the vector
// that contains the training images (vec), and then sorts the training images
// based on intensity.
void HRSBinarySearch::train( const VectorImage& vec )
{
  // uses operator = overload to stor vec values in private member variable
  m_Bvector = vec;
  // sorts the vector based off image intensity to be used in binary search
  m_Bvector.sort();
}
//------------------------------------------------------------------------
// HRSBinarySearch::classify
//------------------------------------------------------------------------
// Calls the binarySearch helper function to allow for binary search
// based on initial input parameters
Image HRSBinarySearch::classify( const Image& Image )
{
  // calls the binarySearch_h helper function
  return binarySearch_h( Image, m_Bvector, 0, m_Bvector.size(),
                         m_Bvector.size() );
}
