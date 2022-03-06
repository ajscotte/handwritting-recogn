//========================================================================
// Tree.inl
//========================================================================
// Implementation of Tree.

#include "ece2400-stdlib.h"
#include <cassert>
#include <iostream>

//------------------------------------------------------------------------
// Tree::Node
//------------------------------------------------------------------------
// establishes the member fields of the node struct
template <typename T, typename CmpFunc>
inline Tree<T, CmpFunc>::Node::Node( const T& v )
// :m_value(v), m_left_p(nullptr), m_right_p(nullptr)
{
  m_value   = v;
  m_left_p  = nullptr;
  m_right_p = nullptr;
}


//------------------------------------------------------------------
// Tree::Constructor
//------------------------------------------------------------------
// initializes all private member fields
template <typename T, typename CmpFunc>
inline Tree<T, CmpFunc>::Tree( unsigned int K, CmpFunc cmp )
    : m_root_p( nullptr ), m_size( 0 ), m_k( K ), m_cmp( cmp )
{
}



//------------------------------------------------------------------
// Tree::Destructor
//------------------------------------------------------------------
// recursively destruct each node until you reach the root pointer
template <typename T, typename CmpFunc>
Tree<T, CmpFunc>::~Tree()
{
  clear_node( m_root_p );
}

//------------------------------------------------------------------
// Tree::close_node
//------------------------------------------------------------------
// Destructor Helper function
template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::clear_node( Node* node_p )
{
  if ( node_p == nullptr ) {
    return;
  }
  // recursively zoom into the left side of the tree
  clear_node( node_p->m_left_p );
  // recursively zoom into the right side of the tree
  clear_node( node_p->m_right_p );
  delete node_p;
}

//------------------------------------------------------------------------
// Tree::Tree
//------------------------------------------------------------------------
// copy costructor that takes in another tree and performs a deep copy
template <typename T, typename CmpFunc>
Tree<T, CmpFunc>::Tree( const Tree<T, CmpFunc>& tree )
{
  // copies private member fields that are constant throughout tree
  m_k   = tree.m_k;
  m_cmp = tree.m_cmp;
  // if the size is zero of the input tree
  if ( tree.m_size == 0 ) {
    // set the private fields to the appropriate value for a size zero tree
    m_root_p = nullptr;
    m_size   = 0;
  }
  // when the size isn't zero
  else {
    // create a new node on the heap for the nonzero sized tree
    m_size   = tree.m_size;
    m_root_p = new Node( tree.m_root_p->m_value );
    // call for recursive function
    copy_h( tree.m_root_p, m_root_p );
  }
}

//------------------------------------------------------------------------
// Tree::copy_h
//------------------------------------------------------------------------
// copy costructor recursive helper function
template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::copy_h( Node* node_p, Node* node_p2 )
{
  // copys the value from the input tree

  // base cases when the tree gets to the end and doesn't have anymore nodes
  if ( node_p->m_left_p == nullptr && node_p->m_right_p == nullptr ) {
    node_p2->m_left_p  = nullptr;
    node_p2->m_right_p = nullptr;
    return;
  }
  else if ( node_p->m_left_p == nullptr ) {
    node_p2->m_left_p  = nullptr;
    node_p2->m_right_p = new Node( node_p->m_right_p->m_value );
    copy_h( node_p->m_right_p, node_p2->m_right_p );
  }
  else if ( node_p->m_right_p == nullptr ) {
    node_p2->m_right_p = nullptr;
    node_p2->m_left_p  = new Node( node_p->m_left_p->m_value );
    copy_h( node_p->m_left_p, node_p2->m_left_p );
  }
  // recursive case that create a new node on the stack for both branches
  else {
    // node_p2 = new Node(node_p->m_value);
    node_p2->m_right_p = new Node( node_p->m_right_p->m_value );
    node_p2->m_left_p  = new Node( node_p->m_left_p->m_value );
    copy_h( node_p->m_left_p, node_p2->m_left_p );
    copy_h( node_p->m_right_p, node_p2->m_right_p );
  }
}

//------------------------------------------------------------------
// Tree::operator=
//------------------------------------------------------------------
// overloads the = operator
template <typename T, typename CmpFunc>
Tree<T, CmpFunc>& Tree<T, CmpFunc>::operator=( const Tree<T, CmpFunc>& tree )
{
  if ( this != &tree ) {
    clear_node( m_root_p );
    // copies private member fields that are constant throughout tree
    m_k   = tree.m_k;
    m_cmp = tree.m_cmp;
    // if the size is zero of the input tree
    if ( tree.m_size == 0 ) {
      // set the private fields to the appropriate value for a size zero tree
      m_root_p = nullptr;
      m_size   = 0;
    }
    // when the size isn't zero
    else {
      // create a new node on the heap for the nonzero sized tree
      m_root_p = new Node( tree.m_root_p->m_value );
      m_size   = tree.m_size;
      // call for recursive function
      copy_h( tree.m_root_p, m_root_p );
    }
  }
  return *this;
}

//------------------------------------------------------------------
// Tree::size
//------------------------------------------------------------------
// returns the size of the tree, returns the member field
template <typename T, typename CmpFunc>
inline size_t Tree<T, CmpFunc>::size() const
{
  return m_size;
}

