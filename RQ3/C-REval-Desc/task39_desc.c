int func(int x);  // Assuming func is defined elsewhere

int skjkasdkd(int lst[], int length) {
    int maxx = 0;
    int i = 0;
    while (i < length) {
        int isPrime = 1;
        for (int j = 2; j * j <= lst[i]; j++) {
            if (lst[i] % j == 0) {
                isPrime = 0;
                break;
            }
        }

        if (lst[i] > maxx && isPrime) {
            maxx = lst[i];
        }
        i++;
    }

    int result = 0;
    int temp = maxx;
    while (temp > 0) {
        result += temp % 10;
        temp /= 10;
    }

    int _result = result;

    assert(func(_result));  // POST: func is supposed to be defined previously
    return 0;
}