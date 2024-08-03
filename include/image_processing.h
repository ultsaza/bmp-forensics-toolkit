#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "bmp.h"

// 論理演算関数
void imageAnd(BMPImage *img1, BMPImage *img2, BMPImage *result);
void imageOr(BMPImage *img1, BMPImage *img2, BMPImage *result);
void imageXor(BMPImage *img1, BMPImage *img2, BMPImage *result);

// フィルタ関数
void imageSmooth(BMPImage *img, BMPImage *result);
void imageDifferential(BMPImage *img, BMPImage *result, int direction);
void imageLaplacian(BMPImage *img, BMPImage *result);

// RGB分離関数
void separateRGB(BMPImage *img, BMPImage *red, BMPImage *green, BMPImage *blue);

// 指定ビット抽出関数（既存の extractLSB を置き換え）
BMPImage* extractBit(BMPImage *img, int bitPosition);

#endif // IMAGE_PROCESSING_H
