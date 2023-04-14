#include <stdio.h>
#include <stdlib.h>

typedef struct{
    short   BMP;
    char    sizeOfFile[4];
    char    reserved[4];
    char    offsettoStartofImageData[4];
    char    sizeofBMPInfoHeader[4]; // 40 
    char    width[4];
    char    height[4];
    short   planesCnt; // 1
    short   bitsperPixel; // 24
    char    compressionType[4];             // 0
    char    sizeofImage[4];                 // sizeOfFile - 54
    char    reserved_2[16];                 // reserved
}bmpHeader;

int main(){

    bmpHeader mHeader;
    int width = 1000;
    int height = 1000;

    FILE *fbmp = NULL;

    fbmp = fopen("image.bmp", "w");

    printf("size of header %d", sizeof(mHeader));

    mHeader.BMP = 0x4d42;
    *(int *)(mHeader.sizeOfFile) = 1000*1000 + 54;
    *(int *)(mHeader.reserved) = 0;
    *(int *)(mHeader.offsettoStartofImageData) = 0;
    *(int *)(mHeader.sizeofBMPInfoHeader) = 40;
    *(int *)(mHeader.width) = 1000;
    *(int *)(mHeader.height) = 1000;
    mHeader.planesCnt = 1;
    mHeader.bitsperPixel = 24;
    *(int *)(mHeader.compressionType) = 0;
    *(int *)(mHeader.sizeofImage) = 1000*1000;
    *(long double *)(mHeader.reserved_2) = 0x0000000000000000;

    fwrite(&mHeader,54,1,fbmp);

    char pixel[3];

    for(int i=0; i < 1000 ; i ++){
        for( int p = 0; p < 1000; p++){
            pixel[0] = 255;//blue
            pixel[1] =  0;//green
            pixel[2] = 0;//red
            fwrite(pixel,1,3,fbmp);
        }
    }

    fclose(fbmp);

    return 0;


}