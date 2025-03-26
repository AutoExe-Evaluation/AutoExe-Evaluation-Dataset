public class Translator {
    public static void count_upper(String s) {
        int count = 0;
        for (int i = 0; i < s.length(); i += 2) {
            if ("AEIOU".indexOf(s.charAt(i)) != -1) {
                count++;
            }
        }
        int _result = count;

        assert func(_result);  // POST: func is equivalent to: Given a string s, count the number of uppercase vowels in even indices. For example: count_upper('aBCdEf') returns 1 count_upper('abcdefg') returns 0 count_upper('dBBE') returns 0
    }
}