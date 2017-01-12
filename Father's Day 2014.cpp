// Father's Day 2014.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdint.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#include <iostream>

using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	cout << "----Welcome!----\n\n";
	system("pause");
	system("cls");

	cout << "We have a special for you today!\n\n";
	system("pause");
	system("cls");

	cout << "First, look at SecretMessage.bmp\nto see if you can decipher the message.\n\n";
	system("pause");
	system("cls");

	cout << "How did you do? Not so well, probably.\nNow CLOSE SecretMessage.bmp.\n\n";
	system("pause");
	system("cls");

	// remember filenames
    char* infile = "SecretMessage.bmp";
    char* outfile = "FathersDay.bmp";

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");

    srand(time(NULL));

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            //Get rid of noise.
            triple.rgbtRed = 0;
            triple.rgbtGreen = 0;
            

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

	cout << "TADA! Now OPEN the newly created file.\n\n";
	system("pause");
	system("cls");

    // that's all folks
    return 0;
}

