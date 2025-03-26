public class Main {
    public static void cycpattern_check(String a, String b) {
        int l = b.length();
        String pat = b + b;
        boolean _result = false;
        for (int i = 0; i <= a.length() - l; i++) {
            for (int j = 0; j <= l; j++) {
                if (a.substring(i, i + l).equals(pat.substring(j, j + l))) {
                    _result = true;
                }
            }
        }

        assert func(_result);  // POST: func is equivalent to: You are given 2 words. You need to return True if the second word or any of its rotations is a substring in the first word cycpattern_check("abcd","abd") => False cycpattern_check("hello","ell") => True cycpattern_check("whassup","psus") => False cycpattern_check("abab","baa") => True cycpattern_check("efef","eeff") => False cycpattern_check("himenss","simen") => True
    }
}