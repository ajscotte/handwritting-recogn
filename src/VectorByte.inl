#include "ece2400-stdlib.h"
//========================================================================
// VectorByte.inl
//========================================================================

//------------------------------------------------------------------------
// VectorByte::VectorByte()
//------------------------------------------------------------------------
// default Construct for vector that initialized private member fields
inline VectorByte::VectorByte()
{
  // assigns data to a nullptr, and sets maxsize = size = 0
  m_data      = nullptr;
  m_maxsize   = 0;
  m_sizeArray = 0;
}

//------------------------------------------------------------------------
// VectorByte::~VectorByte()
//------------------------------------------------------------------------
// Destructor for vector that deletes all data from the heap
inline VectorByte::~VectorByte()
{
  // deletes the data in the vector
  delete[] m_data;
}

//------------------------------------------------------------------------
// VectorByte::size()
//------------------------------------------------------------------------
// Returns size of the current vectorByte
inline size_t VectorByte::size() const
{
  // returns private member field that holds the size of the vector
  return m_sizeArray;
}

//------------------------------------------------------------------------
// VectorByte::operator[]
//------------------------------------------------------------------------
// overloads the [] operator to return an value at the specifed index
inline unsigned char VectorByte::operator[]( size_t idx ) const
{
  // returns the value in the data array at the specified index
  return m_data[idx];
}

//------------------------------------------------------------------------
// VectorByte::at()
//------------------------------------------------------------------------
// Returns the value at the specified index if in the bound of the vector
inline unsigned char VectorByte::at( size_t idx ) const
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