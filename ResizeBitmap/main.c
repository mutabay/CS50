#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bmp.h"


int main(int argc, char *argv[]) {
    //enter correct usage
    if (argc != 4) {
        fprintf(stderr, "Usage: resize ratio infile outfile\n");
        return 1;
    }

    int resizeRate = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    //open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr) {
        fprintf(stderr, "%s coulnd't opened for reading\n", infile);
        return 2;
    }

    //open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr) {
        fprintf(stderr, "%s coulnd't opened for writing\n", outfile);
        return 3;
    }

    //read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    //read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //determine new sizes
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int newWidth = bi.biWidth * resizeRate;
    int newHeight = bi.biHeight * resizeRate;

    // determine padding for scanlines
    int inPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //reform bitmap headers
    bi.biHeight = newHeight;
    bi.biWidth = newWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth + outPadding) * abs(newHeight));

    //allocating a memory for storing one scanline
    RGBTRIPLE scanline[newWidth * sizeof(RGBTRIPLE)];

    //write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(RGBTRIPLE), 1, outptr);

    //write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(RGBTRIPLE), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++) {
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++) {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            //create a new scanline in a temporary array
            for (int k = 0; k < resizeRate; ++k) {
                scanline[(j * resizeRate) + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, inPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int j = 0; j < resizeRate; j++) {
            // write a new scanline once
            fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

            // write new padding
            for (int k = 0; k < outPadding; k++) {
                fputc(0x00, outptr);
            }
        }
    }

    //close infile and outfile
    fclose(inptr);
    fclose(outptr);


    return 0;
}