public class PrimeFactor {
    public static void largestPrimeFactor(int n) {
        int largest = 1;
        for (int j = 2; j <= n; j++) {
            boolean isPrime = true;
            if (j < 2) {
                isPrime = false;
            }
            for (int i = 2; i < j - 1; i++) {
                if (j % i == 0) {
                    isPrime = false;
                }
            }
            if (n % j == 0 && isPrime) {
                largest = Math.max(largest, j);
            }
        }
        int _result = largest;

        assert func(_result);  // POST: func is equivalent to: Return the largest prime factor of n. Assume n > 1 and is not a prime. >>> largest_prime_factor(13195) 29 >>> largest_prime_factor(2048) 2
    }
}