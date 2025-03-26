public class Translator {
    public static int minSubArraySum(int[] nums) {
        int max_sum = 0;
        int s = 0;
        for (int num : nums) {
            s += -num;
            if (s < 0) {
                s = 0;
            }
            max_sum = Math.max(s, max_sum);
        }
        if (max_sum == 0) {
            max_sum = Integer.MIN_VALUE;
            for (int i : nums) {
                max_sum = Math.max(-i, max_sum);
            }
        }
        int min_sum = -max_sum;
        int _result = min_sum;

        assert func(_result);  // POST: func is equivalent to: Given an array of integers nums, find the minimum sum of any non-empty sub-array of nums. Example minSubArraySum([2, 3, 4, 1, 2, 4]) == 1 minSubArraySum([-1, -2, -3]) == -6
    }
}