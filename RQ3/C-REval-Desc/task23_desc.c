int largest_prime_factor(int n) {
    int largest = 1;
    for (int j = 2; j <= n; j++) {
        int is_prime = 1;
        if (j < 2) {
            is_prime = 0;
        }
        for (int i = 2; i < j - 1; i++) {
            if (j % i == 0) {
                is_prime = 0;
            }
        }
        if (n % j == 0 && is_prime) {
            largest = (largest > j) ? largest : j;
        }
    }
    int _result = largest;

    assert(func(_result));  // POST: func is equivalent to: Return the largest prime factor of n. Assume n > 1 and is not a prime.
}