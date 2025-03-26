public class Main {
    public static void simplify(String x, String n) {
        String[] ab = x.split("/");
        String[] cd = n.split("/");
        int numerator = Integer.parseInt(ab[0]) * Integer.parseInt(cd[0]);
        int denom = Integer.parseInt(ab[1]) * Integer.parseInt(cd[1]);
        boolean _result = false;
        if ((double) numerator / denom == (int) ((double) numerator / denom)) {
            _result = true;
        }

        assert func(_result);  // POST: func is equivalent to: Your task is to implement a function that will simplify the expression x * n. The function returns True if x * n evaluates to a whole number and False otherwise. Both x and n, are string representation of a fraction, and have the following format, <numerator>/<denominator> where both numerator and denominator are positive whole numbers. You can assume that x, and n are valid fractions, and do not have zero as denominator. simplify("1/5", "5/1") = True simplify("1/6", "2/1") = False simplify("7/10", "10/2") = False
    }
}