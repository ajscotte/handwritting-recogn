#include "ece2400-stdlib.h"
#include "sort-int.h"
//========================================================================
// VectorInt.inl
//========================================================================

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