#include "BMPheader.h"
#include "BMPfunctionality.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    int         height          = 0;
    int         width           = 0;
    int         size_of_image   = 0;
    int         size_of_file    = 0;
    FILE*       fbmp            = NULL;
    FILE*       mFile           = NULL;
    void**      ImageData       = NULL;
    bmpHeader*  pHeader         = NULL;
    char*       ImageFile       = NULL;
    char*       ImageDataOffset = NULL;
    int         offset          = 0;

    if(argc > 2)
    {
        fbmp = fopen(argv[1], "rb");
        if(fbmp == NULL){
            perror("file does not exist!\n");
            return -1;
        }
        mFile = fopen(argv[2], "wb");
        if(mFile == NULL){
            perror("file did not open!\n");
            return -1;
        }
    }
    else
    {
        printf("Input files!\n(Example: inputfile.bmp   outputfile.bmp)\n");
        return -1;
    }

    pHeader = (bmpHeader*) malloc(sizeof(bmpHeader));

    if(1 != fread(pHeader,sizeof(bmpHeader),1,fbmp))
    {
        printf("error 1 reading from file\n");
    }

    size_of_image = get_sizeofImageData(*pHeader);

    ImageDataOffset = bmp_header_offset(*pHeader, &offset);

    if(offset != fread(ImageDataOffset,sizeof(char),offset,fbmp))
    {
        printf("error 2 reading from file\n");
    }

    get_current_dimentions(pHeader,&width,&height);

    ImageFile = (char*) malloc(sizeof(char)* size_of_image);

    if(ImageFile != NULL)
    {
        fread(ImageFile,sizeof(char),size_of_image,fbmp);
    }

    ImageData = BMP_Image_data_handler(ImageFile, *pHeader);
//// main functions ////

    horizontal_flip(ImageData,pHeader);

    ImageData = rotate(ImageData,pHeader);

    Inverce(ImageData,pHeader);

//// main functions end ////
    get_current_dimentions(pHeader,&width,&height);

    fwrite(pHeader,sizeof(bmpHeader),1,mFile);

    fwrite(ImageDataOffset,sizeof(char),offset,mFile);

    int size = size_of_image/(height * width);

    char** Image = (char**)ImageData;

    char byte_value = 0x00;

    if(pHeader->bitsperPixel == 1)
    {
        for(int i = 0; i < height ; i ++)
        {
            for(int p = 0; p < width; )
            {
                for(int bit = 0; bit < 8; bit++, p++)
                {
                    byte_value = byte_value | ((Image[i][p] & 0x01) << 7 - bit); // 1000 0000
                }
                fwrite(&byte_value,sizeof(char),1,mFile);
                byte_value = 0x00;
            }
        }
    }
    else if(pHeader->bitsperPixel == 2)
    {
        for(int i = 0; i < height ; i ++)
        {
            for(int p = 0; p < width; )
            {
                for(int bit = 0; bit < 8; bit+=2, p++)
                {
                    byte_value = byte_value | ((Image[i][p] & 0x03) << 6 - bit); // 1000 0000
                }
                fwrite(&byte_value,sizeof(char),1,mFile);
                byte_value = 0x00;
            }
        }
    }
    else if(pHeader->bitsperPixel == 4)
    {
        for(int i = 0; i < height ; i ++)
        {
            for(int p = 0; p < width; )
            {
                for(int bit = 0; bit < 8; bit+=4, p++)
                {
                    byte_value = byte_value | ((Image[i][p] & 0x0f) << (4 - bit)); // 1000 0000
                }
                fwrite(&byte_value,sizeof(char),1,mFile);
                byte_value = 0x00;
            }
        }
    }
    else
    {
        for(int i = 0; i < height ; i ++)
        {
            for(int p = 0; p < width*size; p++)
            {
                fwrite(&Image[i][p],sizeof(char),1,mFile);
            }
        }   
    }

////////////////////////////////////////////
/// free
///////////////////////////////////////////

    free(pHeader);
    free(ImageDataOffset);
    for(int p = 0; p < height ; p++)
    {
        free(ImageData[p]);
    }
    free(ImageData);
    free(ImageFile);
    fclose(fbmp);
    fclose(mFile);
    return 0;
}