//========================================================================
// image-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for Image.

#include "Image.h"
#include "VectorInt.h"
#include "digits.dat"
#include <stdio.h>

int main()
{
  VectorInt vec( digit1_image, 28 * 28 );
  Image     img( vec, 28, 28 );
  img.set_label( digit1_label );

  printf( "Print the Image:\n" );
  img.print();

  printf( "Label of the image is %c\n", img.get_label() );

  return 0;
}
