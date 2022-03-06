//========================================================================
// Table.h
//========================================================================
// Declarations for generic table.

#ifndef TABLE_H
#define TABLE_H

#include <cstddef>

template <typename T>
class Vector;

template <typename T, typename HashFunc>
class Table {
 public:
  Table( unsigned int nbins, T min, T max, HashFunc hash );
  // Methods
  size_t size() const;
  void   add( const T& value );
  bool   contains( const T& value ) const;

  template <typename DistFunc>
  const T& find_closest( const T& value, DistFunc dist ) const;

  void print() const;

 private:
  Vector<Vector<T>> m_tbl;
  unsigned int      m_nbins;
  T                 m_min;
  T                 m_max;
  size_t            m_size;
  HashFunc          m_hash;
  unsigned int      m_range;
};

// Include inline definitions
#include "Table.inl"

#endif /* TABLE_H */