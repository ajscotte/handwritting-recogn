//========================================================================
// VectorByte.h
//========================================================================
// Declarations for VectorByte.

#ifndef VECTOR_BYTE_H
#define VECTOR_BYTE_H

#include "VectorInt.h"
#include <cstddef>

class VectorByte {
public:
  inline VectorByte();
  inline ~VectorByte();

  // Copy constructor
  VectorByte( const VectorByte& vec );

  // Construct from an array
  VectorByte( int* array, size_t size );

  // Methods
  inline size_t        size() const;
  void                 push_back( unsigned char value );
  inline unsigned char at( size_t idx ) const;
  bool                 contains( int value ) const;
  int                  find_closest( int value ) const;
  void                 sort();
  void                 print() const;

  // Operator overloading
  inline unsigned char operator[]( size_t idx ) const;
  VectorByte&          operator=( const VectorByte& vec );
  VectorByte&          operator=( const VectorInt& vec );

private:
  unsigned char* m_data;
  size_t         m_sizeArray;
  size_t         m_maxsize;
};

#include "VectorByte.inl"

#endif  // VECTOR_INT_H
