public class Solution {
    public static void canArrange(int[] arr) {
        int ind = -1;
        int i = 1;
        while (i < arr.length) {
            if (arr[i] < arr[i - 1]) {
                ind = i;
            }
            i++;
        }
        int _result = ind;

        assert func(_result);  // POST: func is equivalent to: Create a function which returns the largest index of an element which is not greater than or equal to the element immediately preceding it. If no such element exists then return -1. The given array will not contain duplicate values. Examples: can_arrange([1,2,4,3,5]) = 3 can_arrange([1,2,3]) = -1
    }
}