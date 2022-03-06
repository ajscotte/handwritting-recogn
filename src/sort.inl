//========================================================================
// sort.inl
//========================================================================
// Definition of generic sort algorithm.
#include "ece2400-stdlib.h"
#include "sort.h"
#include <assert.h>
#include <cstddef>
#include <cstdio>

template <typename T, typename CmpFunc>
void sort( T* a, size_t size, CmpFunc cmp )
{
  // returns if size is zero
  if ( size == 0 ) {
    return;
  }
  // function call to merge sort
  sort_op_h( a, 0, size, size, cmp );

  return;
}

//------------------------------------------------------------------------
// merge
//------------------------------------------------------------------------
// Helper function that merges two sorted arrays.
template <typename T, typename CmpFunc>
void merge( T* dst, T* src0, size_t begin0, size_t end0, size_t size0, T* src1,
            size_t begin1, size_t end1, size_t size1, CmpFunc cmp )
{
  assert( ( end0 - begin0 == size0 ) && ( begin0 <= end0 ) );
  assert( ( end1 - begin1 == size1 ) && ( begin1 <= end1 ) );

  size_t idx0 = begin0;
  size_t idx1 = begin1;
  size_t size = ( ( end0 - begin0 ) + ( end1 - begin1 ) );

  for ( size_t i = 0; i < size; i++ ) {
    // done with array src0:
    // if end0 and idx0 are the same
    if ( end0 == idx0 ) {
      dst[i] = src1[idx1];
      idx1 += 1;
    }
    // Done with array src1:
    // if end1 and idx1 are the same
    else if ( end1 == idx1 ) {
      dst[i] = src0[idx0];
      idx0 += 1;
    }
    // Front of array src0 is less than front of src1:
    // if idx0 is less than idx1
    else if ( cmp( src0[idx0], src1[idx1] ) ) {
      dst[i] = src0[idx0];
      idx0 += 1;
    }
    // Front of array src1 is less than front of src0:
    // if idx1 is less than idx0
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
template <typename T, typename CmpFunc>
void sort_op_h( T* a, size_t begin, size_t end, size_t size, CmpFunc cmp )
{
  assert( ( end - begin ) == size );
  // ECE2400_DEBUG( "msort_op_h(%lu, %lu)", begin, end );
  size_t mid   = ( begin + end ) / 2;
  size_t size1 = mid - begin;
  size_t size2 = end - mid;
  // base case when size is zero or one array is sorted
  if ( size == 1 || size == 0 ) {
    return;
  }
  // recursive calls to split up array
  sort_op_h( a, begin, mid, size1, cmp );
  sort_op_h( a, mid, end, size2, cmp );
  // merging operation
  T* tempArray = new T[size];
  merge( tempArray, a, begin, mid, size1, a, mid, end, size2, cmp );
  // adds everything back to original array but sorted
  size_t j = 0;
  for ( size_t i = begin; i < end; i++ ) {
    a[i] = tempArray[j];
    j += 1;
  }
  delete[]( tempArray );
}
