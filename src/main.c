// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "image_processing.h"

void show_help(char *program_name);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_help(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "help") == 0) {
        show_help(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "overlay") == 0) {
        if (argc < 6) {
            printf("Error: Not enough arguments for overlay\n");
            show_help(argv[0]);
            return 1;
        }

        BMPImage *img1 = loadBMP(argv[3]);
        BMPImage *img2 = loadBMP(argv[4]);
        BMPImage *result = createBMPImage(img1->infoHeader.width, img1->infoHeader.height);

        if (strcmp(argv[2], "and") == 0) {
            imageAnd(img1, img2, result);
        } else if (strcmp(argv[2], "or") == 0) {
            imageOr(img1, img2, result);
        } else if (strcmp(argv[2], "xor") == 0) {
            imageXor(img1, img2, result);
        } else {
            printf("Error: Unknown overlay option %s\n", argv[2]);
            show_help(argv[0]);
            return 1;
        }

        saveBMP(argv[5], result);
        freeBMP(img1);
        freeBMP(img2);
        freeBMP(result);
        return 0;
    }

    if (strcmp(argv[1], "filter") == 0) {
        if (argc < 5) {
            printf("Error: Not enough arguments for filter\n");
            show_help(argv[0]);
            return 1;
        }

        BMPImage *img = loadBMP(argv[3]);
        BMPImage *result = createBMPImage(img->infoHeader.width, img->infoHeader.height);

        if (strcmp(argv[2], "smooth") == 0) {
            imageSmooth(img, result);
        } else if (strcmp(argv[2], "differential") == 0) {
            imageDifferential(img, result, 0);
        } else if (strcmp(argv[2], "laplacian") == 0) {
            imageLaplacian(img, result);
        } else {
            printf("Error: Unknown filter option %s\n", argv[2]);
            show_help(argv[0]);
            return 1;
        }

        saveBMP(argv[4], result);
        freeBMP(img);
        freeBMP(result);
        return 0;
    }

    if (strcmp(argv[1], "separate") == 0) {
        if (argc < 4) {
            printf("Error: Not enough arguments for separate\n");
            show_help(argv[0]);
            return 1;
        }

        BMPImage *img = loadBMP(argv[2]);
        BMPImage *red = createBMPImage(img->infoHeader.width, img->infoHeader.height);
        BMPImage *green = createBMPImage(img->infoHeader.width, img->infoHeader.height);
        BMPImage *blue = createBMPImage(img->infoHeader.width, img->infoHeader.height);

        imageSeparateRGB(img, red, green, blue);

        saveBMP("red.bmp", red);
        saveBMP("green.bmp", green);
        saveBMP("blue.bmp", blue);

        freeBMP(img);
        freeBMP(red);
        freeBMP(green);
        freeBMP(blue);
        return 0;
    }

    if (strcmp(argv[1], "extract") == 0) {
        if (argc < 5) {
            printf("Error: Not enough arguments for extract\n");
            show_help(argv[0]);
            return 1;
        }

        BMPImage *img = loadBMP(argv[2]);
        BMPImage *result = extractBit(img, atoi(argv[3]));

        saveBMP(argv[4], result);
        freeBMP(img);
        freeBMP(result);
        return 0;
    }

    else {
        printf("Error: Unknown command %s\n\n", argv[1]);
        show_help(argv[0]);
        return 1;
    }
}

void show_help(char* program_name) {
    printf("Usage: %s \033[31m[COMMAND]\033[0m\n\n", program_name);
    printf("Commands:\n");
    printf("  \033[31mhelp\033[0m\t\tShows this help message and exit\n");
    printf("  \033[31moverlay\033[0m \033[32mOPTION\033[0m \033[31mIMAGE_1 IMAGE_2 OUTPUT_NAME\033[0m\tOverlay the two specified images according to the options.\n");
    printf("  The options are: \033[32mand\033[0m, \033[32mor\033[0m, \033[32mxor\033[0m\n");
    printf("  \033[31mfilter\033[0m \033[32mOPTION\033[0m \033[31mIMAGE OUTPUT_NAME\033[0m\tApplies an optionally specified filter to the given image.\n");
    printf("  The options are: \033[32msmooth\033[0m, \033[32mdifferential\033[0m, \033[32mlaplacian\033[0m\n");
    printf("  \033[31mseparate IMAGE OUTPUT_NAME\033[0m\tSeparates the RGB channels of the given image.\n");
    printf("  \033[31mextract IMAGE BIT_POSITION OUTPUT_NAME\033[0m\tExtracts the specified bit from the given image.\n");
    printf("Example:\n");
    printf("  %s overlay and image1.bmp image2.bmp output.bmp\n", program_name);
}
