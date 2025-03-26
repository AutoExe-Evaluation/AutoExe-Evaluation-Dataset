public class SpecialFactorial {
    public static void special_factorial(int n) {
        int fact_i = 1;
        int special_fact = 1;
        for (int i = 1; i <= n; i++) {
            fact_i *= i;
            special_fact *= fact_i;
        }
        int _result = special_fact;

        assert func(_result);  // POST: func is equivalent to: The Brazilian factorial is defined as: brazilian_factorial(n) = n! * (n-1)! * (n-2)! * ... * 1! where n > 0 For example: >>> special_factorial(4) 288 The function will receive an integer as input and should return the special factorial of this integer.
    }
}