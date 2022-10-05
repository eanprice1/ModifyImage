#include <iostream>
#include<stdio.h>
#include<string>
#include <vector>
#pragma warning(disable : 4996)

int main()
{
    const size_t numCols = 750;
    const size_t numRows = 500;
    FILE* pFile = fopen("./OriginalImage.raw", "rb");
    FILE* pReversedFile = fopen("./ReversedImage.raw", "wb");
    FILE* pAdd128File = fopen("./Added128Image.raw", "wb");
    FILE* pAdd20File = fopen("./Added20Image.raw", "wb");

    if (pFile) {
        std::cout << "Opened successfully" << std::endl;

        unsigned char buffer[numCols][numRows];
        unsigned char modifiedPixels[numCols][numRows];

        int elementsRead = fread(buffer, sizeof(unsigned char), numCols * numRows, pFile);
        std::cout << "Count of elements read: " << elementsRead << std::endl;

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                modifiedPixels[j][i] = 255 - buffer[j][i];
            }
        }
        fwrite(modifiedPixels, sizeof(unsigned char), numCols * numRows, pReversedFile);
        std::cout << "Completed reversing image" << std::endl;

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                modifiedPixels[j][i] = buffer[j][i] + 128;
            }
        }
        fwrite(modifiedPixels, sizeof(unsigned char), numCols * numRows, pAdd128File);
        std::cout << "Completed adding 128 to each pixel in the image" << std::endl;

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                modifiedPixels[j][i] = buffer[j][i] + 20;
            }
        }
        fwrite(modifiedPixels, sizeof(unsigned char), numCols * numRows, pAdd20File);
        std::cout << "Completed adding 20 to each pixel in the image" << std::endl;

        fcloseall();
        std::cout << "Files closed" << std::endl;
    }
    else {
        std::cout << "File does not exist or incorrect filepath";
    }
}


