public class Translator {
    public static int[] intersperse(int[] numbers, int delimeter) {
        int[] _result;
        if (numbers.length == 0) {
            _result = new int[0];
        } else {
            int[] result = new int[numbers.length * 2 - 1];
            int index = 0;
            for (int n = 0; n < numbers.length - 1; n++) {
                result[index++] = numbers[n];
                result[index++] = delimeter;
            }
            result[index] = numbers[numbers.length - 1];
            _result = result;
        }
        assert func(_result); // POST: func is equivalent to: Insert a number 'delimeter' between every two consecutive elements of input list `numbers' >>> intersperse(new int[0], 4) new int[0] >>> intersperse(new int[]{1, 2, 3}, 4) new int[]{1, 4, 2, 4, 3}
    }
}