public class Solution {
    private static int digits_sum(int n) {
        int neg = 1;
        if (n < 0) {
            n = -1 * n;
            neg = -1;
        }
        int sum = 0;
        for (char digit : String.valueOf(n).toCharArray()) {
            sum += Character.getNumericValue(digit);
        }
        return sum * neg;
    }

    public static void order_by_points(int[] nums) {
        int[] _result = Arrays.stream(nums)
            .boxed()
            .sorted(Comparator.comparingInt(Solution::digits_sum))
            .mapToInt(Integer::intValue)
            .toArray();

        assert func(_result);  // POST: func is equivalent to: Write a function which sorts the given list of integers in ascending order according to the sum of their digits. Note: if there are several items with similar sum of their digits, order them based on their index in original list. For example: >>> order_by_points([1, 11, -1, -11, -12]) == [-1, -11, 1, -12, 11] >>> order_by_points([]) == []
    }
}
