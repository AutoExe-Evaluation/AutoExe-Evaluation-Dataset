public class Solution {
    public static String solve(String s) {
        int flg = 0;
        int idx = 0;
        char[] new_str = s.toCharArray();
        for (char i : s.toCharArray()) {
            if (Character.isAlphabetic(i)) {
                new_str[idx] = Character.isLowerCase(i) ? Character.toUpperCase(i) : Character.toLowerCase(i);
                flg = 1;
            }
            idx++;
        }
        s = new String(new_str);
        if (flg == 0) {
            StringBuilder _result = new StringBuilder(s).reverse();
        } else {
            String _result = s;
        }

        assert func(_result);  // POST: func is equivalent to: You are given a string s. if s[i] is a letter, reverse its case otherwise keep it as it is. If the string contains no letters, reverse the string. The function should return the resulted string. Examples solve("1234") = "4321" solve("ab") = "AB" solve("#a@C") = "#A@c"
    }
}