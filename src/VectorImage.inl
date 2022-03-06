#include "ece2400-stdlib.h"
#include "sort-image.h"
//========================================================================
// VectorImage.inl
//========================================================================

//------------------------------------------------------------------------
// VectorImage::VectorImage()
//------------------------------------------------------------------------
// default Construct for vector that initialized private member fields
inline VectorImage::VectorImage()
{
  // assigns m_data to a nullptr, and sets m_maxSize = size = 0
  m_data      = nullptr;
  m_maxSize   = 0;
  m_sizeArray = 0;
}

//------------------------------------------------------------------------
// VectorImage::size()
//------------------------------------------------------------------------
// Returns size of the current vectorImage
inline size_t VectorImage::size() const
{
  // returns private member field that holds the size of the vector
  return m_sizeArray;
}

//------------------------------------------------------------------------
// VectorImage::at()
//------------------------------------------------------------------------
// Returns the value at the specified index if in the bound of the vector
inline Image VectorImage::at( size_t idx ) const
{
  // ECE2400_DEBUG( "vector_Image_at(%p, %lu) called!", this, idx );
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
// VectorImage::operator[]
//------------------------------------------------------------------------
// overloads the [] operator to return an value at the specifed index
inline const Image& VectorImage::operator[]( size_t idx ) const
{
  // returns the value in the data array at the specified index
  return m_data[idx];
}

//------------------------------------------------------------------------
// VectorImage::size()
//------------------------------------------------------------------------
// sorts the vector based on the sorting algorithm in sort-Image class
void VectorImage::sort()
{
  // function call to sort_Image function in sort-image.cc
  sort_image( m_data, m_sizeArray );
}

//------------------------------------------------------------------------
// VectorImage::~VectorImage()
//------------------------------------------------------------------------
// Destructor for vector that deletes all data from the heap
VectorImage::~VectorImage()
{
  // deletes the m_data in the vector
  delete[] m_data;
}