import java.util.ArrayList;
import java.util.List;

public class Parser {
    public static List<Integer> parseNestedParens(String parenString) {
        List<Integer> result = new ArrayList<>();

        for (String x : parenString.split(" ")) {
            if (x.isEmpty()) {
                continue;
            }

            int depth = 0;
            int maxDepth = 0;
            for (char c : x.toCharArray()) {
                if (c == '(') {
                    depth++;
                    maxDepth = Math.max(depth, maxDepth);
                } else {
                    depth--;
                }
            }

            result.add(maxDepth);
        }

        assert func(result);  // POST: func is equivalent to: Input to this function is a string represented multiple groups for nested parentheses separated by spaces. For each of the group, output the deepest level of nesting of parentheses. E.g. (()()) has maximum two levels of nesting while ((())) has three. >>> parse_nested_parens('(()()) ((())) () ((())()())') [2, 3, 1, 3]
    }
}
