public class Solution {
    public static void search(int[] lst) {
        int[] frq = new int[max(lst) + 1];
        for (int i : lst) {
            frq[i] += 1;
        }

        int ans = -1;
        for (int i = 1; i < frq.length; i++) {
            if (frq[i] >= i) {
                ans = i;
            }
        }

        int _result = ans;

        assert func(_result);  // POST: func is equivalent to: You are given a non-empty list of positive integers. Return the greatest integer that is greater than zero, and has a frequency greater than or equal to the value of the integer itself. The frequency of an integer is the number of times it appears in the list. If no such a value exist, return -1. Examples: search([4, 1, 2, 2, 3, 1]) == 2 search([1, 2, 2, 3, 3, 3, 4, 4, 4]) == 3 search([5, 5, 4, 4, 4]) == -1
    }
}