//------------------------------------------------------------------
// Tree::add
//------------------------------------------------------------------
// adds a new element into the tree
template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::add( const T& value )
{
  m_root_p = add_h( m_root_p, value );
}

//------------------------------------------------------------------------
// Tree::add_h
//------------------------------------------------------------------------
// helper function for add to recursively find the proper place to add the
// new node.
template <typename T, typename CmpFunc>
typename Tree<T, CmpFunc>::Node* Tree<T, CmpFunc>::add_h( Node*    node_p,
                                                          const T& v )
{
  // base case: found place to insert new node
  if ( node_p == nullptr ) {
    m_size++;
    return new Node( v );
  }
  // base case: value is already in the tree
  if ( v == node_p->m_value )
    return node_p;

  // recursive case
  if ( m_cmp( node_p->m_value, v ) )
    node_p->m_right_p = add_h( node_p->m_right_p, v );
  else
    node_p->m_left_p = add_h( node_p->m_left_p, v );

  return node_p;
}

//------------------------------------------------------------------
// Tree::contains
//------------------------------------------------------------------
// Search the Tree<T,CmpFunc> for the given value and returns true if
// the value is found and false otherwise. If the Tree<T,CmpFunc> is
// empty, then this function should just return false.
template <typename T, typename CmpFunc>
bool Tree<T, CmpFunc>::contains( const T& value ) const
{
  return contains_h( m_root_p, value );
}


//------------------------------------------------------------------
// Tree::contains_h
//------------------------------------------------------------------
// helper function for contains
template <typename T, typename CmpFunc>
bool Tree<T, CmpFunc>::contains_h( Node* node_p, const T& v ) const
{
  if ( node_p == nullptr ) {
    return false;
  }
  // checks if the value V is greater than the current node's value
  // if ( m_cmp( node_p->m_value, v) ) {
  if ( node_p->m_value == v ) {
    return true;
  }
  if ( m_cmp( node_p->m_value, v ) ) {
    return contains_h( node_p->m_right_p, v );
  }
  // since not greater, places value on the left side of the tree
  else {
    return contains_h( node_p->m_left_p, v );
  }
}

//------------------------------------------------------------------------
// Tree::find_closest
//------------------------------------------------------------------------
// recursively find the closet value to the value indicated
template <typename T, typename CmpFunc>
template <typename DistFunc>
const T& Tree<T, CmpFunc>::find_closest( const T& value, DistFunc dist ) const
{
  int levels = 0;
  if ( m_size == 0 ) {
    throw ece2400::OutOfRange( "size is zero" );
  }
  else if ( m_k < m_size ) {
    levels = ece2400::log2( m_size ) - ece2400::log2( m_k );
  }
  const T& close = binary_find_h( m_root_p, value, dist, levels )->m_value;
  return close;
}

//------------------------------------------------------------------------
// Tree::binary_find_h
//------------------------------------------------------------------------
// helps find the closest value in the tree by recusively searching
// switches to linear search when the level is equal to 0 or the 
// nodes to the left or right are nullptrs
template <typename T, typename CmpFunc>
template <typename DistFunc>
typename Tree<T, CmpFunc>::Node* Tree<T, CmpFunc>::binary_find_h(
    Node* node_p, const T& value, DistFunc dist, int level ) const
{
  // std::printf("Value: %d\n",node_p->m_value);
  // std::printf("Value2: %d\n",value);
  if ( node_p->m_value == value ) {
    return node_p;
  }
  else if ( level == 0 ) {
    return linear_find_h( node_p, value, dist, node_p );
  }
  else if ( m_cmp( node_p->m_value, value ) ) {
    if ( node_p->m_right_p == nullptr ) {
      return linear_find_h( node_p, value, dist, node_p );
    }
    return binary_find_h( node_p->m_right_p, value, dist, level - 1 );
  }
  else {
    if ( node_p->m_left_p == nullptr ) {
      return linear_find_h( node_p, value, dist, node_p );
    }
    return binary_find_h( node_p->m_left_p, value, dist, level - 1 );
  }
}

//------------------------------------------------------------------------
// Tree::linear_find_h
//------------------------------------------------------------------------
// Linearly searches the tree to find the correct node, also uses a recursive
// element to continously step throught the tree.
template <typename T, typename CmpFunc>
template <typename DistFunc>
typename Tree<T, CmpFunc>::Node* Tree<T, CmpFunc>::linear_find_h(
    Node* node_p, const T& value, DistFunc dist, Node* closest ) const
{
  if ( node_p == nullptr ) {
    return closest;
  }
  else if ( dist( value, node_p->m_value ) < dist( value, closest->m_value ) ) {
    closest = node_p;
  }
  closest = linear_find_h( node_p->m_left_p, value, dist, closest );
  closest = linear_find_h( node_p->m_right_p, value, dist, closest );
  return closest;
}

//------------------------------------------------------------------------
// Tree::print
//------------------------------------------------------------------------
//prints out the tree
template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::print() const
{
  print_h( m_root_p );
}


//------------------------------------------------------------------------
// Tree::print_h
//------------------------------------------------------------------------
// Print helper function to help print out all the nodes
template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::print_h( Node* node_p ) const
{
  if ( node_p == nullptr ) {
    return;
  }
  std::cout << node_p->m_value << std::endl;
  std::cout << "size: " << m_size << std::endl;
  print_h( node_p->m_left_p );
  print_h( node_p->m_right_p );
}
