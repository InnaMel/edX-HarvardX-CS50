/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember coefficient and filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check n - must be between 0 and 100
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Usage: n must be between 0 and 100(including)\n");
        return 4;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for old scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    BITMAPFILEHEADER outf;
    BITMAPINFOHEADER outi;
    outf = bf;
    outi = bi;

    //change BFH and BIH for new file
    outi.biWidth = bi.biWidth * n;
    // determine padding for  new scanlines
    int newPadding = (4 - (outi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    outi.biHeight = bi.biHeight * n;
    outi.biSizeImage =
        abs(outi.biHeight) * (outi.biWidth * sizeof(RGBTRIPLE) + newPadding);

    outf.bfSize =
        outi.biSizeImage + sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER);

    //writing BFH and BIH in outfile
    fwrite(&outf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&outi, sizeof(BITMAPINFOHEADER), 1, outptr);

    fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER),
          SEEK_SET);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //asking memory for 1 triple
        RGBTRIPLE oldSLTriple[bi.biWidth];
        fread(oldSLTriple, sizeof(RGBTRIPLE), bi.biWidth, inptr);
        RGBTRIPLE newSLTriple[outi.biWidth];
        printf("inptr is %ld", ftell(inptr));
        printf("\n");
        printf("outptr is %ld", ftell(outptr));
        printf("\n");
        printf("**************\n");

        int p = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {

            //Horizontal scanline. Without padding
            for (int l = 0; l < n; l++)
            {
                newSLTriple[p++] = oldSLTriple[j];
            }
        }
        size_t rezWriteOut =
            fwrite(newSLTriple, sizeof(RGBTRIPLE), outi.biWidth, outptr);
        printf("rezWriteOut %zu\n", rezWriteOut);

        if (rezWriteOut == 0)
        {
            printf("rezWriteOut = 0\n");
        }
        printf("newSLTriple in outptr is %ld", ftell(outptr));
        printf("\n");
        printf("**************\n");

        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }
        printf("put padding in outptr %ld", ftell(outptr));
        printf("\n");
        printf("**************\n");

        //Filling vertically
        for (int l = 0; l < n - 1; l++)
        {
            fwrite(newSLTriple, sizeof(RGBTRIPLE), bi.biWidth * n, outptr);
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        fseek(inptr, padding, SEEK_CUR);
        printf("inptr+padding is %ld", ftell(inptr));
        printf("\n");
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
