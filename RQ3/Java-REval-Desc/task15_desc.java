public class Sorter {
    public static void sort_even(int[] l) {
        int[] evens = new int[(l.length + 1) / 2];
        int[] odds = new int[l.length / 2];
        
        for (int i = 0, j = 0, k = 0; i < l.length; i++) {
            if (i % 2 == 0) {
                evens[j++] = l[i];
            } else {
                odds[k++] = l[i];
            }
        }
        
        java.util.Arrays.sort(evens);
        java.util.List<Integer> ans = new java.util.ArrayList<>();
        for (int i = 0; i < odds.length; i++) {
            ans.add(evens[i]);
            ans.add(odds[i]);
        }
        if (evens.length > odds.length) {
            ans.add(evens[evens.length - 1]);
        }
        int[] _result = ans.stream().mapToInt(i -> i).toArray();

        assert func(_result); // POST: func is equivalent to: This function takes a list l and returns a list l' such that l' is identical to l in the odd indicies, while its values at the even indicies are equal to the values of the even indicies of l, but sorted. >>> sort_even([1, 2, 3]) [1, 2, 3] >>> sort_even([5, 6, 3, 4]) [3, 6, 5, 4]
    }
}