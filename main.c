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

    ImageFile = (char*) malloc(sizeof(char)* size_of_image);

    if(ImageFile != NULL)
    {
        fread(ImageFile,sizeof(char),size_of_image,fbmp);
    }

    ImageData = BMP_Image_data_handler(ImageFile, *pHeader);

    fwrite(pHeader,sizeof(bmpHeader),1,mFile);

    fwrite(ImageDataOffset,sizeof(char),offset,mFile);

    if(pHeader->bitsperPixel == 24)
    {
        pixel24b** pBuffer = (pixel24b**)ImageData;
        char data;
        for(int i = 0;i < 1280; i ++)
        {
            for(int p = 0; p < 1920; p++)
            {
                fwrite(&pBuffer[i][p],sizeof(pixel24b),1,mFile);
            }
        }
    }

////////////////////////////////////////////
    free(pHeader);
    free(ImageDataOffset);
    for(int p = 0; p < width ; p++)
    {
        printf("%d\n", *((((pixel24b**)ImageData)+p)+p));
        free(ImageData[p]);
    }
    free(ImageData);
    free(ImageFile);
    fclose(fbmp);
    fclose(mFile);
    return 0;
}