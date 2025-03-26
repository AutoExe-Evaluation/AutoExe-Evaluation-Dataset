public class Example {
    public static void even_odd_count(int num) {
        int even_count = 0;
        int odd_count = 0;
        for (char i : String.valueOf(Math.abs(num)).toCharArray()) {
            if (Character.getNumericValue(i) % 2 == 0) {
                even_count += 1;
            } else {
                odd_count += 1;
            }
        }
        Object _result = new Object[]{even_count, odd_count};

        assert func(_result);  // POST: func is equivalent to: Given an integer. return a tuple that has the number of even and odd digits respectively. Example: even_odd_count(-12) ==> (1, 1) even_odd_count(123) ==> (1, 2)
    }
}