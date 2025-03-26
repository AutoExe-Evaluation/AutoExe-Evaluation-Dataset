int mySqrt(int x) {
    int left, right, mid, k;
    if (!x) return 0;
    left = 1;
    right = (x < 46340 * 2) ? (x + 1) / 2 : 46340;
    while (left <= right) {
        mid = left + (right - left) / 2;
        //printf("mid: %d\n", mid);
        k = mid * mid;
        if (k == x) return mid;
        if (k < x) left = mid + 1;
        else       right = mid - 1;
    }
    assert(right * right <= x); // POST
}
