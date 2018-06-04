#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <cs50.h>
#include <stdint.h>

//#include "structJPG.h"
#define  sizeJpgBlock 512


typedef uint8_t BYTE;
typedef struct _JFIFHeader
{
    BYTE SOI[2];                /* 00h  Start of Image Marker     */
    BYTE APP0[2];               /* 02h  Application Use Marker    */
    BYTE Length[2];             /* 04h  Length of APP0 Field      */
    BYTE Identifier[5];         /* 06h  "JFIF" (zero terminated) Id String */
    BYTE Version[2];            /* 07h  JFIF Format Revision      */
    BYTE Units;                 /* 09h  Units used for Resolution */
    BYTE Xdensity[2];           /* 0Ah  Horizontal Resolution     */
    BYTE Ydensity[2];           /* 0Ch  Vertical Resolution       */
    BYTE XThumbnail;            /* 0Eh  Horizontal Pixel Count    */
    BYTE YThumbnail;            /* 0Fh  Vertical Pixel Count      */
} JFIFHEAD;

bool compare(JFIFHEAD *oneJpgSTR);

int main(int argc, char *argv[])
{
    int numberJpg = 0;
    char filename[8];
    bool found = false;
    sprintf(filename, "%03i.jpg", numberJpg);
    FILE *img = fopen(filename, "w");
    int frd = 0;


    if ((argc != 2) || (strcmp(argv[1], "card.raw") != 0))
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *recFile = fopen(argv[1], "r");
    if (recFile == NULL)
    {
        fprintf(stderr, "Your file can not opened\n");
        return 2;
    }

    // getting memory for look for the signature of jpg
    JFIFHEAD *oneJpgSTR = NULL;

    // getting memory for look for the end of card
    void *buff = malloc(sizeJpgBlock);
    if (buff == NULL)
    {
        printf("Memory for buff is not highlighted \n");
    }


    do
    {
        frd = fread(buff, 1, 512, recFile);
        printf("From file in buff %i \n", frd);
        if (frd != 512)
        {
            break;
        }

        oneJpgSTR = (JFIFHEAD *) buff;

        if (compare(oneJpgSTR) == true && found == false)
        {
            fwrite(oneJpgSTR, sizeJpgBlock, 1, img);
            found = true;

        }
        else
        {
            if (!compare(oneJpgSTR) && found == true)
            {
                fwrite(oneJpgSTR, sizeJpgBlock, 1, img);
            }
            else if (compare(oneJpgSTR) && found == true)
            {
                numberJpg++;
                fclose(img);
                sprintf(filename, "%03i.jpg", numberJpg);
                img = fopen(filename, "w");
                fwrite(oneJpgSTR, sizeJpgBlock, 1, img);
            }
        }
    }
    while (frd == sizeJpgBlock);
    fclose(img);
    free(oneJpgSTR);
    fclose(recFile);
    return 0;
}

bool compare(JFIFHEAD *oneJpgSTR)
{
    bool rezCompare;
    if (oneJpgSTR->SOI[0] == 0xff && oneJpgSTR->SOI[1] == 0xd8
        && oneJpgSTR->APP0[0] == 0xff && (oneJpgSTR->APP0[1] & 0xf0) == 0xe0)
    {
        rezCompare = true;
    }
    else
    {
        rezCompare = false;
    }
    return rezCompare;
}
