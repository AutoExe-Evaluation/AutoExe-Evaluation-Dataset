public class Solution {
    public static int count_nums(int[] arr) {
        int _result = 0;
        for (int i : arr) {
            int neg = 1;
            if (i < 0) {
                i = -1 * i;
                neg = -1;
            }
            int sum = 0;
            for (char c : String.valueOf(i).toCharArray()) {
                sum += Character.getNumericValue(c);
            }
            if (sum * neg > 0) {
                _result++;
            }
        }
        
        assert func(_result);  // POST: func is equivalent to: Write a function count_nums which takes an array of integers and returns the number of elements which has a sum of digits > 0. If a number is negative, then its first signed digit will be negative: e.g. -123 has signed digits -1, 2, and 3. >>> count_nums([]) == 0 >>> count_nums([-1, 11, -11]) == 1 >>> count_nums([1, 1, 2]) == 3
    }
}
