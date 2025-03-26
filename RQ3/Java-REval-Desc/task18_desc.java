public class Fib4 {
    private static int[] appendAndPop(int[] results) {
        int newValue = results[results.length - 1] + results[results.length - 2] + results[results.length - 3] + results[results.length - 4];
        int[] newResults = new int[results.length];
        System.arraycopy(results, 1, newResults, 0, results.length - 1);
        newResults[newResults.length - 1] = newValue;
        return newResults;
    }

    public static void fib4(int n) {
        int[] results = {0, 0, 2, 0};
        int _result;
        if (n < 4) {
            _result = results[n];
        } else {
            for (int i = 4; i <= n; i++) {
                results = appendAndPop(results);
            }
            _result = results[results.length - 1];
        }
        assert func(_result); // POST: func is equivalent to: The Fib4 number sequence is a sequence similar to the Fibbonacci sequnece that's defined as follows: fib4(0) -> 0 fib4(1) -> 0 fib4(2) -> 2 fib4(3) -> 0 fib4(n) -> fib4(n-1) + fib4(n-2) + fib4(n-3) + fib4(n-4). Please write a function to efficiently compute the n-th element of the fib4 number sequence. Do not use recursion. >>> fib4(5) 4 >>> fib4(6) 8 >>> fib4(7) 14
    }
}
