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
