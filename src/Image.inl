//========================================================================
// Image.inl
//========================================================================
// Implementations for inline functions for Image. This is for
// optimization purpose only. It is fine to leave this file empty.


//------------------------------------------------------------------------
// Image::operator[]
//------------------------------------------------------------------------
// Overload the subscript operator. returns the pixel at the given
// index idx of the image without any boundary check and type converts to int.
// template<typename T>
inline int Image::operator[]( size_t idx ) const
{
  return m_vector[idx];
}

//------------------------------------------------------------------------
// Image::Image()
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
inline Image::Image( const Vector<int>& vec, size_t ncols, size_t nrows )
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
  // m_vector = vec;
  for ( size_t i = 0; i < ncols * nrows; i++ ) {
    m_vector.push_back( (unsigned char) vec[i] );
  }
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
inline void Image::set_label( char label )
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
