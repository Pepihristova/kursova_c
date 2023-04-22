#ifndef BMP_HEADER_H
#define BMP_HEADER_H
#include <stdio.h>

typedef struct
{
    char pixel;
}pixel8b;

typedef union
{
    short size;
    struct{
        unsigned short blue : 5;
        unsigned short green : 6;
        unsigned short red : 5;
    }color;
}pixel16p;

typedef struct
{
    char blue_color;
    char green_color;
    char red_color;
}pixel24b;

typedef struct
{
    short   BMP;
    char    sizeOfFile[4];
    char    reserved[4];
    char    offsettoStartofImageData[4]; //138
    char    sizeofBMPInfoHeader[4]; // 40 124
    char    width[4];
    char    height[4];
    short   planesCnt; // 1
    short   bitsperPixel; // 24
    char    compressionType[4];             // 0
    char    sizeofImage[4];
}bmpHeader;

void input_dimentions(bmpHeader* pHeader, int width, int height);

void get_current_dimentions(bmpHeader* pHeader, int* width, int* height);

char* bmp_header_offset(bmpHeader mHeader,int* p_offset);

int get_sizeofImageData(bmpHeader mHeader);

#endif
