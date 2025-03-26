public class BracketChecker {
    public static void correctBracketing(String brackets) {
        int depth = 0;
        boolean result = true;
        for (char b : brackets.toCharArray()) {
            if (b == '(') {
                depth += 1;
            } else {
                depth -= 1;
            }
            if (depth < 0) {
                result = false;
            }
        }
        if (result) {
            result = (depth == 0);
        }

        assert func(result);  // POST: func is equivalent to: brackets is a string of "(" and ")". return True if every opening bracket has a corresponding closing bracket. >>> correctBracketing("(") False >>> correctBracketing("()") True >>> correctBracketing("(()())") True >>> correctBracketing(")(()") False
    }
}