public class PrimeLength {
    public static void primeLength(String string) {
        int l = string.length();
        boolean _result = true;
        if (l == 0 || l == 1) {
            _result = false;
        }
        for (int i = 2; i < l; i++) {
            if (l % i == 0) {
                _result = false;
            }
        }

        assert func(_result);  // POST: func is equivalent to: Write a function that takes a string and returns True if the string length is a prime number or False otherwise Examples prime_length('Hello') == True prime_length('abcdcba') == True prime_length('kittens') == True prime_length('orange') == False
    }
}