public class Translation {
    public static void willItFly(int[] q, int w) {
        boolean _result = true;
        if (sum(q) > w) {
            _result = false;
        }

        int i = 0;
        int j = q.length - 1;
        while (i < j) {
            if (q[i] != q[j]) {
                _result = false;
            }
            i++;
            j--;
        }

        assert func(_result);  // POST: func is equivalent to: Write a function that returns True if the object q will fly, and False otherwise. The object q will fly if it's balanced (it is a palindromic list) and the sum of its elements is less than or equal the maximum possible weight w. Example: will_it_fly([1, 2], 5) ➞ False # 1+2 is less than the maximum possible weight, but it's unbalanced. will_it_fly([3, 2, 3], 1) ➞ False # it's balanced, but 3+2+3 is more than the maximum possible weight. will_it_fly([3, 2, 3], 9) ➞ True # 3+2+3 is less than the maximum possible weight, and it's balanced. will_it_fly([3], 5) ➞ True # 3 is less than the maximum possible weight, and it's balanced.
    }
}
