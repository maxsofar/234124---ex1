#include "AsciiArtTool.h"
#include "RLEList.h"
#include <string.h>

char invertFunction(char characterToBeInverted) {
    if (characterToBeInverted == '@') {
        return ' ';
    } else if (characterToBeInverted == ' ') {
        return '@';
    } else {
        return characterToBeInverted;
    }
}

/*
void error(char* message, char* filename) {
    printf("%s %s\n", message, filename ? filename : "");
}
*/

int main(int argc, char** argv) {
    /*
    if (argc != 4) {
        error("Usage: AsciiArtTool <flag> <source> <target>", NULL);
        return 0;
    }
    */

    FILE* source = fopen(argv[2], "r");
    /*
    if (!source) {
        error("Error: cannot open", argv[2]);
        return 0;
    }
    */

    FILE* target = fopen(argv[3], "w");
    /*
    if (!target) {
        fclose(source);
        error("Error: cannot open", argv[3]);
        return 0;
    }
    */

    RLEList list = asciiArtRead(source);

    if (strcmp(argv[1], "-e") == 0) {
        asciiArtPrintEncoded(list, target);
    } else if (strcmp(argv[1], "-i") == 0) {
        RLEListMap(list, &invertFunction);
        asciiArtPrint(list, target);
    }

    fclose(source);
    fclose(target);
    RLEListDestroy(list);

    return 0;
}