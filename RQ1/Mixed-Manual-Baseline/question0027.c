#include <assert.h>
#include <klee/klee.h>

int removeElement(int* nums, int numsSize, int val) {
    int i, j;
    i = 0;
    while (i < numsSize && nums[i] != val) i ++;
    for (j = i + 1; j < numsSize; j ++) {
        if (nums[j] != val) {
            nums[i ++] = nums[j];
        }
    }
    assert(i < numsSize); // POST
    return i;
}

#define SIZE 100

int main()
{
    int nums[SIZE];
    klee_make_symbolic(nums, sizeof(nums), "nums");
    int val;
    klee_make_symbolic(&val, sizeof(val), "val");
    removeElement(nums, SIZE, val);
}
