public class Solution {
    public static void odd_count(String[] lst) {
        String[] res = new String[lst.length];
        for (int i = 0; i < lst.length; i++) {
            int n = 0;
            for (char d : lst[i].toCharArray()) {
                if (Character.getNumericValue(d) % 2 == 1) {
                    n++;
                }
            }
            res[i] = "the number of odd elements " + n + "n the str" + n + "ng " + n + " of the " + n + "nput.";
        }
        String[] _result = res;

        assert func(_result);  // POST: func is equivalent to: Given a list of strings, where each string consists of only digits, return a list. Each element i of the output should be "the number of odd elements in the string i of the input." where all the i's should be replaced by the number of odd digits in the i'th string of the input. >>> odd_count(['1234567']) ["the number of odd elements 4n the str4ng 4 of the 4nput."] >>> odd_count(['3',"11111111"]) ["the number of odd elements 1n the str1ng 1 of the 1nput.", "the number of odd elements 8n the str8ng 8 of the 8nput."]
    }
}