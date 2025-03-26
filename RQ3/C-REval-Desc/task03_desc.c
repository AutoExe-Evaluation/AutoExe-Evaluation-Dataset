int* intersperse(int* numbers, int length, int delimeter, int* result_length) {
    if (length == 0) {
        *result_length = 0;
        return NULL;
    }

    int* result = (int*)malloc((length * 2 - 1) * sizeof(int));
    int index = 0;

    for (int i = 0; i < length - 1; i++) {
        result[index++] = numbers[i];
        result[index++] = delimeter;
    }

    result[index++] = numbers[length - 1];
    *result_length = index;

    return result;
}