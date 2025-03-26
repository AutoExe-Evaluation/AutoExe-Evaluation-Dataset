public class RomanConverter {
    public static String int_to_mini_roman(int number) {
        int[] num = {1, 4, 5, 9, 10, 40, 50, 90,  
                     100, 400, 500, 900, 1000}; 
        String[] sym = {"I", "IV", "V", "IX", "X", "XL",  
                        "L", "XC", "C", "CD", "D", "CM", "M"}; 
        int i = 12;
        String res = "";
        while (number > 0) { 
            int div = number / num[i]; 
            number %= num[i]; 
            while (div > 0) { 
                res += sym[i]; 
                div -= 1;
            }
            i -= 1;
        }
        String _result = res.toLowerCase();

        assert func(_result);  // POST: func is equivalent to: Given a positive integer, obtain its roman numeral equivalent as a string, and return it in lowercase. Restrictions: 1 <= num <= 1000 Examples: >>> int_to_mini_roman(19) == 'xix' >>> int_to_mini_roman(152) == 'clii' >>> int_to_mini_roman(426) == 'cdxxvi'
    }
}