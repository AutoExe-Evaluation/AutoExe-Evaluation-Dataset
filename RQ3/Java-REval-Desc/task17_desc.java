public class Example {
    public static void change_base(int x, int base) {
        String ret = "";
        while (x > 0) {
            ret = (x % base) + ret;
            x /= base;
        }
        String _result = ret;

        assert func(_result);  // POST: func is equivalent to: Change numerical base of input number x to base. return string representation after the conversion. base numbers are less than 10. >>> change_base(8, 3) '22' >>> change_base(8, 2) '1000' >>> change_base(7, 2) '111'
    }
}