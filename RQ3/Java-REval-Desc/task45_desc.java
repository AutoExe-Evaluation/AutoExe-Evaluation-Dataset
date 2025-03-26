public class UniqueDigits {
    public static void unique_digits(int[] x) {
        java.util.List<Integer> odd_digit_elements = new java.util.ArrayList<>();
        for (int i : x) {
            if (java.util.Arrays.stream(Integer.toString(i).split("")).allMatch(c -> Integer.parseInt(c) % 2 == 1)) {
                odd_digit_elements.add(i);
            }
        }
        java.util.List<Integer> _result = new java.util.ArrayList<>(odd_digit_elements);
        java.util.Collections.sort(_result);

        assert func(_result);  // POST: func is equivalent to: Given a list of positive integers x. return a sorted list of all elements that hasn't any even digit. Note: Returned list should be sorted in increasing order. For example: >>> unique_digits([15, 33, 1422, 1]) [1, 15, 33] >>> unique_digits([152, 323, 1422, 10]) []
    }
}