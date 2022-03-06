//========================================================================
// HRSAlternative.cc
//========================================================================
// Alternative HRS implementation.

#include "HRSAlternative.h"

#include "IHandwritingRecSys.h"
#include "Image.h"
#include "Vector.h"
#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <thread>



//------------------------------------------------------------------------
// HRSLinearSearch::HRSLinearSearch
//------------------------------------------------------------------------
// Default constructor for HRSLinearSearch.
HRSAlternative::HRSAlternative()
{
  // private member variable already initialized by its own class
}



//------------------------------------------------------------------------
// HRSLinearSearch::train
//------------------------------------------------------------------------
// Train the HRS. For HRSLinearSearch
void HRSAlternative::train( const Vector<Image>& vec )
{
  // uses operator = overload to copy data from vec
  m_Avector = vec;
}


//------------------------------------------------------------------------
// free_find_closest
//------------------------------------------------------------------------
// free function used to help find the closest value using threads.
// this function will be passed into the std::threads function in classify
void free_find_closest( Vector<Image>* vec, const Image* img, size_t begin,
                        size_t end, Vector<Image>* result, size_t i )
{
  ( *result )[i] =
      vec->find_closest_alternative( *img, distance_euclidean, begin, end );
}



//------------------------------------------------------------------------
// HRSLinearSearch::classify
//------------------------------------------------------------------------
// Classify the given image. This function searchs through the entire
// training set and return the image that has the smallest euclidean
// distance from the given image.
Image HRSAlternative::classify( const Image& img )
{
  // sets the size and splits the size up into quarters for
  // use in the threads and free function
  size_t size     = m_Avector.size();
  size_t quarter1 = size / 4;
  size_t quarter2 = size / 2;
  size_t quarter3 = ( 3 * size ) / 4;
  size_t end      = size;


  // creates a default vector of 4 images but creating a
  // new Vector<Image> and pushes in 4 default images
  Vector<Image> result;
  result.push_back( Image() );
  result.push_back( Image() );
  result.push_back( Image() );
  result.push_back( Image() );


  // does a linear search of the vector if there are 4 or less images
  if ( m_Avector.size() <= 4 ) {
    m_Avector.find_closest( img, distance_euclidean );
  }

  // splits the function into 4 processes and runs them all at the same time
  std::thread A( free_find_closest, &m_Avector, &img, 0, quarter1, &result, 0 );
  std::thread B( free_find_closest, &m_Avector, &img, quarter1, quarter2,
                 &result, 1 );
  std::thread C( free_find_closest, &m_Avector, &img, quarter2, quarter3,
                 &result, 2 );
  free_find_closest( &m_Avector, &img, quarter3, end, &result, 3 );

 // waits until all 3 threads sync up with the main thread
  A.join();
  B.join();
  C.join();

  // does a linear search of the 4 images inside this new
  // Vector<Image> to find the closest
  return result.find_closest( img, distance_euclidean );
}