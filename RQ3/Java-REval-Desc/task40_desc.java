public class Main {
    public static void countUpTo(int n) {
        int[] primes = new int[n];
        int count = 0;
        for (int i = 2; i < n; i++) {
            boolean isPrime = true;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes[count++] = i;
            }
        }
        int[] _result = new int[count];
        System.arraycopy(primes, 0, _result, 0, count);

        assert func(_result);  // POST: func is equivalent to: Implement a function that takes an non-negative integer and returns an array of the first n integers that are prime numbers and less than n. for example: count_up_to(5) => [2,3] count_up_to(11) => [2,3,5,7] count_up_to(0) => [] count_up_to(20) => [2,3,5,7,11,13,17,19] count_up_to(1) => [] count_up_to(18) => [2,3,5,7,11,13,17]
    }
}