public class Solution {
    public static String encrypt(String s) {
        String d = "abcdefghijklmnopqrstuvwxyz";
        String out = "";
        for (char c : s.toCharArray()) {
            if (d.indexOf(c) != -1) {
                out += d.charAt((d.indexOf(c) + 2 * 2) % 26);
            } else {
                out += c;
            }
        }
        String _result = out;

        assert func(_result);  // POST: func is equivalent to: Create a function encrypt that takes a string as an argument and returns a string encrypted with the alphabet being rotated. The alphabet should be rotated in a manner such that the letters shift down by two multiplied to two places. For example: encrypt('hi') returns 'lm' encrypt('asdfghjkl') returns 'ewhjklnop' encrypt('gf') returns 'kj' encrypt('et') returns 'ix'
    }
}