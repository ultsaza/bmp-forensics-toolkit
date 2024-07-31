#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

BMPImage* loadBMP(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    BMPImage *image = (BMPImage*)malloc(sizeof(BMPImage));
    
    fread(&image->fileHeader, sizeof(BMPFileHeader), 1, file);
    fread(&image->infoHeader, sizeof(BMPInfoHeader), 1, file);

    if (image->infoHeader.bitsPerPixel != 24) {
        fclose(file);
        free(image);
        return NULL;
    }

    int dataSize = image->infoHeader.width * image->infoHeader.height * 3;
    image->data = (uint8_t*)malloc(dataSize);
    fseek(file, image->fileHeader.offset, SEEK_SET);
    fread(image->data, dataSize, 1, file);

    fclose(file);
    return image;
}

int saveBMP(const char *filename, BMPImage *image) {
    FILE *file = fopen(filename, "wb");
    if (!file) return 0;

    fwrite(&image->fileHeader, sizeof(BMPFileHeader), 1, file);
    fwrite(&image->infoHeader, sizeof(BMPInfoHeader), 1, file);

    int dataSize = image->infoHeader.width * image->infoHeader.height * 3;
    fseek(file, image->fileHeader.offset, SEEK_SET);
    fwrite(image->data, dataSize, 1, file);

    fclose(file);
    return 1;
}

void freeBMP(BMPImage *image) {
    if (image) {
        if (image->data) free(image->data);
        free(image);
    }
}
