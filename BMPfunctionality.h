
#ifndef BMP_FUNCTIONALITY_H
#define BMP_FUNCTIONALITY_H

#include <stdio.h>
#include "BMPheader.h"

void** BMP_Image_data_handler(char* buffer, bmpHeader mHeader);
int horizontal_flip(void** input,bmpHeader* pHeader);
void** rotate(void** input,bmpHeader* pHeader);
int Inverce(void** input,bmpHeader* pHeader);
/*

void BMP_inverce();

*/
#endif