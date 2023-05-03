#include "BMPheader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_sizeofImageData(bmpHeader mHeader)
{
    int size = 0;
    int height = 0;
    int width = 0;
    float multiplier = 0.0;

    size = *(int*)(mHeader.sizeofImage);

    if(size != 0)
    {
        return size;

    }
    else
    {
        size = *(int*)(mHeader.sizeOfFile) - *(int*)(mHeader.sizeofBMPInfoHeader);
        if (size != 0 )
        {
            return size;
        }
        else
        {
            width = *(int*)(mHeader.width);
            height = *(int*)(mHeader.height);
            switch (mHeader.bitsperPixel)
            {
            case 1:
                multiplier = 8;
                break;
            case 2:
                multiplier = 4;
                break;
            case 4:
                multiplier = 2;
                break;
            case 8:
                multiplier = 1;
                break;
            
            default:
                multiplier = 1;
                break;
            }
        }
    }

    size = width * height;
    size /= multiplier; 
    return size;
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

