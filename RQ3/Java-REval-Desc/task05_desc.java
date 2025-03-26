public class Solution {
    public static Tuple<Integer, Integer> sum_product(List<Integer> numbers) {
        int sum_value = 0;
        int prod_value = 1;

        for (int n : numbers) {
            sum_value += n;
            prod_value *= n;
        }
        Tuple<Integer, Integer> _result = new Tuple<>(sum_value, prod_value);

        assert func(_result);  // POST: func is equivalent to: For a given list of integers, return a tuple consisting of a sum and a product of all the integers in a list. Empty sum should be equal to 0 and empty product should be equal to 1. >>> sum_product([]) (0, 1) >>> sum_product([1, 2, 3, 4]) (10, 24)
    }
}