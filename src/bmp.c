#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

BMPImage* loadBMP(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Debug: Failed to open file %s\n", filename);
        return NULL;
    }

    BMPImage *image = (BMPImage*)malloc(sizeof(BMPImage));
    
    fread(&image->fileHeader, sizeof(BMPFileHeader), 1, file);
    fread(&image->infoHeader, sizeof(BMPInfoHeader), 1, file);

    if (image->infoHeader.bitsPerPixel != 24) {
        printf("Debug: File %s is not a 24-bit BMP (actual bits per pixel: %d)\n", 
               filename, image->infoHeader.bitsPerPixel);
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

BMPImage* createBMPImage(int width, int height) {
    BMPImage *image = (BMPImage*)malloc(sizeof(BMPImage));
    if (!image) return NULL;

    // ファイルヘッダの設定
    image->fileHeader.type = 0x4D42;  // "BM"
    image->fileHeader.size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * height * 3;
    image->fileHeader.reserved1 = 0;
    image->fileHeader.reserved2 = 0;
    image->fileHeader.offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    // 情報ヘッダの設定
    image->infoHeader.size = sizeof(BMPInfoHeader);
    image->infoHeader.width = width;
    image->infoHeader.height = height;
    image->infoHeader.planes = 1;
    image->infoHeader.bitsPerPixel = 24;
    image->infoHeader.compression = 0;
    image->infoHeader.imageSize = width * height * 3;
    image->infoHeader.xPixelsPerMeter = 0;
    image->infoHeader.yPixelsPerMeter = 0;
    image->infoHeader.colorsUsed = 0;
    image->infoHeader.colorsImportant = 0;

    // 画像データ用のメモリ割り当て
    image->data = (uint8_t*)calloc(width * height * 3, sizeof(uint8_t));
    if (!image->data) {
        free(image);
        return NULL;
    }

    return image;
}
