//========================================================================
// Vector.inl
//========================================================================
// Implementation of Vector.

#include "ece2400-stdlib.h"
#include "sort.h"
#include <iostream>
#include <thread>


//------------------------------------------------------------------------
// Vector::Vector
//------------------------------------------------------------------------
// default Construct for vector that initialized private member fields
template <typename T>
inline Vector<T>::Vector()
{
  // assigns data to a nullptr, and sets maxsize = size = 0
  m_data      = nullptr;
  m_maxsize   = 0;
  m_sizeArray = 0;
}

//------------------------------------------------------------------------
// Vector::~Vector
//------------------------------------------------------------------------
// Destructor for vector that deletes all data from the heap
template <typename T>
inline Vector<T>::~Vector()
{
  // deletes the data in the vector
  delete[] m_data;
}

//------------------------------------------------------------------------
// Vector::Vector
//------------------------------------------------------------------------
// non default constructor that copies input parameters
template <typename T>
Vector<T>::Vector( T* array, size_t size )
{
  // creates space on the heap and then stores values based on the input array
  m_data = new T[size];
  for ( size_t i = 0; i < size; i++ ) {
    m_data[i] = array[i];
  }
  // initializes private member fields
  m_sizeArray = size;
  m_maxsize   = size;
}

//------------------------------------------------------------------------
// Vector::Vector
//------------------------------------------------------------------------
// Copy constructor that takes a current Vector and copys the values into a
// new Vector
template <typename T>
Vector<T>::Vector( const Vector& vec )
{
  // sets Vector to nullptr if size is zero
  if ( vec.m_sizeArray == 0 ) {
    m_data = nullptr;
  }
  // when size is greater than zero
  else {
    // copies data from the Vector parameter into new array
    m_data = new T[vec.m_sizeArray];
    for ( size_t i = 0; i < vec.m_sizeArray; i++ ) {
      m_data[i] = vec.m_data[i];
    }
  }
  // initializes private member variables based on input vector
  m_sizeArray = vec.m_sizeArray;
  m_maxsize   = vec.m_sizeArray;
}

//------------------------------------------------------------------------
// Vector::operator=
//------------------------------------------------------------------------
// overloads the = operator to copy the values from
// one vector to another when set equal to each other
template <typename T>
Vector<T>& Vector<T>::operator=( const Vector<T>& vec )
{
  // checks to see if the vector is the same vector
  if ( this != &vec ) {
    // deletes current data in order to be replaced
    delete[] m_data;
    // if there isn't any room in the vector being copied,
    // initialize the vector to default constructor values
    if ( vec.m_maxsize == 0 ) {
      m_sizeArray = 0;
      m_data      = nullptr;
      m_maxsize   = 0;
    }
    // if the size of the parameter vector is non-zero
    else {
      // set the member variables of the new vector to match the parameter
      // vector
      m_sizeArray = vec.m_sizeArray;
      m_data      = new T[vec.m_maxsize];
      m_maxsize   = vec.m_maxsize;
      for ( size_t i = 0; i < m_sizeArray; i++ ) {
        m_data[i] = vec.m_data[i];
      }
    }
  }
  // returns vector with new values
  return *this;
}

//------------------------------------------------------------------------
// Vector::size()
//------------------------------------------------------------------------
// Returns size of the current Vector
template <typename T>
inline size_t Vector<T>::size() const
{
  // returns private member field that holds the size of the vector
  return m_sizeArray;
}

//------------------------------------------------------------------------
// Vector::pushback
//------------------------------------------------------------------------
// pushback_v2 function that adds values to the vector
template <typename T>
void Vector<T>::push_back( const T& value )
{
  if ( m_maxsize == 0 ) {
    m_maxsize = m_maxsize + 1;
    m_data    = new T[1];
    m_data[0] = value;
    m_sizeArray += 1;
  }
  // case for when the array is full
  else if ( ( m_sizeArray ) == ( m_maxsize ) ) {
    // create a temporary array to hold the current values
    T* newVec = new T[m_maxsize * 2];
    for ( size_t i = 0; i < this->m_maxsize; i++ ) {
      newVec[i] = m_data[i];
    }
    // add new value
    newVec[m_maxsize] = value;
    // delete data array from heap
    delete[] m_data;
    // update member variables with new values
    m_data      = newVec;
    m_sizeArray = m_sizeArray + 1;
    m_maxsize   = m_maxsize * 2;
  }
  // case for when the size of the array is still smaller than maxsize
  else {
    m_data[m_sizeArray] = value;
    m_sizeArray         = m_sizeArray + 1;
  }
}

