public class Solution {
    public static void correctBracketing(String brackets) {
        int depth = 0;
        boolean _result = true;
        for (char b : brackets.toCharArray()) {
            if (b == '<') {
                depth += 1;
            } else {
                depth -= 1;
            }
            if (depth < 0) {
                _result = false;
            }
        }
        if (_result) {
            _result = (depth == 0);
        }
        assert func(_result);  // POST: func is equivalent to: brackets is a string of "<" and ">". return True if every opening bracket has a corresponding closing bracket. >>> correct_bracketing("<") False >>> correct_bracketing("<>") True >>> correct_bracketing("<<><>>") True >>> correct_bracketing("><<>") False
    }
}