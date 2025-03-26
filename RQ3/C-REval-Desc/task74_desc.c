#include <stdio.h>
#include <stdlib.h>

int digits_sum(int n) {
    int neg = 1;
    if (n < 0) {
        n = -n;
        neg = -1;
    }
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum * neg;
}

int compare(const void *a, const void *b) {
    int sum_a = digits_sum(*(int *)a);
    int sum_b = digits_sum(*(int *)b);
    return (sum_a > sum_b) - (sum_a < sum_b);
}

void order_by_points(int *nums, int size) {
    qsort(nums, size, sizeof(int), compare);
}

int main() {
    int nums[] = {1, 11, -1, -11, -12};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    order_by_points(nums, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    
    return 0;
}