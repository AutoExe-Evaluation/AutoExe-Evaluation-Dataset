public class Solution {
    public static String make_palindrome(String string) {
        String _result;
        if (string.isEmpty()) {
            _result = "";
        }

        int beginning_of_suffix = 0;

        while (!string.substring(beginning_of_suffix).equals(new StringBuilder(string.substring(beginning_of_suffix)).reverse().toString())) {
            beginning_of_suffix++;
        }

        _result = string + new StringBuilder(string.substring(0, beginning_of_suffix)).reverse().toString();

        assert func(_result);  // POST: func is equivalent to: Test if given string is a palindrome Find the shortest palindrome that begins with a supplied string. Algorithm idea is simple: - Find the longest postfix of supplied string that is a palindrome. - Append to the end of the string reverse of a string prefix that comes before the palindromic suffix. >>> make_palindrome('') '' >>> make_palindrome('cat') 'catac' >>> make_palindrome('cata') 'catac'
    }
}