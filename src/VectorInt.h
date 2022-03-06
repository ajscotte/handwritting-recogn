//========================================================================
// VectorInt.h
//========================================================================
// Declarations for VectorInt.

#ifndef VECTOR_INT_H
#define VECTOR_INT_H

#include <cstddef>

class VectorInt {
public:
  inline VectorInt();
  inline ~VectorInt();

  // Copy constructor
  VectorInt( const VectorInt& vec );

  // Construct from an array
  VectorInt( int* array, size_t size );

  // Methods
  inline size_t size() const;
  void          push_back( int value );
  inline int    at( size_t idx ) const;
  bool          contains( int value ) const;
  int           find_closest( int value ) const;
  inline void   sort();
  void          print() const;

  // Operator overloading
  inline int operator[]( size_t idx ) const;
  VectorInt& operator=( const VectorInt& vec );

private:
  int*   data;
  size_t sizeArray;
  size_t maxsize;
};

#include "VectorInt.inl"

#endif  // VECTOR_INT_H
