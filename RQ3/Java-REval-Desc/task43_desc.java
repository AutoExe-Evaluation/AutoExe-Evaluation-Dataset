public class Solution {
    public static void words_string(String s) {
        String[] _result;
        if (s == null || s.isEmpty()) {
            _result = new String[0];
        } else {
            StringBuilder s_list = new StringBuilder();

            for (char letter : s.toCharArray()) {
                if (letter == ',') {
                    s_list.append(' ');
                } else {
                    s_list.append(letter);
                }
            }

            _result = s_list.toString().split("\\s+");
        }

        assert func(_result);  // POST: func is equivalent to: You will be given a string of words separated by commas or spaces. Your task is to split the string into words and return an array of the words. For example: words_string("Hi, my name is John") == ["Hi", "my", "name", "is", "John"] words_string("One, two, three, four, five, six") == ["One", "two", "three", "four", "five", "six"]
    }
}