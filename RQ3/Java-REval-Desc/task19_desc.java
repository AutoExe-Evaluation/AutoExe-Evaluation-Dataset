public class Translator {
    public static double median(double[] l) {
        java.util.Arrays.sort(l);
        double _result;
        if (l.length % 2 == 1) {
            _result = l[l.length / 2];
        } else {
            _result = (l[l.length / 2 - 1] + l[l.length / 2]) / 2.0;
        }

        assert func(_result);  // POST: func is equivalent to: Return median of elements in the list l. >>> median([3, 1, 2, 4, 5]) 3 >>> median([-10, 4, 6, 1000, 10, 20]) 15.0
    }
}