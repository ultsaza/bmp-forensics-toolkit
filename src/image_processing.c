#include "image_processing.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 論理演算関数の実装
void imageAnd(BMPImage *img1, BMPImage *img2, BMPImage *result) {
    int size = img1->infoHeader.width * img1->infoHeader.height * 3;
    for (int i = 0; i < size; i++) {
        result->data[i] = img1->data[i] & img2->data[i];
    }
}

void imageOr(BMPImage *img1, BMPImage *img2, BMPImage *result) {
    int size = img1->infoHeader.width * img1->infoHeader.height * 3;
    for (int i = 0; i < size; i++) {
        result->data[i] = img1->data[i] | img2->data[i];
    }
}

void imageXor(BMPImage *img1, BMPImage *img2, BMPImage *result) {
    int size = img1->infoHeader.width * img1->infoHeader.height * 3;
    for (int i = 0; i < size; i++) {
        result->data[i] = img1->data[i] ^ img2->data[i];
    }
}

// 平滑化フィルタ
void imageSmooth(BMPImage *img, BMPImage *result) {
    int width = img->infoHeader.width;
    int height = img->infoHeader.height;
    int stride = width * 3;

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < 3; c++) {
                int sum = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        sum += img->data[(y + dy) * stride + (x + dx) * 3 + c];
                    }
                }
                result->data[y * stride + x * 3 + c] = sum / 9;
            }
        }
    }
}

// 微分フィルタ (簡易版: Sobel)
void imageDifferential(BMPImage *img, BMPImage *result, int direction) {
    int width = img->infoHeader.width;
    int height = img->infoHeader.height;
    int stride = width * 3;

    int kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < 3; c++) {
                int sum = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int pixel = img->data[(y + dy) * stride + (x + dx) * 3 + c];
                        sum += pixel * (direction == 0 ? kernelX[dy+1][dx+1] : kernelY[dy+1][dx+1]);
                    }
                }
                result->data[y * stride + x * 3 + c] = abs(sum) > 255 ? 255 : abs(sum);
            }
        }
    }
}

// ラプラシアンフィルタ
void imageLaplacian(BMPImage *img, BMPImage *result) {
    int width = img->infoHeader.width;
    int height = img->infoHeader.height;
    int stride = width * 3;

    int kernel[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            for (int c = 0; c < 3; c++) {
                int sum = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        sum += img->data[(y + dy) * stride + (x + dx) * 3 + c] * kernel[dy+1][dx+1];
                    }
                }
                result->data[y * stride + x * 3 + c] = abs(sum) > 255 ? 255 : abs(sum);
            }
        }
    }
}

BMPImage* extractLSB(BMPImage *img) {
    if (!img || !img->data) return NULL;

    BMPImage *result = (BMPImage*)malloc(sizeof(BMPImage));
    if (!result) return NULL;

    // ヘッダ情報をコピー
    memcpy(&result->fileHeader, &img->fileHeader, sizeof(BMPFileHeader));
    memcpy(&result->infoHeader, &img->infoHeader, sizeof(BMPInfoHeader));

    int width = img->infoHeader.width;
    int height = img->infoHeader.height;
    int size = width * height * 3;  // 24-bit BMPを想定

    result->data = (uint8_t*)malloc(size);
    if (!result->data) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        // 最下位ビットを抽出し、それを新しい画像の対応するバイトの最上位ビットにセット
        result->data[i] = (img->data[i] & 0x01) ? 0xFF : 0x00;
    }

    return result;
}
