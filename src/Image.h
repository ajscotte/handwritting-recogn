//========================================================================
// Image.h
//========================================================================
// Declarations for Image.

#ifndef IMAGE_H
#define IMAGE_H

#include "VectorByte.h"
#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include <cstddef>

class Image {
public:
  // Constructors
  inline Image();
  inline Image( const VectorInt& vec, size_t ncols, size_t nrows );

  // Methods
  inline size_t get_ncols() const;
  inline size_t get_nrows() const;
  int           at( size_t x, size_t y ) const;
  inline void   set_label( const char& l );
  inline char   get_label() const;
  int           get_intensity() const;
  void          print() const;

  // Operator overloading
  bool        operator==( const Image& rhs ) const;
  inline bool operator!=( const Image& rhs ) const;

  inline int operator[]( size_t idx ) const;

private:
  VectorByte  m_vector;
  size_t      m_cols;
  size_t      m_rows;
  char        m_label;
  mutable int m_intensity;
};

// Free function that returns the distance between two images
uint_t distance( const Image& a, const Image& b );

#include "Image.inl"

#endif  // IMAGE_H
