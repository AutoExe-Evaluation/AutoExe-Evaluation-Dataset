import java.util.ArrayList;

public class Main {
    public static void prime_fib(int n) {
        ArrayList<Integer> f = new ArrayList<>();
        f.add(0);
        f.add(1);
        
        while (true) {
            f.add(f.get(f.size() - 1) + f.get(f.size() - 2));
            boolean is_prime = true;
            if (f.get(f.size() - 1) < 2) {
                is_prime = false;
            }
            for (int k = 2; k < Math.min((int) Math.sqrt(f.get(f.size() - 1)) + 1, f.get(f.size() - 1) - 1); k++) {
                if (f.get(f.size() - 1) % k == 0) {
                    is_prime = false;
                }
            }
            if (is_prime) {
                n -= 1;
            }
            if (n == 0) {
                int _result = f.get(f.size() - 1);
            }
        }

        assert func(_result);  // POST: func is equivalent to: prime_fib returns n-th number that is a Fibonacci number and it's also prime. >>> prime_fib(1) 2 >>> prime_fib(2) 3 >>> prime_fib(3) 5 >>> prime_fib(4) 13 >>> prime_fib(5) 89
    }
}