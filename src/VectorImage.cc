//========================================================================
// VectorImage.cc
//========================================================================
// Implementation of VectorImage.

#include "VectorImage.h"
#include "Image.h"
#include "ece2400-stdlib.h"
#include "sort-image.h"

//------------------------------------------------------------------------
// VectorImage::VectorImage
//------------------------------------------------------------------------
// non default constructor that copies input parameters
VectorImage::VectorImage( Image* array, size_t size )
{
  // initializes a vector based on the specifications provided in the parameters
  m_data = new Image[size];
  for ( size_t i = 0; i < size; i++ ) {
    m_data[i] = array[i];
  }
  // initializes private member fields
  m_sizeArray = size;
  m_maxSize   = size;
}

//------------------------------------------------------------------------
// VectorImage::VectorImage
//------------------------------------------------------------------------
// Copy constructor that takes a current vectorImage and copys the values into a
// new vectorImage
VectorImage::VectorImage( const VectorImage& vec )
{
  // sets vectorImage to nullptr if size is zero
  if ( vec.m_sizeArray == 0 ) {
    m_data = nullptr;
  }
  // when size is greater than zero
  else {
    // copies data from the vectorImage parameter into new array
    m_data = new Image[vec.m_sizeArray];
    for ( size_t i = 0; i < vec.m_sizeArray; i++ ) {
      m_data[i] = vec.m_data[i];
    }
  }
  // initializes private member variables based on input vector
  m_sizeArray = vec.m_sizeArray;
  m_maxSize   = vec.m_sizeArray;
}

//------------------------------------------------------------------------
// VectorImage::operator=
//------------------------------------------------------------------------
// overloads the = operator to copy the values from
// one vector to another when set equal to each other
VectorImage& VectorImage::operator=( const VectorImage& vec )
{
  // checks to see if the vector is the same vector
  if ( this != &vec ) {
    // deletes current data in order to be replaced
    delete[] m_data;
    // if there isn't any room in the vector being copied,
    // initialize the vector to default constructor values
    if ( vec.m_maxSize == 0 ) {
      m_sizeArray = 0;
      m_data      = nullptr;
      m_maxSize   = 0;
    }
    // if the size of the parameter vector is non-zero
    else {
      // set the member variables of the new vector to match the parameter
      // vector
      m_sizeArray = vec.m_sizeArray;
      m_data      = new Image[vec.m_maxSize];
      m_maxSize   = vec.m_maxSize;
      for ( size_t i = 0; i < m_sizeArray; i++ ) {
        m_data[i] = vec.m_data[i];
      }
    }
  }
  // returns vector with new Images
  return *this;
}

//------------------------------------------------------------------------
// VectorImage::pushback
//------------------------------------------------------------------------
// pushback_v2 function that adds values to the vector
void VectorImage::push_back( const Image& img )
{
  assert( this != nullptr );
  // case for when the array is empty
  if ( m_maxSize == 0 ) {
    m_maxSize = m_maxSize + 1;
    m_data    = new Image[1];
    m_data[0] = img;
    m_sizeArray += 1;
  }
  else if ( ( m_sizeArray ) == ( m_maxSize ) ) {
    // create a temporary array to hold the current values
    Image* newVec = new Image[m_maxSize * 2];
    for ( unsigned int i = 0; i < this->m_maxSize; i++ ) {
      newVec[i] = m_data[i];
    }
    // add new value
    newVec[m_maxSize] = img;
    // delete data array from heap
    delete[] m_data;
    // update member variables with new values
    m_data      = newVec;
    m_sizeArray = m_sizeArray + 1;
    m_maxSize   = m_maxSize * 2;
  }
  // case for when the size of the array is still smaller than m_maxSize
  else {
    m_data[m_sizeArray] = img;
    m_sizeArray         = m_sizeArray + 1;
  }
}

//------------------------------------------------------------------------
// VectorImage::contains
//------------------------------------------------------------------------
// returns boolean values depending on whether the vector contains a specific
// Image
bool VectorImage::contains( const Image& img ) const
{
  assert( this != nullptr );
  // Searching the vector to find if the value is in the loop, returning true if
  // found returns false is the vector does not contain the Image
  for ( size_t i = 0; i < m_sizeArray; i++ ) {
    if ( m_data[i] == img ) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------
// VectorImage::find_closest
//------------------------------------------------------------------------
// finds the value in the vector closest to the input value
Image VectorImage::find_closest( const Image& img ) const
{
  // ECE2400_DEBUG( "vector_Image_find_closest(%p, %d) called!", this, img );
  // case when vector m_data size is zero
  if ( m_sizeArray == 0 ) {
    throw ece2400::OutOfRange( "Empty array, index out of bounds" );
  }

  uint_t difference = distance( m_data[0], img );
  Image  answer     = m_data[0];
  // iterates over vector to compare value with current input values
  for ( size_t i = 0; i < m_sizeArray; i++ ) {
    uint_t compare = distance( m_data[i], img );
    if ( difference > compare ) {
      difference = compare;
      answer     = m_data[i];
    }
  }
  return answer;
}

// printing out the vector - Matt
// void VectorImage::print() const
// {
//   assert( this != nullptr );
//   for ( size_t i = 0; i < m_sizeArray; i++ ) {
//     printf( "Element %lu has the value: %d\n", i, this->m_data[i] );
//   }
// }
