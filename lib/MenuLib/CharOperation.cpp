#include "MenuLib.h"


char* IntToString(int val) {
    if (val == 0) {
        char* zeroStr = (char*)malloc(2 * sizeof(char));
        zeroStr[0] = '0';
        zeroStr[1] = '\0';
        return zeroStr;
    }

    int isNegative = val < 0;
    int temp = isNegative ? -val : val;
    int digitCount = 0;

    while (temp != 0) {
        temp /= 10;
        digitCount++;
    }

    char* arr = (char*)malloc((digitCount + isNegative + 1) * sizeof(char));
    if (isNegative) {
        arr[0] = '-';
        val = -val;
    }

    arr[digitCount + isNegative] = '\0';
    for (int i = digitCount + isNegative - 1; i >= isNegative; --i) {
        arr[i] = (val % 10) + '0';
        val /= 10;
    }

    return arr;
}



char* charGenerator(char* rev, int space) {
    int len = strlen(rev);
    int copyLength = len < space - 1 ? len : space - 1;

    char* result = (char*)malloc(space * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    strncpy(result, rev, copyLength);
    for (int i = copyLength; i < space - 1; i++) {
        result[i] = ' ';
    }

    result[space - 1] = '\0';

    return result;
}


char* floatToString(float num, int precision) {
    int bufferSize = precision + 5; // Розраховуємо розмір буфера (запас для цілого числа та символів '*C')
    char* str = (char*)malloc(bufferSize * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    snprintf(str, bufferSize - 2, "%.*f", precision, num);
    strcat(str, "*C");

    return str;
}


char* mergeChar(const char* first, const char* second) {
    int sizeOfFirst = strlen(first);
    int sizeOfSecond = strlen(second);

    char* result = (char*)malloc((sizeOfFirst + sizeOfSecond + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < sizeOfFirst; i++) {
        result[i] = (first[i] == '_') ? ' ' : first[i];
    }

    for (int i = 0; i < sizeOfSecond; i++) {
        result[sizeOfFirst + i] = (second[i] == '_') ? ' ' : second[i];
    }

    result[sizeOfFirst + sizeOfSecond] = '\0';

    return result;
}
