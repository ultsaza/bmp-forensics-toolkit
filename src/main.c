#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "image_processing.h"

void printUsage(const char* programName) {
    printf("Usage:\n");
    printf("%s rgb <input_file.bmp> <output_prefix>\n", programName);
    printf("%s extract-bit <input_file.bmp> <output_file.bmp> <bit_position>\n", programName);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printUsage(argv[0]);
        return 1;
    }

    const char *command = argv[1];
    const char *input_file = argv[2];

    BMPImage *input_image = loadBMP(input_file);
    if (!input_image) {
        printf("Error: Could not load input file %s\n", input_file);
        return 1;
    }

    if (strcmp(command, "rgb") == 0) {
        if (argc != 4) {
            printUsage(argv[0]);
            freeBMP(input_image);
            return 1;
        }

        const char *output_prefix = argv[3];
        char output_file[256];

        BMPImage *red = loadBMP(input_file);
        BMPImage *green = loadBMP(input_file);
        BMPImage *blue = loadBMP(input_file);

        separateRGB(input_image, red, green, blue);

        snprintf(output_file, sizeof(output_file), "%s_red.bmp", output_prefix);
        saveBMP(output_file, red);

        snprintf(output_file, sizeof(output_file), "%s_green.bmp", output_prefix);
        saveBMP(output_file, green);

        snprintf(output_file, sizeof(output_file), "%s_blue.bmp", output_prefix);
        saveBMP(output_file, blue);

        printf("RGB separation completed. Results saved with prefix %s\n", output_prefix);

        freeBMP(red);
        freeBMP(green);
        freeBMP(blue);
    }
    else if (strcmp(command, "extract-bit") == 0) {
        if (argc != 5) {
            printUsage(argv[0]);
            freeBMP(input_image);
            return 1;
        }

        const char *output_file = argv[3];
        int bit_position = atoi(argv[4]);

        BMPImage *bit_image = extractBit(input_image, bit_position);
        if (!bit_image) {
            printf("Error: Failed to extract bit\n");
            freeBMP(input_image);
            return 1;
        }

        if (!saveBMP(output_file, bit_image)) {
            printf("Error: Could not save output file %s\n", output_file);
            freeBMP(input_image);
            freeBMP(bit_image);
            return 1;
        }

        printf("Bit extraction completed. Result saved to %s\n", output_file);

        freeBMP(bit_image);
    }
    else {
        printf("Unknown command: %s\n", command);
        printUsage(argv[0]);
        freeBMP(input_image);
        return 1;
    }

    freeBMP(input_image);
    return 0;
}