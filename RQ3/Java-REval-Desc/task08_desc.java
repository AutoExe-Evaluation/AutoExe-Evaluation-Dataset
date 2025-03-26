import java.util.List;
import java.util.Optional;

public class Example {
    public static Optional<String> longest(List<String> strings) {
        String _result = null;
        if (strings.isEmpty()) {
            _result = null;
        } else {
            int maxlen = strings.stream().mapToInt(String::length).max().orElse(0);
            for (String s : strings) {
                if (s.length() == maxlen) {
                    _result = s;
                    break; // to return the first one in case of multiple strings of the same length
                }
            }
        }
        assert func(_result); // POST: func is equivalent to: Out of list of strings, return the longest one. Return the first one in case of multiple strings of the same length. Return None in case the input list is empty. >>> longest([]) >>> longest(['a', 'b', 'c']) 'a' >>> longest(['a', 'bb', 'ccc']) 'ccc'
    }
}
