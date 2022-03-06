//========================================================================
// HRSTableSearch.cc
//========================================================================
// Definitions for HRSTableSearch

#include "HRSTableSearch.h"
#include "Image.h"
#include "Table.h"
#include "Vector.h"


//------------------------------------------------------------------
// HRSTableSearch
//------------------------------------------------------------------
// constructor
HRSTableSearch::HRSTableSearch( unsigned int K )
    : m_table( 1, Image(), Image(), hash_intensity )
{
  // defines private variables
  m_k = K;
}


//------------------------------------------------------------------
// HRSTableSearch:train
//------------------------------------------------------------------
// adds known values to a table for reference
void HRSTableSearch::train( const Vector<Image>& vec )
{
  // values to be used throughout the function
  size_t idx_min       = 0;
  size_t idx_max       = 0;
  size_t size          = vec.size();
  size_t min_intensity = hash_intensity( vec[0] );
  size_t max_intensity = min_intensity;
  size_t compare;
  // searches for index of smallest and largest intensity
  for ( size_t i = 1; i < size; i++ ) {
    compare = hash_intensity( vec[i] );
    if ( min_intensity > compare ) {
      idx_min       = i;
      min_intensity = compare;
    }
    if ( max_intensity < compare ) {
      idx_max       = i;
      max_intensity = compare;
    }
  }
  // creates bin_size
  unsigned int bin_size = 1;
  if ( m_k < size ) {
    bin_size = size / m_k;
  }
  // makes table
  m_table = Table<Image, ImgHashFuncType>( bin_size, vec[idx_min], vec[idx_max],
                                           hash_intensity );
  for ( size_t i = 0; i < size; i++ ) {
    m_table.add( vec[i] );
  }
}


//------------------------------------------------------------------
// HRSTableSearch::classify
//------------------------------------------------------------------
// searchers for closest image to match value
Image HRSTableSearch::classify( const Image& Image )
{
  // calls find closest function in table class
  return m_table.find_closest( Image, distance_euclidean );
}