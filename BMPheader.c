#include "BMPheader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_sizeofImageData(bmpHeader mHeader)
{
    return *(int*)(mHeader.sizeofImage);
}

void get_current_dimentions(bmpHeader* pHeader, int* width, int* height)
{
    *width = *(int*)(pHeader->width);
    *height = *(int*)(pHeader->height);
}

void input_dimentions(bmpHeader* pHeader, int width, int height){
    *(int *)(pHeader->width) = width;
    *(int *)(pHeader->height) = height;
}

char* bmp_header_offset(bmpHeader mHeader, int* p_offset)
{
    char* offset = NULL;
    int offsetToImageData = 0;
    
    offsetToImageData = *(int*)(mHeader.offsettoStartofImageData) - sizeof(bmpHeader);
    *p_offset = offsetToImageData;
    offset = (char*) malloc(offsetToImageData);
    return offset;
}

