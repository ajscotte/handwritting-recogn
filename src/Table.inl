//========================================================================
// Table.inl
//========================================================================
// Implementation of Table.

#include "Vector.h"
#include "ece2400-stdlib.h"
#include <iostream>

//------------------------------------------------------------------
// Table::Table 
//------------------------------------------------------------------
// Default constructor, initializes all private member fields
template <typename T, typename HashFunc>
Table<T, HashFunc>::Table( unsigned int nbins, T min, T max, HashFunc hash )
{
  if ( ( nbins == 0 ) || ( hash( max ) < hash( min ) ) ) {
    throw ece2400::OutOfRange(
        "The number of bins is 0 or the max is less than the min." );
  }
  m_nbins = nbins;
  m_min   = min;
  m_max   = max;
  m_hash  = hash;
  m_size  = 0;
  m_range = ( hash( max ) - hash( min ) ) / nbins;
  if ( m_range == 0 ) {
    m_range = 1;
  }
  for ( size_t i = 0; i < nbins; i++ ) {
    m_tbl.push_back( Vector<T>() );
  }
}

//------------------------------------------------------------------
// Table::size
//------------------------------------------------------------------
// returns the size of the Table
template <typename T, typename HashFunc>
size_t Table<T, HashFunc>::size() const
{
  return m_size;
}

//------------------------------------------------------------------
// Table::add
//------------------------------------------------------------------
// adds a new element into the Table
template <typename T, typename HashFunc>
void Table<T, HashFunc>::add( const T& value )
{
  // make sure to increment size by 1 with every addition
  unsigned int value_h = m_hash( value );
  unsigned int max     = m_hash( m_max );
  unsigned int min     = m_hash( m_min );
  if ( value_h < min ) {
    m_tbl[0].push_back( value );
  }
  else if ( value_h > max ) {
    m_tbl[m_nbins - 1].push_back( value );
  }
  else {
    unsigned int bin = ( value_h - min ) / m_range;
    if ( bin > ( m_nbins - 1 ) ) {
      bin = m_nbins - 1;
    }
    m_tbl[bin].push_back( value );
  }
  m_size++;
}

//------------------------------------------------------------------
// Table::contains
//------------------------------------------------------------------
// Search the Table<T,HashFunc> for the given value and returns true if
// the value is found and false otherwise. If the Table<T,HashFunc> is
// empty, then this function should just return false.
template <typename T, typename HashFunc>
bool Table<T, HashFunc>::contains( const T& value ) const
{
  unsigned int value_h = m_hash( value );
  unsigned int min     = m_hash( m_min );
  unsigned int bin     = ( value_h - min ) / m_range;
  if ( bin > ( m_nbins - 1 ) ) {
    bin = m_nbins - 1;
  }
  return m_tbl[bin].contains( value );
}

//------------------------------------------------------------------
// Table::find_closest
//------------------------------------------------------------------
// finds the closet value to value in the table
template <typename T, typename HashFunc>
template <typename DistFunc>
const T& Table<T, HashFunc>::find_closest( const T& value, DistFunc dist ) const
{
  unsigned int value_h = m_hash( value );
  unsigned int max     = m_hash( m_max );
  unsigned int min     = m_hash( m_min );
  unsigned int bin     = ( value_h - min ) / m_range;
  if ( m_size == 0 ) {
    throw ece2400::OutOfRange( "Empty table" );
  }
  else if ( value_h > max ) {
    bin = m_nbins - 1;
  }
  else if ( value_h < min ) {
    bin = 0;
  }
  unsigned int max_bin = bin;
  unsigned int min_bin = bin;
  if ( m_tbl[bin].size() == 0 ) {
    // std::printf("Bin size1: %lu\n", m_tbl[bin].size());
    for ( unsigned int i = 0; i < m_nbins; i++ ) {
      if ( m_tbl[max_bin].size() != 0 ) {
        bin = max_bin;
        break;
      }
      else if ( m_tbl[min_bin].size() != 0 ) {
        bin = min_bin;
        break;
      }
      if ( min_bin != 0 ) {
        min_bin--;
      }
      if ( max_bin != m_nbins - 1 ) {
        max_bin++;
      }
    }
  }
  return m_tbl[bin].find_closest( value, dist );
}

//------------------------------------------------------------------
// Table::print
//------------------------------------------------------------------
// prints out the values of the table
template <typename T, typename HashFunc>
void Table<T, HashFunc>::print() const
{
  for ( unsigned int i = 0; i < m_nbins; i++ ) {
    for ( size_t c = 0; c < m_tbl[i].size(); c++ ) {
      std::cout << m_tbl[i][c] << " ";
    }
    std::cout << std::endl;
  }
}