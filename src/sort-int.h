//========================================================================
// sort-int.h
//========================================================================

#ifndef SORT_INT_H
#define SORT_INT_H

#include <cstddef>

void sort_int( int* a, size_t size );

void merge( int* dst, int* src0, size_t begin0, size_t end0, size_t size0,
            int* src1, size_t begin1, size_t end1, size_t size1 );

void msort_op_h( int* a, size_t begin, size_t end, size_t size );

#endif  // SORT_INT_H
