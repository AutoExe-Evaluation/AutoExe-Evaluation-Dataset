public class Translation {
    public static void total_match(String[] lst1, String[] lst2) {
        int l1 = 0;
        for (String st : lst1) {
            l1 += st.length();
        }

        int l2 = 0;
        for (String st : lst2) {
            l2 += st.length();
        }

        String[] _result;
        if (l1 <= l2) {
            _result = lst1;
        } else {
            _result = lst2;
        }

        assert func(_result);  // POST: func is equivalent to: Write a function that accepts two lists of strings and returns the list that has total number of chars in the all strings of the list less than the other list. if the two lists have the same number of chars, return the first list. Examples total_match([], []) ➞ [] total_match(['hi', 'admin'], ['hI', 'Hi']) ➞ ['hI', 'Hi'] total_match(['hi', 'admin'], ['hi', 'hi', 'admin', 'project']) ➞ ['hi', 'admin'] total_match(['hi', 'admin'], ['hI', 'hi', 'hi']) ➞ ['hI', 'hi', 'hi'] total_match(['4'], ['1', '2', '3', '4', '5']) ➞ ['4'];
    }
}