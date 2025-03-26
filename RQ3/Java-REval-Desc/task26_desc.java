public class CircularShift {
    public static void circular_shift(int x, int shift) {
        String s = Integer.toString(x);
        String _result;
        if (shift > s.length()) {
            _result = new StringBuilder(s).reverse().toString();
        } else {
            _result = s.substring(s.length() - shift) + s.substring(0, s.length() - shift);
        }

        assert func(_result);  // POST: func is equivalent to: Circular shift the digits of the integer x, shift the digits right by shift and return the result as a string. If shift > number of digits, return digits reversed. >>> circular_shift(12, 1) "21" >>> circular_shift(12, 2) "12"
    }
}