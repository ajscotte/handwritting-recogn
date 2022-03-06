//========================================================================
// VectorByte.cc
//========================================================================
// Implementation of VectorByte.

#include "VectorByte.h"
#include "ece2400-stdlib.h"
#include "limits.h"
#include "sort-image.h"
#include <assert.h>

//------------------------------------------------------------------------
// VectorByte::VectorByte
//------------------------------------------------------------------------
// non default constructor that copies input parameters
VectorByte::VectorByte( int* array, size_t size )
{
  // creates space on the heap and then stores values based on the input array
  m_data = new unsigned char[size];
  for ( size_t i = 0; i < size; i++ ) {
    m_data[i] = array[i];
  }
  // initializes private member fields
  m_sizeArray = size;
  m_maxsize   = size;
}

//------------------------------------------------------------------------
// VectorByte::VectorByte
//------------------------------------------------------------------------
// Copy constructor that takes a current vectorByte and copys the values into a
// new vectorByte
VectorByte::VectorByte( const VectorByte& vec )
{
  // sets vectorInt to nullptr if size is zero
  if ( vec.m_sizeArray == 0 ) {
    m_data = nullptr;
  }
  // when size is greater than zero
  else {
    // copies data from the vectorByte parameter into new array
    m_data = new unsigned char[vec.m_sizeArray];
    for ( size_t i = 0; i < vec.m_sizeArray; i++ ) {
      m_data[i] = vec.m_data[i];
    }
  }
  // initializes private member variables based on input vector
  m_sizeArray = vec.m_sizeArray;
  m_maxsize   = vec.m_sizeArray;
}

//------------------------------------------------------------------------
// VectorByte::operator=
//------------------------------------------------------------------------
// overloads the = operator to copy the values from
// one vector to another when set equal to each other for vectorByte
VectorByte& VectorByte::operator=( const VectorByte& vec )
{
  //ECE2400_DEBUG( "VectorByte::operator= called!" );
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
      m_data      = new unsigned char[vec.m_maxsize];
      m_maxsize   = vec.m_maxsize;
      for ( size_t i = 0; i < m_sizeArray; i++ ) {
        m_data[i] = vec[i];
      }
    }
  }
  // returns vector with new values
  return *this;
}

//------------------------------------------------------------------------
// VectorByte::pushback
//------------------------------------------------------------------------
// pushback_v2 function that adds values to the vector
void VectorByte::push_back( unsigned char value )
{
  assert( this != nullptr );
  //ECE2400_DEBUG( "vector_int_push_back_v2(%p, %d) called!", this, value );
  // case for when the array is empty
  if ( m_maxsize == 0 ) {
    //ECE2400_DEBUG( "Checking m_maxsize == 0" );
    m_maxsize = m_maxsize + 1;
    m_data    = new unsigned char[1];
    m_data[0] = value;
    m_sizeArray += 1;
  }
  // case for when the array is full
  else if ( ( m_sizeArray ) == ( m_maxsize ) ) {
    //ECE2400_DEBUG( "Checking m_maxsize == size" );
    // create a temporary array to hold the current values
    unsigned char* newVec = new unsigned char[m_maxsize * 2];
    for ( unsigned int i = 0; i < this->m_maxsize; i++ ) {
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
  // case for when the size of the array is still smaller than m_maxsize
  else {
    //ECE2400_DEBUG( "Checking m_maxsize != size" );
    m_data[m_sizeArray] = value;
    m_sizeArray         = m_sizeArray + 1;
  }
}

//------------------------------------------------------------------------
// VectorByte::contains
//------------------------------------------------------------------------
// returns boolean values depending on whether the vector contains a specific
// value
bool VectorByte::contains( int value ) const
{
  assert( this != nullptr );
  //ECE2400_DEBUG( "vector_int_contains(%p, %d) called!", this, value );
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
// VectorByte::find_closest
//------------------------------------------------------------------------
// finds the value in the vector closest to the input value
int VectorByte::find_closest( int value ) const
{
  //ECE2400_DEBUG( "vector_int_find_closest(%p, %d) called!", this, value );
  // case when vector m_data size is zero
  if ( m_sizeArray == 0 ) {
    throw ece2400::OutOfRange( "Empty array, index out of bounds" );
  }

  uint_t difference = distance( m_data[0], value );
  int    answer     = m_data[0];
  // iterates over vector to compare value with current input values
  for ( size_t i = 0; i < m_sizeArray; i++ ) {
    uint_t compare = distance( m_data[i], value );
    if ( difference > compare ) {
      difference = compare;
      answer     = m_data[i];
    }
  }
  return answer;
}

//------------------------------------------------------------------------
// VectorByte::print
//------------------------------------------------------------------------
// prints the vector's values
void VectorByte::print() const
{
  assert( this != nullptr );
  for ( size_t i = 0; i < m_sizeArray; i++ ) {
    printf( "Element %lu has the value: %d\n", i, this->m_data[i] );
  }
}

//------------------------------------------------------------------------
// VectorByte::operator=
//------------------------------------------------------------------------
// overloads the = operator to copy the values from
// one vector to another when set equal to each other for a vectorByte =
// VectorInt
VectorByte& VectorByte::operator=( const VectorInt& vec )
{
  // checks to see if the vector is the same vector
  //ECE2400_DEBUG( "VectorByte::operator= called!" );
  // deletes current data in order to be replaced
  delete[] m_data;
  // if there isn't any room in the vector being copied,
  // initialize the vector to default constructor values
  if ( vec.size() == 0 ) {
    m_sizeArray = 0;
    m_data      = nullptr;
    m_maxsize   = 0;
  }
  // if the size of the parameter vector is non-zero
  else {
    // set the member variables of the new vector to match the parameter vector
    m_sizeArray = vec.size();
    // type conversion
    m_data    = new unsigned char[vec.size()];
    m_maxsize = vec.size();
    for ( size_t i = 0; i < m_sizeArray; i++ ) {
      m_data[i] = (unsigned char) vec[i];
    }
  }
  // returns vector with new values
  return *this;
}