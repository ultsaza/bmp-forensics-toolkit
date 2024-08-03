// main.c
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "image_processing.h"

void testLogicalOperations(BMPImage *input) {
    BMPImage *input2 = loadBMP("myicon.bmp");  // 同じ画像を使用
    BMPImage *result = createBMPImage(input->infoHeader.width, input->infoHeader.height);

    imageAnd(input, input2, result);
    saveBMP("output_and.bmp", result);

    imageOr(input, input2, result);
    saveBMP("output_or.bmp", result);

    imageXor(input, input2, result);
    saveBMP("output_xor.bmp", result);

    freeBMP(input2);
    freeBMP(result);
}

void testFilters(BMPImage *input) {
    BMPImage *result = createBMPImage(input->infoHeader.width, input->infoHeader.height);

    imageSmooth(input, result);
    saveBMP("output_smooth.bmp", result);

    imageDifferential(input, result, 0);  // X方向
    saveBMP("output_differential_x.bmp", result);

    imageDifferential(input, result, 1);  // Y方向
    saveBMP("output_differential_y.bmp", result);

    imageLaplacian(input, result);
    saveBMP("output_laplacian.bmp", result);

    freeBMP(result);
}

void testLSBExtraction(BMPImage *input) {
    BMPImage *lsb = extractBit(input, 0);
    saveBMP("output_lsb.bmp", lsb);
    freeBMP(lsb);
}

int main() {
    const char *input_file = "myicon.bmp";
    
    BMPImage *input = loadBMP(input_file);
    if (!input) {
        printf("Error: Could not load input file %s\n", input_file);
        return 1;
    }

    printf("Testing logical operations...\n");
    testLogicalOperations(input);

    printf("Testing filters...\n");
    testFilters(input);

    printf("Testing LSB extraction...\n");
    testLSBExtraction(input);

    printf("All tests completed. Check output files for results.\n");

    freeBMP(input);
    return 0;
}