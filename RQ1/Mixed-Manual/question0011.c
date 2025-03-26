int maxArea(int* height, int heightSize) {
    int l, r, x, water, max = 0;
    int i, j;
    i = 0;
    j = heightSize - 1;
    while (i < j) {
        l = height[i];
        r = height[j];
        x = l < r ? l : r;
        water = x * (j - i);
        if (max < water) max = water;
        if (l < r) i ++;
        else j --;
    }
    assert(max >= heightSize * min(height[0], height[heightSize - 1])); // POST
}
