//========================================================================
// Image.cc
//========================================================================
// Implementations for Image.

#include "Image.h"
#include "VectorByte.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// distance
//------------------------------------------------------------------------
// A helper function that calculates the Euclidean distance between two
// images.
// Throws an ece2400::InvalidArgument exception if dimension of a doesn't
// match that of b.

uint_t distance( const Image& a, const Image& b )
{
  // tests to see if Images have the same dimensions
  if ( ( a.get_ncols() != b.get_ncols() ) ||
       ( a.get_nrows() != b.get_nrows() ) ) {
    throw ece2400::InvalidArgument( "Dimensions do not match" );
  }
  size_t size       = a.get_nrows() * a.get_ncols();
  uint_t distance_h = 0;
  // calulates Eulidean distance for each index
  for ( size_t i = 0; i < size; i++ ) {
    distance_h += ( a[i] - b[i] ) * ( a[i] - b[i] );
  }

  return distance_h;
}
//------------------------------------------------------------------------
// print_pixel
//------------------------------------------------------------------------
// A helper function that prints a grayscale pixel using unicode based on
// the integer value.

void print_pixel( int v )
{
  if ( v <= 0 )
    std::printf( "%s", "  " );
  else if ( 0 < v && v <= 64 )
    std::printf( "%s", "\u2591\u2591" );
  else if ( 64 < v && v <= 128 )
    std::printf( "%s", "\u2592\u2592" );
  else if ( 128 < v && v <= 192 )
    std::printf( "%s", "\u2593\u2593" );
  else
    std::printf( "%s", "\u2588\u2588" );
}

// returns the the value of the pixel at the x-th column and y-th row-Alex
int Image::at( size_t x, size_t y ) const
{
  if ( ( x >= m_cols ) || ( y >= m_rows ) ) {
    throw ece2400::OutOfRange(
        "Please enter a value for the rows and columns inside the bounds." );
  }
  int rowAdjust = y * m_cols;
  // type converts to correct type
  return (int) m_vector[rowAdjust + x];
}

//------------------------------------------------------------------------
// Image::getintensity
//------------------------------------------------------------------------
// finds the intensity of an image by adding up each value in the vector private
// variable
int Image::get_intensity() const
{
  // optimization that checks if intensity has not been changed yet
  if ( m_intensity < 0 ) {
    m_intensity = 0;
    size_t size = m_cols * m_rows;
    // calculates intensity of an image by adding value at each index in image
    // vector
    for ( size_t i = 0; i < size; i++ ) {
      m_intensity = m_intensity + m_vector[i];
    }
  }
  // returns private member variable
  return m_intensity;
}
//------------------------------------------------------------------------
// Image::print
//------------------------------------------------------------------------
// prints the contents of the image. We are provided with a print_pixel helper
// function to print a grey scale pixel based on the integer value
void Image::print() const
{
}
//------------------------------------------------------------------------
// Image::operator==
//------------------------------------------------------------------------
// Overload the equal-to operator so that it compares the value of each pixel.
// Return true only if the each pixel in the right-hand-side image is the same
// as that in the current image. If the dimensions of the two images do not
// match, simply return false. Otherwise return true
bool Image::operator==( const Image& rhs ) const
{
  // checks to see if demsions are the same
  if ( ( rhs.m_cols != m_cols ) || rhs.m_rows != m_rows ) {
    return false;
  }
  // checks to see if each index value in the member vector is the same
  for ( size_t i = 0; i < m_vector.size(); i++ ) {
    if ( m_vector[i] != rhs.m_vector[i] ) {
      return false;
    }
  }
  // if exactly the same returns true
  return true;
}

// Overload the equal-to operator so that it compares the value of each pixel.
// Return false only if the each pixel in the right-hand-side image is the same
// as that in the current image. If the dimensions of the two images do not
// match, simply return true. Return false if both images are empty.-Alex
