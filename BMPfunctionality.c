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
            {
                pixel1b** mbuffer;

                mbuffer = (pixel1b**) malloc(height*sizeof(pixel1b*));

                for(int i = 0; i < height; i ++)
                {
                    mbuffer[i] = (pixel1b*) malloc(width*sizeof(pixel1b));
                }

                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; )
                    {
                        for(int bit = 0; bit < 8; bit++, p++)
                        {
                            mbuffer[i][p].value = 0x01 & (buffer[p/8 + (width/8) * i] >> (7 - bit));
                        }
                    }
                }
                return (void **)mbuffer;
            }
        case 2:
            {
                pixel2b** mbuffer;

                mbuffer = (pixel2b**) malloc(height*sizeof(pixel2b*));

                for(int i = 0; i < height; i ++)
                {
                    mbuffer[i] = (pixel2b*) malloc(width*sizeof(pixel2b));
                }

                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; )
                    {
                        for(int bit = 0; bit < 8; bit+=2, p++)
                        {
                            mbuffer[i][p].value = 0x03 & (buffer[p/4 + (width/4) * i] >> (6 - bit));
                        }
                    }
                }
                return (void **)mbuffer;
            }
        case 4:
            {
                pixel4b** mbuffer;

                mbuffer = (pixel4b**) malloc(height*sizeof(pixel4b*));

                for(int i = 0; i < height; i ++)
                {
                    mbuffer[i] = (pixel4b*) malloc(width*sizeof(pixel4b));
                }

                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; )
                    {
                        for(int bit = 0; bit < 8; bit+=4, p++)
                        {
                            mbuffer[i][p].value = 0x0f & (buffer[p/2 + (width/2) * i] >> (4 - bit));
                        }
                    }
                }
                return (void **)mbuffer;
            }
        case 8:
            {
                pixel8b** mbuffer;

                mbuffer = (pixel8b**) malloc(height*sizeof(pixel8b*));

                for(int i = 0; i < height; i ++)
                {
                    mbuffer[i] = (pixel8b*) malloc(width*sizeof(pixel8b));
                }

                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {   
                        //memcpy(&mbuffer[i][p],buffer+((height*i)+p),sizeof(pixel24b));
                        mbuffer[i][p].value = *(buffer+width*i+ p);
                    }
                }
                return (void **)mbuffer;
            }
        case 16:
            {
                pixel16b** mbuffer;

                mbuffer = (pixel16b**) malloc(height*sizeof(pixel16b*));

                for(int i = 0; i < height; i ++)
                {
                    mbuffer[i] = (pixel16b*) malloc(width*sizeof(pixel16b));
                }

                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {   
                        mbuffer[i][p].value   = 0x00ff & *(buffer+width*i*2+ p*2 + 0);

                        mbuffer[i][p].value  |= 0xff00 & (*(buffer+width*i*2+ p*2 + 1)) << 8;
                    }
                }
                return (void **)mbuffer;
            }
        case 24:
            {
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
            }
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
            {
                pixel1b** pBuffer = (pixel1b**)input;
                pixel1b temp;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width/2; p++)
                    {
                        memcpy(&temp,&pBuffer[i][p],sizeof(pixel1b));
                        memcpy(&pBuffer[i][p],&pBuffer[i][width-(1+p)],sizeof(pixel1b));
                        memcpy(&pBuffer[i][width-(1+p)],&temp,sizeof(pixel1b));
                    }
                }
            }
            break;
        case 2:
            {
                pixel2b** pBuffer = (pixel2b**)input;
                pixel2b temp;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width/2; p++)
                    {
                        memcpy(&temp,&pBuffer[i][p],sizeof(pixel2b));
                        memcpy(&pBuffer[i][p],&pBuffer[i][width-(1+p)],sizeof(pixel2b));
                        memcpy(&pBuffer[i][width-(1+p)],&temp,sizeof(pixel2b));
                    }
                }
            }
            break;
        case 4:
            {
                pixel4b** pBuffer = (pixel4b**)input;
                pixel4b temp;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width/2; p++)
                    {
                        memcpy(&temp,&pBuffer[i][p],sizeof(pixel4b));
                        memcpy(&pBuffer[i][p],&pBuffer[i][width-(1+p)],sizeof(pixel4b));
                        memcpy(&pBuffer[i][width-(1+p)],&temp,sizeof(pixel4b));
                    }
                }
            }
            break;
        case 8:
            {
                pixel8b** pBuffer = (pixel8b**)input;
                pixel8b temp;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width/2; p++)
                    {
                        memcpy(&temp,&pBuffer[i][p],sizeof(pixel8b));
                        memcpy(&pBuffer[i][p],&pBuffer[i][width-(1+p)],sizeof(pixel8b));
                        memcpy(&pBuffer[i][width-(1+p)],&temp,sizeof(pixel8b));
                    }
                }
            }
        break;
        case 16:
            {
                pixel16b** pBuffer = (pixel16b**)input;
                pixel16b temp;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width/2; p++)
                    {
                        memcpy(&temp,&pBuffer[i][p],sizeof(pixel16b));
                        memcpy(&pBuffer[i][p],&pBuffer[i][width-(1+p)],sizeof(pixel16b));
                        memcpy(&pBuffer[i][width-(1+p)],&temp,sizeof(pixel16b));
                    }
                }
            }
        break;
        case 24:
            {
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
            {
                pixel1b** pBuffer = (pixel1b**)input;
                pixel1b** Rbuffer = NULL;

                Rbuffer = (pixel1b**) malloc(width*sizeof(pixel1b*));
                for(int i = 0; i < width; i ++)
                {
                    Rbuffer[i] = (pixel1b*) malloc(height*sizeof(pixel1b));
                }

                for(int i = 0; i < width; i ++)
                {
                    for(int p = 0; p < height; p++)
                    {
                        memcpy(&Rbuffer[i][p],&pBuffer[p][width - 1 - i],sizeof(pixel1b));
                    }
                }

                for(int p = 0; p < height ; p++)
                {
                    free(pBuffer[p]);
                }
                free(pBuffer);

                return (void**)Rbuffer;
            }
        case 2:
            {
                pixel2b** pBuffer = (pixel2b**)input;
                pixel2b** Rbuffer = NULL;

                Rbuffer = (pixel2b**) malloc(width*sizeof(pixel2b*));
                for(int i = 0; i < width; i ++)
                {
                    Rbuffer[i] = (pixel2b*) malloc(height*sizeof(pixel2b));
                }

                for(int i = 0; i < width; i ++)
                {
                    for(int p = 0; p < height; p++)
                    {
                        memcpy(&Rbuffer[i][p],&pBuffer[p][width - 1 - i],sizeof(pixel2b));
                    }
                }

                for(int p = 0; p < height ; p++)
                {
                    free(pBuffer[p]);
                }
                free(pBuffer);

                return (void**)Rbuffer;
            }
        case 4:
            {
                pixel4b** pBuffer = (pixel4b**)input;
                pixel4b** Rbuffer = NULL;

                Rbuffer = (pixel4b**) malloc(width*sizeof(pixel4b*));
                for(int i = 0; i < width; i ++)
                {
                    Rbuffer[i] = (pixel4b*) malloc(height*sizeof(pixel4b));
                }

                for(int i = 0; i < width; i ++)
                {
                    for(int p = 0; p < height; p++)
                    {
                        memcpy(&Rbuffer[i][p],&pBuffer[p][width - 1 - i],sizeof(pixel4b));
                    }
                }

                for(int p = 0; p < height ; p++)
                {
                    free(pBuffer[p]);
                }
                free(pBuffer);

                return (void**)Rbuffer;
            }
        case 8:
            {
                pixel8b** pBuffer = (pixel8b**)input;
                pixel8b** Rbuffer = NULL;

                Rbuffer = (pixel8b**) malloc(width*sizeof(pixel8b*));
                for(int i = 0; i < width; i ++)
                {
                    Rbuffer[i] = (pixel8b*) malloc(height*sizeof(pixel8b));
                }

                for(int i = 0; i < width; i ++)
                {
                    for(int p = 0; p < height; p++)
                    {
                        memcpy(&Rbuffer[i][p],&pBuffer[p][width - 1 - i],sizeof(pixel8b));
                    }
                }

                for(int p = 0; p < height ; p++)
                {
                    free(pBuffer[p]);
                }
                free(pBuffer);

                return (void**)Rbuffer;
            }
        case 16:
            {
                pixel16b** pBuffer = (pixel16b**)input;
                pixel16b** Rbuffer = NULL;

                Rbuffer = (pixel16b**) malloc(width*sizeof(pixel16b*));
                for(int i = 0; i < width; i ++)
                {
                    Rbuffer[i] = (pixel16b*) malloc(height*sizeof(pixel16b));
                }

                for(int i = 0; i < width; i ++)
                {
                    for(int p = 0; p < height; p++)
                    {
                        memcpy(&Rbuffer[i][p],&pBuffer[p][width - 1 - i],sizeof(pixel16b));
                    }
                }

                for(int p = 0; p < height ; p++)
                {
                    free(pBuffer[p]);
                }
                free(pBuffer);

                return (void**)Rbuffer;
            }
        case 24:
            {
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
            }
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
            {
                pixel1b** pBuffer = (pixel1b**)input;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {
                        pBuffer[i][p].value = !pBuffer[i][p].value;
                    }
                }
            }
            break;
        case 2:
            {
                pixel2b** pBuffer = (pixel2b**)input;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {
                        pBuffer[i][p].value = 4 - pBuffer[i][p].value;
                    }
                }
            }
            break;
        case 4:
            {
                pixel4b** pBuffer = (pixel4b**)input;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {
                        pBuffer[i][p].value = 15 - pBuffer[i][p].value;
                    }
                }
            }
            break;
        case 8:
            {
                pixel8b** pBuffer = (pixel8b**)input;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {
                        pBuffer[i][p].value = 255 - pBuffer[i][p].value;
                    }
                }
            }
            break;
        case 16:
            {
                pixel16b** pBuffer = (pixel16b**)input;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {
                        pBuffer[i][p].color.blue_color    = 31 - pBuffer[i][p].color.blue_color;
                        pBuffer[i][p].color.green_color   = 63 - pBuffer[i][p].color.green_color;
                        pBuffer[i][p].color.red_color     = 31 - pBuffer[i][p].color.red_color;
                    }
                }
            }
            break;
        case 24:
            {
                pixel24b** pBuffer = (pixel24b**)input;
                for(int i = 0; i < height; i ++)
                {
                    for(int p = 0; p < width; p++)
                    {
                        pBuffer[i][p].blue_color    = 255 - pBuffer[i][p].blue_color;
                        pBuffer[i][p].green_color   = 255 - pBuffer[i][p].green_color;
                        pBuffer[i][p].red_color     = 255 - pBuffer[i][p].red_color;
                    }
                }
            }
            break;
        default:
        printf("error");
        return 1;
    }
}