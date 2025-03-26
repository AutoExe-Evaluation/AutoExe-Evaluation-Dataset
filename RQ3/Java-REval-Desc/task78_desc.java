public class Main {
    public static void sortedListSum(java.util.List<String> lst) {
        java.util.Collections.sort(lst);
        java.util.List<String> new_lst = new java.util.ArrayList<>();
        for (String i : lst) {
            if (i.length() % 2 == 0) {
                new_lst.add(i);
            }
        }
        java.util.List<String> _result = new_lst.stream().sorted(java.util.Comparator.comparingInt(String::length).thenComparing(String::compareTo)).toList();

        assert func(_result);  // POST: func is equivalent to: Write a function that accepts a list of strings as a parameter, deletes the strings that have odd lengths and returns the resulted list with a sorted order, The list is always a list of strings and never an array of numbers, and it may contain duplicates. The order of the list should be ascending by length of each word, and you should return the list sorted by that rule. If two words have the same length, sort the list alphabetically. The function should return a list of strings in sorted order. You may assume that all words will have the same length. For example: assert list_sort(["aa", "a", "aaa"]) => ["aa"] assert list_sort(["ab", "a", "aaa", "cd"]) => ["ab", "cd"]
    }
}