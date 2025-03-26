public class Solution {
    public static void digits(int n) {
        int product = 1;
        int odd_count = 0;
        for (char digit : String.valueOf(n).toCharArray()) {
            int int_digit = Character.getNumericValue(digit);
            if (int_digit % 2 == 1) {
                product = product * int_digit;
                odd_count++;
            }
        }
        int _result;
        if (odd_count == 0) {
            _result = 0;
        } else {
            _result = product;
        }

        assert func(_result);  // POST: func is equivalent to: Given a positive integer n, return the product of the odd digits. Return 0 if all digits are even. For example: digits(1) == 1 digits(4) == 0 digits(235) == 15
    }
}