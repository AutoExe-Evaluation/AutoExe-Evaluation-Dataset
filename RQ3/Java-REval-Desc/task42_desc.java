public class Main {
    public static int closestInteger(String value) {
        if (value.chars().filter(ch -> ch == '.').count() == 1) {
            // remove trailing zeros
            while (value.charAt(value.length() - 1) == '0') {
                value = value.substring(0, value.length() - 1);
            }
        }

        double num = Double.parseDouble(value);
        int res;
        if (value.endsWith(".5")) {
            if (num > 0) {
                res = (int) Math.ceil(num);
            } else {
                res = (int) Math.floor(num);
            }
        } else if (value.length() > 0) {
            res = (int) Math.round(num);
        } else {
            res = 0;
        }

        int _result = res;

        assert func(_result);  // POST: func is equivalent to: Create a function that takes a value (string) representing a number and returns the closest integer to it. If the number is equidistant Examples >>> closest_integer("10") 10 >>> closest_integer("15.3") 15 Note: Rounding away farthest return 15 and closest_integer("-14.5") should return -15.
    }
}