#include <assert.h>
#include <klee/klee.h>

int removeDuplicates(int* nums, int numsSize) {
    int i, j;
    
    if (numsSize < 2) return numsSize;
    
    for (i = 0, j = 1; j < numsSize; j ++) {
        if (nums[j] != nums[i]) {
            i ++;
            nums[i] = nums[j];
        }
    }
    
    assert(i + 1 < numsSize); // POST
    return i;
}

#define SIZE 100

int main()
{
    int nums[SIZE];
    klee_make_symbolic(nums, sizeof(nums), "nums");
    removeDuplicates(nums, SIZE);
}
