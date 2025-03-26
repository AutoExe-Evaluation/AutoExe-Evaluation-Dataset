#include <assert.h>
#include <klee/klee.h>

int removeDuplicates(int* nums, int numsSize) {
    int i, j;
    
    if (numsSize < 3) return numsSize;
    
    for (i = 2, j = 2; j < numsSize; j ++) {
        if (nums[j] != nums[i - 2]) {
            nums[i] = nums[j];
            i ++;
        }
    }
    
    assert(i <= numsSize);
    return i;
}

#define SIZE 100

int main()
{
    int nums[SIZE];
    klee_make_symbolic(nums, sizeof(nums), "nums");
    removeDuplicates(nums, SIZE);
}
