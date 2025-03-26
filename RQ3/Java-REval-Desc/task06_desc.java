import java.util.ArrayList;
import java.util.List;

public class Solution {
    public static List<Integer> rollingMax(List<Integer> numbers) {
        Integer runningMax = null;
        List<Integer> result = new ArrayList<>();

        for (Integer n : numbers) {
            if (runningMax == null) {
                runningMax = n;
            } else {
                runningMax = Math.max(runningMax, n);
            }

            result.add(runningMax);
        }

        List<Integer> _result = result;

        assert func(_result);  // POST: func is equivalent to: From a given list of integers, generate a list of rolling maximum element found until given moment in the sequence. >>> rolling_max([1, 2, 3, 2, 3, 4, 2]) [1, 2, 3, 3, 3, 4, 4]
    }
}