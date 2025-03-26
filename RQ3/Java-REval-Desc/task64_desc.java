public class NestedBrackets {
    public static boolean is_nested(String string) {
        int[] opening_bracket_index = new int[string.length()];
        int[] closing_bracket_index = new int[string.length()];
        int opening_count = 0;
        int closing_count = 0;

        for (int i = 0; i < string.length(); i++) {
            if (string.charAt(i) == '[') {
                opening_bracket_index[opening_count++] = i;
            } else {
                closing_bracket_index[closing_count++] = i;
            }
        }

        int cnt = 0;
        int i = 0;
        int l = closing_count;

        for (int idx = 0; idx < opening_count; idx++) {
            if (i < l && opening_bracket_index[idx] < closing_bracket_index[l - 1 - i]) {
                cnt++;
                i++;
            }
        }

        boolean _result = cnt >= 2;

        assert func(_result);  // POST: func is equivalent to: Create a function that takes a string as input which contains only square brackets. The function should return True if and only if there is a valid subsequence of brackets where at least one bracket in the subsequence is nested. is_nested('[[]]') ➞ True is_nested('[]]]]]]][[[[[]') ➞ False is_nested('[][]') ➞ False is_nested('[]') ➞ False is_nested('[[][]]') ➞ True is_nested('[[]][[') ➞ True
    }
}