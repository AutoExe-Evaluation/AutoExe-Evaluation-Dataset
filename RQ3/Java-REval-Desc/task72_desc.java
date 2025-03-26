public class Translator {
    public static void wordsInSentence(String sentence) {
        StringBuilder newLst = new StringBuilder();
        for (String word : sentence.split(" ")) {
            int flg = 0;
            if (word.length() == 1) {
                flg = 1;
            }
            for (int i = 2; i < word.length(); i++) {
                if (word.length() % i == 0) {
                    flg = 1;
                }
            }
            if (flg == 0 || word.length() == 2) {
                if (newLst.length() > 0) {
                    newLst.append(" ");
                }
                newLst.append(word);
            }
        }
        String result = newLst.toString();

        assert func(result);  // POST: func is equivalent to: You are given a string representing a sentence, the sentence contains some words separated by a space, and you have to return a string that contains the words whose lengths are prime numbers, the order of the words in the new string should be the same as the original one. Example 1: Input: sentence = "This is a test" Output: "is" Example 2: Input: sentence = "lets go for swimming" Output: "go for" Constraints: * 1 <= len(sentence) <= 100 * sentence contains only letters
    }
}