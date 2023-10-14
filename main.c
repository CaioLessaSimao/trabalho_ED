#include "image.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	image *pic = create(3,3,"P2");
	write_to_ppm(pic, "a.ppm");

	return 0;
}