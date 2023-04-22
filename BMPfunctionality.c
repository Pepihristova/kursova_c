#include "BMPfunctionality.h"
#include "BMPheader.h"
#include <stdlib.h>
#include <string.h>

void** BMP_Image_data_handler(char* buffer, bmpHeader mHeader)
{
    if(buffer == NULL)
    {
        return NULL;
    }

    int bits_per_pixel = mHeader.bitsperPixel;
    int height = *(int *)(mHeader.height);
    int width = *(int *)(mHeader.width);

    switch(bits_per_pixel)
    {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 24:
            pixel24b** mbuffer;

            mbuffer = (pixel24b**) malloc(height*sizeof(pixel24b*));

            for(int i = 0; i < height; i ++)
            {
                mbuffer[i] = (pixel24b*) malloc(width*sizeof(pixel24b));
            }

            for(int i = 0; i < height; i ++)
            {
                for(int p = 0; p < width; p++)
                {   
                    //memcpy(&mbuffer[i][p],buffer+((height*i)+p),sizeof(pixel24b));
                    mbuffer[i][p].blue_color  = *(buffer+width*i*3+ p*3 + 0);
                    mbuffer[i][p].green_color = *(buffer+width*i*3+ p*3 + 1);
                    mbuffer[i][p].red_color   = *(buffer+width*i*3+ p*3 + 2);
                }
            }
            return (void **)mbuffer;
        default:
        printf("error");
        return NULL;
    }
}

int horizontal_flip(void** input,bmpHeader* pHeader)
{
    if(input == NULL || pHeader == NULL)
    {
        return 1;
    }

    int bits_per_pixel = pHeader->bitsperPixel;
    int height = *(int *)(pHeader->height);
    int width = *(int *)(pHeader->width);

    switch(bits_per_pixel)
    {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 24:
            pixel24b** pBuffer = (pixel24b**)input;
            pixel24b temp;
            for(int i = 0; i < height; i ++)
            {
                for(int p = 0; p < width/2; p++)
                {
                    memcpy(&temp,&pBuffer[i][p],sizeof(pixel24b));
                    memcpy(&pBuffer[i][p],&pBuffer[i][width-(1+p)],sizeof(pixel24b));
                    memcpy(&pBuffer[i][width-(1+p)],&temp,sizeof(pixel24b));
                }
            }
        break;
        default:
        printf("error");
        return 1;
    }
}

void** rotate(void** input,bmpHeader* pHeader)
{
    if(input == NULL || pHeader == NULL)
    {
        return NULL;
    }

    int bits_per_pixel = pHeader->bitsperPixel;
    int height = *(int *)(pHeader->height);
    int width = *(int *)(pHeader->width);

    input_dimentions(pHeader, height, width);

    switch(bits_per_pixel)
    {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 24:
            pixel24b** pBuffer = (pixel24b**)input;
            pixel24b** Rbuffer = NULL;

            Rbuffer = (pixel24b**) malloc(width*sizeof(pixel24b*));
            for(int i = 0; i < width; i ++)
            {
                Rbuffer[i] = (pixel24b*) malloc(height*sizeof(pixel24b));
            }

            for(int i = 0; i < width; i ++)
            {
                for(int p = 0; p < height; p++)
                {
                    memcpy(&Rbuffer[i][p],&pBuffer[p][width - 1 - i],sizeof(pixel24b));
                }
            }

            for(int p = 0; p < height ; p++)
            {
                free(pBuffer[p]);
            }
            free(pBuffer);

            return (void**)Rbuffer;

        default:
        printf("error");
        return NULL;
    }
}

int Inverce(void** input,bmpHeader* pHeader)
{
   if(input == NULL || pHeader == NULL)
    {
        return 1;
    }

    int bits_per_pixel = pHeader->bitsperPixel;
    int height = *(int *)(pHeader->height);
    int width = *(int *)(pHeader->width);

    switch(bits_per_pixel)
    {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 24:
            pixel24b** pBuffer = (pixel24b**)input;
            int temp_blue;
            for(int i = 0; i < height; i ++)
            {
                for(int p = 0; p < width; p++)
                {
                    pBuffer[i][p].blue_color    = 255 - pBuffer[i][p].blue_color;
                    pBuffer[i][p].green_color   = 255 - pBuffer[i][p].green_color;
                    pBuffer[i][p].red_color     = 255 - pBuffer[i][p].red_color;
                }
            }
        break;
        default:
        printf("error");
        return 1;
    }
}