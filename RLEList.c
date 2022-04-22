#include "tool/RLEList.h"
#include <stdlib.h>
#include <string.h>

struct RLEList_t{
    char character;
    int numOfRepetitions;
    RLEList previous;
    RLEList next;
};

RLEList RLEListCreate() {
    RLEList newList = malloc(sizeof(*newList));
    if(!newList) {
        return NULL;
    }
    newList->character = '\0';
    newList->numOfRepetitions = 0;
    newList->previous = NULL;
    newList->next = NULL;
    return newList;
}

void RLEListDestroy(RLEList list) {
    RLEList toRemove;
    while (list != NULL) {
        toRemove = list;
        list = list->next;
        free(toRemove);
    }
}

RLEListResult RLEListAppend(RLEList list, char value) {
    if (list == NULL || value == '\0') {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list->next != NULL) {
        list = list->next;
    }

    if (list->character == value) {
        ++list->numOfRepetitions;
        return RLE_LIST_SUCCESS;
    } else {
        RLEList newList = RLEListCreate();
        if (newList == NULL) {
            return RLE_LIST_OUT_OF_MEMORY;
        }

        list->next = newList;
        newList->previous = list;
        newList->character = value;
        ++newList->numOfRepetitions;
        return RLE_LIST_SUCCESS;
    }
}

int RLEListSize(RLEList list) {
    if (list == NULL) {
        return -1;
    }

    int counter = 0;
    while (list != NULL) {
        counter += list->numOfRepetitions;
        list = list->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index) {
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    ++index; //starts from 0
    int counter = 0;

    while (list != NULL) {
        counter += list->numOfRepetitions;

        if (counter > index)
        {
            --list->numOfRepetitions;
            return RLE_LIST_SUCCESS;
        }
        else if (counter == index)
        {
            if (list->previous->character != '\0') {
                list->previous->next = list->next;
                if (list->next != NULL) {
                    list->next->previous = list->previous;
                }
                free(list);
            } else {
                if (list->next != NULL) {
                    list->next->previous = list->previous;
                }
                list->previous->next = list->next;
                free(list);
            }
            return RLE_LIST_SUCCESS;
        }
        list = list->next;
    }
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result) {
    if (list == NULL) {
        if (result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    if (index < 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    ++index; //starts from zero
    int counter = 0;
    while (list != NULL) {
        counter += list->numOfRepetitions;
        if (counter >= index) {
            if (result != NULL) {
                *result = RLE_LIST_SUCCESS;
            }
            return list->character;
        }
        list = list->next;
    }
    if (result != NULL) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    return 0;
}

static int intToStr(char* destinationStr, int numOfRepetitions) {
    int count = 0;
    sprintf(destinationStr,"%d",numOfRepetitions);

    do {
        numOfRepetitions /= 10;
        ++count;
    } while (numOfRepetitions != 0);
    return count;
}

char* RLEListExportToStr(RLEList list, RLEListResult* result) {
    if (list == NULL) {
        if (result != NULL) {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }

    int listSize = RLEListSize(list);

    //(?)worst case: every letter appears once - no RLE compression
    char* str = malloc(sizeof(char) * listSize * 3 + 1);

    if (str == NULL) {
        return NULL;
    }

    char* strHead = str;
    list = list->next;

    while (list != NULL) {
        *strHead = list->character;
        ++strHead;
        strHead += intToStr(strHead, list->numOfRepetitions);
        *strHead = '\n';
        ++strHead;
        list = list->next;
    }
    *strHead = '\0';
    if (result != NULL) {
        *result = RLE_LIST_SUCCESS;
    }
    return str;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    if (list == NULL || map_function == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    list = list->next;

    while (list != NULL) {
        char updatedCharacter = map_function(list->character);
        if (updatedCharacter != list->character)
        {
            if (list->previous->character != updatedCharacter) {
                list->character = updatedCharacter;
            } else {
                list->previous->numOfRepetitions += list->numOfRepetitions;
                list->previous->next = list->next;
                list->next->previous = list->previous;
                RLEList toBeDeleted = list;
                list = list->previous;
                free(toBeDeleted);
            }
        }
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}