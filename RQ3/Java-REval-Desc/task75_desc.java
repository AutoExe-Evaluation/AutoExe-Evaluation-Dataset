public class Solution {
    public static void specialFilter(int[] nums) {
        int count = 0;
        for (int num : nums) {
            if (num > 10) {
                int[] odd_digits = {1, 3, 5, 7, 9};
                String number_as_string = Integer.toString(num);
                if (contains(odd_digits, Character.getNumericValue(number_as_string.charAt(0))) 
                    && contains(odd_digits, Character.getNumericValue(number_as_string.charAt(number_as_string.length() - 1)))) {
                    count += 1;
                }
            }
        }
        int _result = count;

        assert func(_result); // POST: func is equivalent to: Write a function that takes an array of numbers as input and returns the number of elements in the array that are greater than 10 and both first and last digits of a number are odd (1, 3, 5, 7, 9). For example: specialFilter([15, -73, 14, -15]) => 1 specialFilter([33, -2, -3, 45, 21, 109]) => 2
    }
}
