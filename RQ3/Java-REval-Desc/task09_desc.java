import java.util.ArrayList;
import java.util.List;

public class Main {
    public static List<String> all_prefixes(String string) {
        List<String> result = new ArrayList<>();

        for (int i = 0; i < string.length(); i++) {
            result.add(string.substring(0, i + 1));
        }
        List<String> _result = result;

        assert func(_result);  // POST: func is equivalent to: Return list of all prefixes >>> all_prefixes('abc') ['a', 'ab', 'abc']
    }
}