//========================================================================
// Image.h
//========================================================================
// Declarations for Image.

#ifndef IMAGE_H
#define IMAGE_H

#include "Vector.h"
#include "ece2400-stdlib.h"

#include <cstddef>
#include <functional>
#include <iostream>

class Image {
 public:
  // Constructors
  inline Image();
  Image( const Vector<int>& vec, size_t ncols, size_t nrows );

  // Methods
  inline size_t get_ncols() const;
  inline size_t get_nrows() const;
  int           at( size_t x, size_t y ) const;
  inline void   set_label( char l );
  inline char   get_label() const;
  int           get_intensity() const;
  void          print() const;

  // Operator overloading
  bool operator==( const Image& rhs ) const;
  bool operator!=( const Image& rhs ) const;

  inline int operator[]( size_t idx ) const;

  friend std::ostream& operator<<( std::ostream& output, const Image& image );

 private:
  Vector<unsigned char> m_vector;
  size_t                m_cols;
  size_t                m_rows;
  char                  m_label;
  mutable int           m_intensity;
};

// Define aliases for image free function types
typedef bool ( *ImgCmpFuncType )( const Image&, const Image& );
typedef size_t ( *ImgDistFuncType )( const Image&, const Image& );
typedef size_t ( *ImgHashFuncType )( const Image& );

// Declare image free functions
bool   less_intensity( const Image& a, const Image& b );
size_t distance_euclidean( const Image& a, const Image& b );
size_t hash_intensity( const Image& a );

// Include inline definitions
#include "Image.inl"

#endif  // IMAGE_H
