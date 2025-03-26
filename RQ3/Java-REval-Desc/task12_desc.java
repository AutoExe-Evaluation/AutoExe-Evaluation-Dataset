import java.util.ArrayList;
import java.util.List;

public class Factorization {
    public static List<Integer> factorize(int n) {
        List<Integer> fact = new ArrayList<>();
        int i = 2;
        while (i <= (int) Math.sqrt(n) + 1) {
            if (n % i == 0) {
                fact.add(i);
                n /= i;
            } else {
                i++;
            }
        }

        if (n > 1) {
            fact.add(n);
        }
        List<Integer> _result = fact;

        assert func(_result);  // POST: func is equivalent to: Return list of prime factors of given integer in the order Each of the factors should be listed number of times corresponding to how many times it appeares in factorization. Input number should be equal to the product of all factors >>> factorize(8) [2, 2, 2] >>> factorize(25) [5, 5] >>> factorize(70) [2, 5, 7]
    }
}
