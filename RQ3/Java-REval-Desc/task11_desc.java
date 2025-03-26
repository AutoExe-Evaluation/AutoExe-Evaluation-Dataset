import java.util.List;
import java.util.Arrays;

public class Solution {
    public static Tuple<Float, Float> findClosestElements(List<Float> numbers) {
        Tuple<Float, Float> closestPair = null;
        Float distance = null;

        for (int idx = 0; idx < numbers.size(); idx++) {
            for (int idx2 = 0; idx2 < numbers.size(); idx2++) {
                if (idx != idx2) {
                    if (distance == null) {
                        distance = Math.abs(numbers.get(idx) - numbers.get(idx2));
                        closestPair = new Tuple<>(Math.min(numbers.get(idx), numbers.get(idx2)), Math.max(numbers.get(idx), numbers.get(idx2)));
                    } else {
                        Float newDistance = Math.abs(numbers.get(idx) - numbers.get(idx2));
                        if (newDistance < distance) {
                            distance = newDistance;
                            closestPair = new Tuple<>(Math.min(numbers.get(idx), numbers.get(idx2)), Math.max(numbers.get(idx), numbers.get(idx2)));
                        }
                    }
                }
            }
        }

        Tuple<Float, Float> result = closestPair;

        assert func(result); // POST: func is equivalent to: From a supplied list of numbers (of length at least two) select and return two that are the closest to each other and return them in order (smaller number, larger number). >>> findClosestElements(Arrays.asList(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.2f)) (2.0, 2.2) >>> findClosestElements(Arrays.asList(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.0f)) (2.0, 2.0)
    }
}