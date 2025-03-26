public class Solution {
    public static void common(int[] l1, int[] l2) {
        java.util.Set<Integer> ret = new java.util.HashSet<>();
        for (int e1 : l1) {
            for (int e2 : l2) {
                if (e1 == e2) {
                    ret.add(e1);
                }
            }
        }
        java.util.List<Integer> _result = new java.util.ArrayList<>(ret);
        java.util.Collections.sort(_result);

        assert func(_result);  // POST: func is equivalent to: Return sorted unique common elements for two lists. >>> common([1, 4, 3, 34, 653, 2, 5], [5, 7, 1, 5, 9, 653, 121]) [1, 5, 653] >>> common([5, 3, 2, 8], [3, 2])
    }
}