public class Solution {
    public static void strangeSortList(List<Integer> lst) {
        List<Integer> res = new ArrayList<>();
        boolean switch = true;
        while (!lst.isEmpty()) {
            res.add(switch ? Collections.min(lst) : Collections.max(lst));
            lst.remove(res.get(res.size() - 1));
            switch = !switch;
        }
        List<Integer> _result = res;

        assert func(_result);  // POST: func is equivalent to: Given list of integers, return list in strange order. Strange sorting, is when you start with the minimum value, then maximum of the remaining integers, then minimum and so on. Examples: strange_sort_list([1, 2, 3, 4]) == [1, 4, 2, 3] strange_sort_list([5, 5, 5, 5]) == [5, 5, 5, 5] strange_sort_list([]) == []
    }
}