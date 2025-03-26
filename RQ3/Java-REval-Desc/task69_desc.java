public class SpaceFixer {
    public static String fix_spaces(String text) {
        String new_text = "";
        int i = 0;
        int start = 0;
        int end = 0;
        while (i < text.length()) {
            if (text.charAt(i) == ' ') {
                end += 1;
            } else {
                if (end - start > 2) {
                    new_text += "-" + text.charAt(i);
                } else if (end - start > 0) {
                    new_text += "_".repeat(end - start) + text.charAt(i);
                } else {
                    new_text += text.charAt(i);
                }
                start = i + 1;
                end = i + 1;
            }
            i += 1;
        }
        if (end - start > 2) {
            new_text += "-";
        } else if (end - start > 0) {
            new_text += "_";
        }
        String _result = new_text;

        assert func(_result);  // POST: func is equivalent to: Given a string text, replace all spaces in it with underscores, and if a string has more than 2 consecutive spaces, then replace all consecutive spaces with - fix_spaces("Example") == "Example" fix_spaces("Example 1") == "Example_1" fix_spaces(" Example 2") == "_Example_2" fix_spaces(" Example 3") == "_Example-3"
    }
}