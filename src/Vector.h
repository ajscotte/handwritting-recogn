//========================================================================
// Vector.h
//========================================================================
// Declarations for Vector.

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename T>
class Vector {
 public:
  inline Vector();
  inline ~Vector();

  // Copy constructor
  Vector( const Vector<T>& vec );

  // Construct from an array
  Vector( T* array, size_t size );

  // Methods
  inline size_t size() const;
  void          push_back( const T& value );
  const T&      at( size_t idx ) const;
  T&            at( size_t idx );
  bool          contains( const T& value ) const;

  // clang-format off
  template <typename DistFunc>
  const T& find_closest( const T& value, DistFunc dist ) const;

  template <typename DistFunc>
  T find_closest_alternative( const T& value, DistFunc dist, size_t begin, size_t end) const;

  template <typename CmpFunc>
  void sort( CmpFunc cmp );
  // clang-format on

  void print() const;

  // Operator overloading
  inline const T&   operator[]( size_t idx ) const;
  inline T&         operator[]( size_t idx );
  inline Vector<T>& operator=( const Vector<T>& vec );
  // Vector<T>& operator=( const Vector<int>& vec );

 private:
  T*     m_data;
  size_t m_sizeArray;
  size_t m_maxsize;
};

// Include inline definitions
#include "Vector.inl"

#endif  // VECTOR_H
