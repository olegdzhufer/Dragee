#include "MenuLib.h"


char* IntToString(int val) {
    int i = 0, temp, digitCount;
    digitCount = 0;
    temp = val;

    while (temp != 0) {
        temp /= 10;
        digitCount++;
    }

    char* arr = (char*)malloc((digitCount + 1) * sizeof(char));

    i = digitCount;
    while (val) {
        arr[--i] = (char)(val % 10) + '0'; 
        val /= 10;
    }

    arr[digitCount] = '\0';

    return arr;
}

char* charGenerator(char* rev, int space){
    char* result = (char*) malloc(space* sizeof(char));
    int i = 0;
    while(rev[i] != '\0'){
        i ++;
    }

    if(result){
        if(i > space - 1){
            free(result);
            return NULL;
        }
        
        for(int n = 0; n < space - 1; n++){
            if(rev[n] != '\0'){
                result[n] = rev[n];
                
            }
            else{
                i = n;
                break;
            }
            
        }
        while (i < space -1)
        {
            result[i] = ' ';
            i ++;
        }
        
        result[space - 1] = '\0';

        return result;
    }
    return NULL;
}

char* floatToString(float num, int precision) {
    char* str = (char*)malloc(6 * sizeof(char)); // Виділяємо пам'ять для рядка
    snprintf(str, 6, "%.*f", precision, num); // Використовуємо snprintf для конвертації
    return str;
}

char* mergeChar(const char* first, const char* second) {
    int sizeOfFirst = 0;
    int sizeOfSecond = 0;

    // Визначаємо довжину першого рядка
    while (first[sizeOfFirst] != '\0') {
        sizeOfFirst++;
    }
    // Визначаємо довжину другого рядка
    while (second[sizeOfSecond] != '\0') {
        sizeOfSecond++;
    }
    // Виділяємо пам'ять для об'єднаного рядка
    char* result = (char*)malloc((sizeOfFirst + sizeOfSecond + 1) * sizeof(char));

    // Об'єднуємо перший рядок
    for (int i = 0; i < sizeOfFirst; i++) {
        if(first[i] == '_')result[i] = ' ';
        else result[i] = first[i];
    }

    // Об'єднуємо другий рядок
    for (int i = 0; i < sizeOfSecond; i++) {
        if(result[sizeOfFirst + i] == '_')result[sizeOfFirst + i] = ' ' ;
        else result[sizeOfFirst + i] = second[i];
    }

    // Додаємо нульовий символ в кінець об'єднаного рядка
    result[sizeOfFirst + sizeOfSecond] = '\0';

    return result;
}
