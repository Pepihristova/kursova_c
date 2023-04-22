
#ifndef BMP_FUNCTIONALITY_H
#define BMP_FUNCTIONALITY_H

#include <stdio.h>
#include "BMPheader.h"

void** BMP_Image_data_handler(char* buffer, bmpHeader mHeader);
/*
void BMP_rotate(FILE ** Finput, FILE** Foutput);

void BMP_inverce();

void BMP_flip();
*/
#endif