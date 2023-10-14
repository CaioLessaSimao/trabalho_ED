#ifndef IMAGE_H
#define IMAGE_H

typedef struct image_struct image;
/**
* Creates a new image.
*
* @param rows The number of rows (height) of the image.
3
* @param cols The number of columns (width) of the image.
* @param type The PPM type ("P2" for grayscale or "P3" for color).
* @return A pointer to the newly created image.
*/
image* create(int rows, int cols, const char type[]);
/**
* Loads an image from a PPM file.
*
* @param filename The name of the PPM file to load.
* @return A pointer to the loaded image.
*/
image* load_from_ppm(const char* filename);
/**
* Writes an image to a PPM file.
*
* @param image The image to write to the file.
* @param filename The name of the PPM file to write.
*/
void write_to_ppm(image* image, const char* filename);
/**
* Converts an RGB image to grayscale.
*
* @param image_rgb The input RGB image to convert.
* @param image_gray The output grayscale image where the result is
stored.
*/
void rgb_to_gray(image* image_rgb, image* image_gray);
#endif