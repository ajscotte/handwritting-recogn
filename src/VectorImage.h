//========================================================================
// VectorImage.h
//========================================================================
// Declarations for VectorImage.

#ifndef VECTOR_IMAGE_H
#define VECTOR_IMAGE_H

#include "Image.h"
#include <cstddef>

class VectorImage {
public:
  inline VectorImage();
  inline ~VectorImage();

  // Copy constructor
  VectorImage( const VectorImage& vec );
  VectorImage( Image* data, size_t size );

  // Methods
  inline size_t size() const;
  void          push_back( const Image& img );
  inline Image  at( size_t idx ) const;
  bool          contains( const Image& img ) const;
  Image         find_closest( const Image& img ) const;
  inline void   sort();
  void          print() const;

  // Operator overloading
  inline const Image& operator[]( size_t idx ) const;
  VectorImage&        operator=( const VectorImage& vec );

private:
  Image* m_data;
  size_t m_sizeArray;
  size_t m_maxSize;
};

#include "VectorImage.inl"

#endif  // VECTOR_IMAGE_H
