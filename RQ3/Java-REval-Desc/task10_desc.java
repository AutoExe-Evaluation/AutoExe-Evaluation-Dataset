public class Translator {
    public static int howManyTimes(String string, String substring) {
        int times = 0;

        for (int i = 0; i <= string.length() - substring.length(); i++) {
            if (string.substring(i, i + substring.length()).equals(substring)) {
                times++;
            }
        }

        int _result = times;

        assert func(_result);  // POST: func is equivalent to: Find how many times a given substring can be found in the original string. Count overlapping cases. >>> how_many_times('', 'a') 0 >>> how_many_times('aaa', 'a') 3 >>> how_many_times('aaaa', 'aa') 3
    }
}
