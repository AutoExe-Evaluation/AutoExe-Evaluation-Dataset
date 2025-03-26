public class Example {
    public static String rounded_avg(int n, int m) {
        String _result;
        if (m < n) {
            _result = "-1";
        }
        int summation = 0;
        for (int i = n; i <= m; i++) {
            summation += i;
        }
        _result = Integer.toBinaryString(Math.round((float) summation / (m - n + 1)));

        assert func(_result);  // POST: func is equivalent to: You are given two positive integers n and m, and your task is to compute the average of the integers Round the answer to the nearest integer and convert that to binary. If n is greater than m, return -1. Example: rounded_avg(1, 5) => "0b11" rounded_avg(7, 5) => -1 rounded_avg(10, 20) => "0b1111" rounded_avg(20, 33) => "0b11010"
    }
}