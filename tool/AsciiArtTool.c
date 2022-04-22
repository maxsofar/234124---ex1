#include "RLEList.h"
#include "AsciiArtTool.h"

struct RLEList_t{
    char character;
    int numOfRepetitions;
    RLEList previous;
    RLEList next;
};

RLEList asciiArtRead(FILE* in_stream) {
    RLEList newList = RLEListCreate();
    if (newList == NULL) {
        return NULL;
    }

    char buffer;

    while ((fscanf(in_stream, "%c", &buffer)) != EOF) {
        RLEListAppend(newList, buffer);
    }
    return newList;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    list = list->next;       //
    while(list != NULL) {
        for (int i = 0; i < list->numOfRepetitions; ++i) {
            fprintf(out_stream, "%c", list->character);
        }
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) {
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char* str = RLEListExportToString(list, NULL);

    fprintf(out_stream, "%s", str);
    return RLE_LIST_SUCCESS;
}