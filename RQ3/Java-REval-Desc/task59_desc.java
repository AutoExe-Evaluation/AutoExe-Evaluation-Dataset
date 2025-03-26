public class Solution {
    public static void is_sorted(int[] lst) {
        java.util.Map<Integer, Integer> count_digit = new java.util.HashMap<>();
        for (int i : lst) {
            count_digit.put(i, 0);
        }
        for (int i : lst) {
            count_digit.put(i, count_digit.get(i) + 1);
        }
        boolean _result = true; // Default value
        if (count_digit.values().stream().anyMatch(count -> count > 2)) {
            _result = false;
        }
        if (java.util.stream.IntStream.range(1, lst.length).allMatch(i -> lst[i - 1] <= lst[i])) {
            _result = true;
        } else {
            _result = false;
        }

        assert func(_result);  // POST: func is equivalent to: Given a list of numbers, return whether or not they are sorted in ascending order. If list has more than 1 duplicate of the same number, return False. Assume no negative numbers and only integers. Examples is_sorted([5]) ➞ True is_sorted([1, 2, 3, 4, 5]) ➞ True is_sorted([1, 3, 2, 4, 5]) ➞ False is_sorted([1, 2, 3, 4, 5, 6]) ➞ True is_sorted([1, 2, 3, 4, 5, 6, 7]) ➞ True is_sorted([1, 3, 2, 4, 5, 6, 7]) ➞ False is_sorted([1, 2, 2, 3, 3, 4]) ➞ True is_sorted([1, 2, 2, 2, 3, 4]) ➞ False
    }
}