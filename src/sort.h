//========================================================================
// sort.h
//========================================================================
// Declarations for generic sort algorithm.

#ifndef SORT_H
#define SORT_H

#include <cstddef>

// Cmp is a function object type. cmp should return true when arg1 is
// strictly less than arg2, and false otherwise.
template <typename T, typename CmpFunc>
inline void sort( T* a, size_t size, CmpFunc cmp );

template <typename T, typename CmpFunc>
void merge( T* dst, T* src0, size_t begin0, size_t end0, size_t size0, T* src1,
            size_t begin1, size_t end1, size_t size1, CmpFunc cmp );

template <typename T, typename CmpFunc>
void sort_op_h( T* a, size_t begin, size_t end, size_t size, CmpFunc cmp );

// Include inline definitions
#include "sort.inl"

#endif  // SORT_H
