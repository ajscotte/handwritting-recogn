//========================================================================
// sort-image.h
//========================================================================

#ifndef SORT_IMAGE_H
#define SORT_IMAGE_H

#include "Image.h"
#include "ece2400-stdlib.h"
#include <assert.h>
#include <cstddef>
#include <cstdio>

void sort_image( Image* a, size_t size );
void merge( Image* dst, Image* src0, size_t begin0, size_t end0, size_t size0,
            Image* src1, size_t begin1, size_t end1, size_t size1 );

void msort_op_h( Image* a, size_t begin, size_t end, size_t size );

#endif  // SORT_IMAGE_H
