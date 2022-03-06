//========================================================================
// Image.inl
//========================================================================

//------------------------------------------------------------------------
// Image::Image
//------------------------------------------------------------------------
// Default consructor that initializes all private member fields
inline Image::Image()
{
  // initializes private member variables
  m_rows      = 0;
  m_cols      = 0;
  m_label     = '?';
  m_intensity = -1;
}

//------------------------------------------------------------------------
// Image::Image
//------------------------------------------------------------------------
// Non-Default consructor that initializes all private member fields with known
// variables
inline Image::Image( const VectorInt& vec, size_t ncols, size_t nrows )
{
  // checks for errors
  if ( ncols >= 128 )
    throw ece2400::InvalidArgument(
        "The size of the columns needs to be less than 128 inputs." );
  if ( nrows >= 128 )
    throw ece2400::InvalidArgument(
        "The size of the rowss needs to be less than 128 inputs" );
  if ( vec.size() != ( nrows * ncols ) )
    throw ece2400::InvalidArgument(
        "The size of the vector does not match the number of rows times the number of columns." );
  // converting from VectorInt to VectorByte
  m_vector = vec;
  // initializes private member variables
  m_cols      = ncols;
  m_rows      = nrows;
  m_label     = '?';
  m_intensity = -1;
}

//------------------------------------------------------------------------
// Image::get_ncols
//------------------------------------------------------------------------
// returns m_cols private member variable
inline size_t Image::get_ncols() const
{
  return m_cols;
}

//------------------------------------------------------------------------
// Image::get_nrows
//------------------------------------------------------------------------
// returns m_rows private member variable
inline size_t Image::get_nrows() const
{
  return m_rows;
}

//------------------------------------------------------------------------
// Image::set_label
//------------------------------------------------------------------------
// mutator method for m_label private variable
inline void Image::set_label( const char& label )
{
  // change label value
  m_label = label;
}

//------------------------------------------------------------------------
// Image::get_label
//------------------------------------------------------------------------
// returns m_label private member variable
inline char Image::get_label() const
{
  return m_label;
}
//------------------------------------------------------------------------
// Image::operator[]
//------------------------------------------------------------------------
// Overload the subscript operator. returns the pixel at the given
// index idx of the image without any boundary check and type converts to int.
inline int Image::operator[]( size_t idx ) const
{
  // type converts to int from unsigned char
  return (int) m_vector[idx];
}
//------------------------------------------------------------------------
// Image::operator!=
//------------------------------------------------------------------------
// Overload the equal-to operator so that it compares the value of each pixel.
// Return false only if the each pixel in the right-hand-side image is the same
// as that in the current image. If the dimensions of the two images do not
// match, simply return true. Return false if both images are empty.
bool Image::operator!=( const Image& rhs ) const
{
  // oposite of operator= function
  return !operator==( rhs );
}