//------------------------------------------------------------------------
// Vector::at()
//------------------------------------------------------------------------
// Returns the value at the specified index if in the bound of the vector
template <typename T>
const T& Vector<T>::at( size_t idx ) const
{
  if ( idx < m_sizeArray ) {
    // returns value at specific index
    return m_data[idx];
  }
  else {
    // returns an exceptions when idex out of bounds
    throw ece2400::OutOfRange( "Index out of bounds" );
  }
}

//------------------------------------------------------------------------
// Vector::at()
//------------------------------------------------------------------------
// Returns the value at the specified index if in the bound of the vector
template <typename T>
T& Vector<T>::at( size_t idx )
{
  if ( idx < m_sizeArray ) {
    // returns value at specific index
    return m_data[idx];
  }
  else {
    // returns an exceptions when idex out of bounds
    throw ece2400::OutOfRange( "Index out of bounds" );
  }
}

//------------------------------------------------------------------------
// Vector::contains
//------------------------------------------------------------------------
// returns boolean values depending on whether the vector contains a specific
// value
template <typename T>
bool Vector<T>::contains( const T& value ) const
{
  // Searching the vector to find if the value is in the loop, returning true if
  // found returns false is the vector does not contain the value
  for ( size_t i = 0; i < m_sizeArray; i++ ) {
    if ( m_data[i] == value ) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------
// Vector::find_closest
//------------------------------------------------------------------------
// finds the value in the vector closest to the input value
template <typename T>
template <typename DistFunc>
const T& Vector<T>::find_closest( const T& value, DistFunc dist ) const
{
  // case when vector data size is zero
  if ( m_sizeArray == 0 ) {
    throw ece2400::OutOfRange( "Empty array, index out of bounds" );
  }

  size_t difference = dist( m_data[0], value );
  size_t idx        = 0;
  // iterates over vector to compare value with current input values
  for ( size_t i = 0; i < m_sizeArray; i++ ) {
    size_t compare = dist( m_data[i], value );
    if ( difference > compare ) {
      difference = compare;
      idx        = i;
    }
  }
  return m_data[idx];
}

//------------------------------------------------------------------------
// Vector::find_closest_alternative
//------------------------------------------------------------------------
// finds the value in the vector closest to the input value, used with threads
// to split up the linear search in our HRS Alternative Search
template <typename T>
template <typename DistFunc>
T Vector<T>::find_closest_alternative( const T& value, DistFunc dist,
                                       size_t begin, size_t end ) const
{
  size_t difference = dist( m_data[begin], value );
  size_t idx        = begin;
  // iterates over vector to compare value with current input values
  for ( size_t i = begin; i < end; i++ ) {
    size_t compare = dist( m_data[i], value );
    if ( difference > compare ) {
      difference = compare;
      idx        = i;
    }
  }
  return m_data[idx];
}

//------------------------------------------------------------------------
// Vector::sort()
//------------------------------------------------------------------------
// sorts the vector based on the sorting algorithm in sort-int class
template <typename T>
template <typename CmpFunc>
void Vector<T>::sort( CmpFunc cmp )
{
  // function call to sort_int function in sort-int.cc
  ::sort( m_data, m_sizeArray, cmp );
}

//------------------------------------------------------------------------
// Vector::print
//------------------------------------------------------------------------
// prints the vector's values
// void Vector::print() const
// {
//   assert( this != nullptr );
//   for ( size_t i = 0; i < sizeArray; i++ ) {
//     printf( "Element %lu has the value: %d\n", i, this->data[i] );
//   }
// }

//------------------------------------------------------------------------
// Vector::operator[]
//------------------------------------------------------------------------
// overloads the [] operator to return an value at the specifed index(read only)
template <typename T>
inline const T& Vector<T>::operator[]( size_t idx ) const
{
  // returns the value in the data array at the specified index
  return m_data[idx];
}

//------------------------------------------------------------------------
// Vector::operator[]
//------------------------------------------------------------------------
// overloads the [] operator to return an value at the specifed index(cam write)
template <typename T>
inline T& Vector<T>::operator[]( size_t idx )
{
  // returns the value in the data array at the specified index
  return m_data[idx];
}
