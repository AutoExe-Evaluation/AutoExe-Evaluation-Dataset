int* sum_product(int* numbers, int size) {
    static int result[2];
    int sum_value = 0;
    int prod_value = 1;

    for (int i = 0; i < size; i++) {
        sum_value += numbers[i];
        prod_value *= numbers[i];
    }

    if (size == 0) {
        prod_value = 1;
    }

    result[0] = sum_value;
    result[1] = prod_value;

    return result;
}