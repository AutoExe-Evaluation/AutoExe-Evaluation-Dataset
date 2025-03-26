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
}
