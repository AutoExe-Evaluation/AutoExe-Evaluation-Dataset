#include <assert.h>
#include <stdlib.h>
#include <klee/klee.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    assert(numsSize > 1); // PRE
    int *x = malloc(numsSize * sizeof(int));
    //assert(x);
    int i, j, k;
    
    x[0] = 1;
    for (i = 1; i < numsSize; i ++) {
        x[i] = x[i - 1] * nums[i - 1];
    }
    k = nums[numsSize - 1];
    for (i = numsSize - 2; i >= 0; i --) {
        x[i] = x[i] * k;
        k *= nums[i];
    }
    
    *returnSize = numsSize;
    assert(x[0] / x[1] == nums[1] / nums[0]); // POST
    return x;
}

#define SIZE 100

int main()
{
    int nums[SIZE];
    klee_make_symbolic(nums, sizeof(nums), "nums");
    int returnSize = 0;
    productExceptSelf(nums, SIZE, &returnSize);
}
