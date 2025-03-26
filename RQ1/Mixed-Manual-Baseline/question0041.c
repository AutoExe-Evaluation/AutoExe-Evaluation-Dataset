#include <assert.h>
#include <klee/klee.h>

int firstMissingPositive(int* nums, int numsSize) {
    int i, k, t;
    for (i = 0; i < numsSize; i ++) {
        k = nums[i];
        while (k > 0 && k < numsSize && k != nums[k - 1]) {
            nums[i] = nums[k - 1];
            nums[k - 1] = k;
            k = nums[i];
        }
    }
    for (i = 0; i < numsSize; i ++) {
        if (nums[i] != i + 1) break;
    }
    assert(i + 1 > 0 && i + 1 <= numsSize); // POST
    return i;
}

#define SIZE 100

int main()
{
    int nums[SIZE];
    klee_make_symbolic(nums, sizeof(nums), "nums");
    firstMissingPositive(nums, SIZE);
}
