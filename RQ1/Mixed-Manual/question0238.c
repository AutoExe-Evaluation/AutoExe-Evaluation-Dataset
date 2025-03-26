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
    assert(output[0] / output[1] == nums[1] / nums[0]); // POST
}
