//========================================================================
// sort-image.cc
//========================================================================
// Implementation of the sort-image function

#include "sort-image.h"

void sort_image( Image* a, size_t size )
{
  // returns if size is zero
  if ( size == 0 ) {
    return;
  }
  // calls merge sort
  msort_op_h( a, 0, size, size );

  return;
}

//------------------------------------------------------------------------
// merge
//------------------------------------------------------------------------
// Helper function that merges two sorted arrays.

void merge( Image* dst, Image* src0, size_t begin0, size_t end0, size_t size0,
            Image* src1, size_t begin1, size_t end1, size_t size1 )
{
  assert( ( end0 - begin0 == size0 ) && ( begin0 <= end0 ) );
  assert( ( end1 - begin1 == size1 ) && ( begin1 <= end1 ) );

  size_t idx0 = begin0;
  size_t idx1 = begin1;
  size_t size = ( ( end0 - begin0 ) + ( end1 - begin1 ) );

  for ( size_t i = 0; i < size; i++ ) {
    // done with array src0:
    if ( idx0 == end0 ) {
      dst[i] = src1[idx1];
      idx1 += 1;
    }
    // Done with array src1:
    else if ( idx1 == end1 ) {
      dst[i] = src0[idx0];
      idx0 += 1;
    }
    // Front of array src0 is less than front of src1:
    else if ( src0[idx0].get_intensity() < src1[idx1].get_intensity() ) {
      dst[i] = src0[idx0];
      idx0 += 1;
    }
    // Front of array src1 is less than front of src0:
    else {
      dst[i] = src1[idx1];
      idx1 += 1;
    }
  }
}

//------------------------------------------------------------------------
// msort_op_h
//------------------------------------------------------------------------
// helper function for msort
void msort_op_h( Image* a, size_t begin, size_t end, size_t size )
{
  assert( ( end - begin ) == size );
  //ECE2400_DEBUG( "msort_op_h(%lu, %lu)", begin, end );
  size_t mid   = ( begin + end ) / 2;
  size_t size1 = mid - begin;
  size_t size2 = end - mid;
  // base case for function since array is sorted when size is one or zero
  if ( size == 1 || size == 0 ) {
    return;
  }
  // recursive statements that divide array
  msort_op_h( a, begin, mid, size1 );
  msort_op_h( a, mid, end, size2 );

  // merge operation that puts arrays back together
  Image* tempArray = new Image[size];
  merge( tempArray, a, begin, mid, size1, a, mid, end, size2 );

  // adds sorted array back to original
  size_t j = 0;
  for ( size_t i = begin; i < end; i++ ) {
    a[i] = tempArray[j];
    j += 1;
  }
  delete[]( tempArray );
}
