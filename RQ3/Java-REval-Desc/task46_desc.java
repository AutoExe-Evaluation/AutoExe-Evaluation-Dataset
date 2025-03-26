public class Translator {
    public static void byLength(int[] arr) {
        java.util.Map<Integer, String> dic = new java.util.HashMap<>();
        dic.put(1, "One");
        dic.put(2, "Two");
        dic.put(3, "Three");
        dic.put(4, "Four");
        dic.put(5, "Five");
        dic.put(6, "Six");
        dic.put(7, "Seven");
        dic.put(8, "Eight");
        dic.put(9, "Nine");
        
        java.util.Arrays.sort(arr);
        java.util.List<String> newArr = new java.util.ArrayList<>();
        for (int i = arr.length - 1; i >= 0; i--) {
            if (dic.containsKey(arr[i])) {
                newArr.add(dic.get(arr[i]));
            }
        }
        String[] result = newArr.toArray(new String[0]);

        assert func(result); // POST: func is equivalent to: Given an array of integers, sort the integers that are between 1 and 9 inclusive, reverse the resulting array, and then replace each digit by its corresponding name "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine". For example: arr = [2, 1, 1, 4, 5, 8, 2, 3] -> sort arr -> [1, 1, 2, 2, 3, 4, 5, 8] -> reverse arr -> [8, 5, 4, 3, 2, 2, 1, 1] return ["Eight", "Five", "Four", "Three", "Two", "Two", "One", "One"] If the array is empty, return an empty array: arr = [] return [] If the array has any strange number ignore it: arr = [1, -1 , 55] -> sort arr -> [-1, 1, 55] -> reverse arr -> [55, 1, -1] return = ['One']
    }
}