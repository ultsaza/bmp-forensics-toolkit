#ifndef BMP_H
#define BMP_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPFileHeader;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
} BMPInfoHeader;
#pragma pack(pop)

typedef struct {
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    uint8_t *data;
} BMPImage;

BMPImage* loadBMP(const char *filename);
int saveBMP(const char *filename, BMPImage *image);
void freeBMP(BMPImage *image);

BMPImage* createBMPImage(int width, int height);

#endif // BMP_H
