public class Main {
    public static void modp(int n, int p) {
        int ret = 1;
        for (int i = 0; i < n; i++) {
            ret = (2 * ret) % p;
        }
        int _result = ret;

        assert func(_result);  // POST: func is equivalent to: Return 2^n modulo p (be aware of numerics). >>> modp(3, 5) 3 >>> modp(1101, 101) 2 >>> modp(0, 101) 1 >>> modp(3, 11) 8 >>> modp(100, 101) 1
    }
}