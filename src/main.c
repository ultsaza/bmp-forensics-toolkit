#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "image_processing.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file.bmp> <output_file.bmp>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    // 入力BMPファイルを読み込む
    BMPImage *input_image = loadBMP(input_file);
    if (!input_image) {
        printf("Error: Could not load input file %s\n", input_file);
        return 1;
    }

    // 最下位ビットを抽出
    BMPImage *lsb_image = extractLSB(input_image);
    if (!lsb_image) {
        printf("Error: Failed to extract LSB\n");
        freeBMP(input_image);
        return 1;
    }

    // 結果を保存
    if (!saveBMP(output_file, lsb_image)) {
        printf("Error: Could not save output file %s\n", output_file);
        freeBMP(input_image);
        freeBMP(lsb_image);
        return 1;
    }

    printf("LSB extraction completed. Result saved to %s\n", output_file);

    // メモリ解放
    freeBMP(input_image);
    freeBMP(lsb_image);

    return 0;
}