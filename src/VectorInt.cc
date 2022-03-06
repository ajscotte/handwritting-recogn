//========================================================================
// VectorInt.cc
//========================================================================
// Implementation of VectorInt.

#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include "limits.h"
#include "sort-int.h"
#include <assert.h>

//------------------------------------------------------------------------
// VectorInt::VectorInt
//------------------------------------------------------------------------
// non default constructor that copies input parameters
VectorInt::VectorInt( int* array, size_t size )
{
  // creates space on the heap and then stores values based on the input array
  data = new int[size];
  for ( size_t i = 0; i < size; i++ ) {
    data[i] = array[i];
  }
  // initializes private member fields
  sizeArray = size;
  maxsize   = size;
}

//------------------------------------------------------------------------
// VectorInt::VectorInt
//------------------------------------------------------------------------
// Copy constructor that takes a current vectorInt and copys the values into a
// new vectorInt
VectorInt::VectorInt( const VectorInt& vec )
{
  // sets vectorInt to nullptr if size is zero
  if ( vec.sizeArray == 0 ) {
    data = nullptr;
  }
  // when size is greater than zero
  else {
    // copies data from the vectorInt parameter into new array
    data = new int[vec.sizeArray];
    for ( size_t i = 0; i < vec.sizeArray; i++ ) {
      data[i] = vec.data[i];
    }
  }
  // initializes private member variables based on input vector
  sizeArray = vec.sizeArray;
  maxsize   = vec.sizeArray;
}

//------------------------------------------------------------------------
// VectorInt::operator=
//------------------------------------------------------------------------
// overloads the = operator to copy the values from
// one vector to another when set equal to each other
VectorInt& VectorInt::operator=( const VectorInt& vec )
{
  //ECE2400_DEBUG( "VectorInt::operator= called!" );
  // checks to see if the vector is the same vector
  if ( this != &vec ) {
    // deletes current data in order to be replaced
    delete[] data;
    // if there isn't any room in the vector being copied,
    // initialize the vector to default constructor values
    if ( vec.maxsize == 0 ) {
      sizeArray = 0;
      data      = nullptr;
      maxsize   = 0;
    }
    // if the size of the parameter vector is non-zero
    else {
      // set the member variables of the new vector to match the parameter
      // vector
      sizeArray = vec.sizeArray;
      data      = new int[vec.maxsize];
      maxsize   = vec.maxsize;
      for ( size_t i = 0; i < sizeArray; i++ ) {
        data[i] = vec.data[i];
      }
    }
  }
  // returns vector with new values
  return *this;
}

//------------------------------------------------------------------------
// VectorInt::pushback
//------------------------------------------------------------------------
// pushback_v2 function that adds values to the vector
void VectorInt::push_back( int value )
{
  assert( this != nullptr );
  //ECE2400_DEBUG( "vector_int_push_back_v2(%p, %d) called!", this, value );
  // case for when the array is empty
  if ( maxsize == 0 ) {
    //ECE2400_DEBUG( "Checking maxsize == 0" );
    maxsize = maxsize + 1;
    data    = new int[1];
    data[0] = value;
    sizeArray += 1;
  }
  // case for when the array is full
  else if ( ( sizeArray ) == ( maxsize ) ) {
    //ECE2400_DEBUG( "Checking maxsize == size" );
    // create a temporary array to hold the current values
    int* newVec = new int[maxsize * 2];
    for ( unsigned int i = 0; i < this->maxsize; i++ ) {
      newVec[i] = data[i];
    }
    // add new value
    newVec[maxsize] = value;
    // delete data array from heap
    delete[] data;
    // update member variables with new values
    data      = newVec;
    sizeArray = sizeArray + 1;
    maxsize   = maxsize * 2;
  }
  // case for when the size of the array is still smaller than maxsize
  else {
    //ECE2400_DEBUG( "Checking maxsize != size" );
    data[sizeArray] = value;
    sizeArray       = sizeArray + 1;
  }
}

//------------------------------------------------------------------------
// VectorInt::contains
//------------------------------------------------------------------------
// returns boolean values depending on whether the vector contains a specific
// value
bool VectorInt::contains( int value ) const
{
  assert( this != nullptr );
  //ECE2400_DEBUG( "vector_int_contains(%p, %d) called!", this, value );
  // Searching the vector to find if the value is in the loop, returning true if
  // found returns false is the vector does not contain the value
  for ( size_t i = 0; i < sizeArray; i++ ) {
    if ( data[i] == value ) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------
// VectorInt::find_closest
//------------------------------------------------------------------------
// finds the value in the vector closest to the input value
int VectorInt::find_closest( int value ) const
{
  //ECE2400_DEBUG( "vector_int_find_closest(%p, %d) called!", this, value );
  // case when vector data size is zero
  if ( sizeArray == 0 ) {
    throw ece2400::OutOfRange( "Empty array, index out of bounds" );
  }

  uint_t difference = distance( data[0], value );
  int    answer     = data[0];
  // iterates over vector to compare value with current input values
  for ( size_t i = 0; i < sizeArray; i++ ) {
    uint_t compare = distance( data[i], value );
    if ( difference > compare ) {
      difference = compare;
      answer     = data[i];
    }
  }
  return answer;
}

//------------------------------------------------------------------------
// VectorInt::print
//------------------------------------------------------------------------
// prints the vector's values
void VectorInt::print() const
{
  assert( this != nullptr );
  for ( size_t i = 0; i < sizeArray; i++ ) {
    printf( "Element %lu has the value: %d\n", i, this->data[i] );
  }
}


//------------------------------------------------------------------------
// VectorInt::VectorInt()
//------------------------------------------------------------------------
// default Construct for vector that initialized private member fields
inline VectorInt::VectorInt()
{
  // assigns data to a nullptr, and sets maxsize = size = 0
  data      = nullptr;
  maxsize   = 0;
  sizeArray = 0;
}

//------------------------------------------------------------------------
// VectorInt::~VectorInt()
//------------------------------------------------------------------------
// Destructor for vector that deletes all data from the heap
inline VectorInt::~VectorInt()
{
  // deletes the data in the vector
  delete[] data;
}

//------------------------------------------------------------------------
// VectorInt::size()
//------------------------------------------------------------------------
// Returns size of the current vectorInt
inline size_t VectorInt::size() const
{
  // returns private member field that holds the size of the vector
  return sizeArray;
}

//------------------------------------------------------------------------
// VectorInt::operator[]
//------------------------------------------------------------------------
// overloads the [] operator to return an value at the specifed index
inline int VectorInt::operator[]( size_t idx ) const
{
  // returns the value in the data array at the specified index
  return data[idx];
}

//------------------------------------------------------------------------
// VectorInt::at()
//------------------------------------------------------------------------
// Returns the value at the specified index if in the bound of the vector
inline int VectorInt::at( size_t idx ) const
{
  if ( idx < sizeArray ) {
    // returns value at specific index
    return data[idx];
  }
  else {
    // returns an exceptions when idex out of bounds
    throw ece2400::OutOfRange( "Index out of bounds" );
  }
}

//------------------------------------------------------------------------
// VectorInt::size()
//------------------------------------------------------------------------
// sorts the vector based on the sorting algorithm in sort-int class
void VectorInt::sort()
{
  // function call to sort_int function in sort-int.cc
  sort_int( data, sizeArray );
}