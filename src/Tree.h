//========================================================================
// Tree.h
//========================================================================
// Declarations for generic tree.

#ifndef TREE_H
#define TREE_H

#include <cstddef>

template <typename T, typename CmpFunc>
class Tree {
 public:
  inline Tree( unsigned int K, CmpFunc cmp );
  ~Tree();

  // Copy constructor
  Tree( const Tree<T, CmpFunc>& tree );

  // Methods
  inline size_t size() const;
  void          add( const T& value );
  bool          contains( const T& value ) const;

  template <typename DistFunc>
  const T& find_closest( const T& value, DistFunc dist ) const;

  void print() const;

  // Operator overloading
  Tree<T, CmpFunc>& operator=( const Tree<T, CmpFunc>& tree );

 private:
  struct Node {
    inline Node( const T& v );
    Node* m_left_p;
    Node* m_right_p;
    T     m_value;  // maybe fix
  };
  Node*        m_root_p;
  size_t       m_size;
  unsigned int m_k;
  CmpFunc      m_cmp;
  void         clear_node( Node* node_p );
  bool         contains_h( Node* node_p, const T& v ) const;
  Node*        add_h( Node* node_p, const T& v );
  void         copy_h( Node* node_p, Node* node_p2 );
  void         print_h( Node* node_p ) const;

  template <typename DistFunc>
  Node* binary_find_h( Node* node_p, const T& value, DistFunc dist,
                       int level ) const;
  template <typename DistFunc>
  Node* linear_find_h( Node* node_p, const T& value, DistFunc dist,
                       Node* closest ) const;
};

// Include inline definitions
#include "Tree.inl"

#endif /* TREE_H */
