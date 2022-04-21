#ifndef INCLUDE
#define INCLUDE
#include "RLEList.h"
#endif // INCLUDE

#ifndef ASCIIARTTOOL_H
#define ASCIIARTTOOL_H
#include <stdio.h>

/**
* ASCII Art Tool
*
* Implements an ASCII Art Tool for creating images using ASCII symbols.
*
* The following functions are available:
*   asciiArtRead -         Reads the given file and compresses it using the RLE method.
*   asciiArtPrint -        Writes an image represented by a list of type RLEList to the file.
*   asciiArtPrintEncoded - Writes the image to the file in a compressed form in the format returned from
*                          RLEListExportToString.
*/


/**
* asciiArtRead: reads the given file and compresses it using the RLE method. 
* 
* @param in_stream - An object of type FILE* that contains the image you would like to compress.
* @return
*   NULL if allocation failed.
*   A list of the RLEList type that contains all the characters in the image.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
* asciiArtPrint: writes an image represented by a list of type RLEList to a file.
*
* @param list - A list of RLEList type  which contains all characters in the picture.
* @param out_stream - An object of type FILE* wherein the image will be written.
* @return
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
*   RLE_LIST_SUCCESS if the character has been inserted successfully
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* asciiArtPrintEncoded: writes the image to the file in a compressed form in the format returned from RLEListExportToString.
*
* @param list - A list of RLEList type which contains the characters in the picture.
* @param out_stream - An object of type FILE* wherein compressed image will be written.
* @return
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
*   RLE_LIST_SUCCESS if the image has been successfully written to the file
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // ASCIIARTTOOL_H