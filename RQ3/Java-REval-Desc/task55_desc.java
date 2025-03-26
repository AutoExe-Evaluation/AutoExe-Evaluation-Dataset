public class WordSelector {
    public static void select_words(String s, int n) {
        java.util.List<String> result = new java.util.ArrayList<>();
        for (String word : s.split(" ")) {
            int n_consonants = 0;
            for (int i = 0; i < word.length(); i++) {
                if ("aeiouAEIOU".indexOf(word.charAt(i)) == -1) {
                    n_consonants++;
                }
            }
            if (n_consonants == n) {
                result.add(word);
            }
        }
        java.util.List<String> _result = result;

        assert func(_result);  // POST: func is equivalent to: Given a string s and a natural number n, you have been tasked to implement a function that returns a list of all words n consonants, in order these words appear in the string s. If the string s is empty then the function should return an empty list. Note: you may assume the input string contains only letters and spaces. Examples: select_words("Mary had a little lamb", 4) ==> ["little"] select_words("Mary had a little lamb", 3) ==> ["Mary", "lamb"] select_words("simple white space", 2) ==> [] select_words("Hello world", 4) ==> ["world"] select_words("Uncle sam", 3) ==> ["Uncle"]
    }
}