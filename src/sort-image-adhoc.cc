//========================================================================
// sort-image-adhoc.cc
//========================================================================

#include "Image.h"
#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include "sort-image.h"
#include <cstddef>
#include <cstdio>

int main()
{
  size_t size      = 4;
  int    data[][4] = {
      {19, 95, 4, 23}, {41, 42, 43, 44}, {1, 21, 200, 199}, {12, 22, 36, 87}};

  Image images[4];

  for ( size_t i = 0; i < size; i++ )
    images[i] = Image( VectorInt( data[i], 4 ), 1, 4 );

  // Print out array before

  std::printf( "Intensity before sorting: \n" );
  for ( size_t i = 0; i < size; i++ )
    std::printf( "%d ", images[i].get_intensity() );
  std::printf( "\n" );

  // Call sort_image

  sort_image( images, size );

  // Print out array after

  std::printf( "Intensity after sorting: \n" );
  for ( size_t i = 0; i < size; i++ )
    std::printf( "%d ", images[i].get_intensity() );
  std::printf( "\n" );

  return 0;
}
