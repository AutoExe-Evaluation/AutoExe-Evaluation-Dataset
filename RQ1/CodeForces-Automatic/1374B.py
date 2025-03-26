def main():
    # PRE:
    # Input Format:
    # The first line of the input contains one integer t (1 \le t \le 2 \cdot 10^4) — the number of test cases. Then t test cases follow. The only line of the test case contains one integer n (1 \le n \le 10^9).
    # POST:
    # Program Description:
    # You are given an integer n. In one move, you can either multiply n by two or divide n by 6 (if it is divisible by 6 without the remainder).Your task is to find the minimum number of moves needed to obtain 1 from n or determine if it's impossible to do that.You have to answer t independent test cases.
    # Output Format:
    # For each test case, print the answer — the minimum number of moves needed to obtain 1 from n if it's possible to do that or -1 if it's impossible to obtain 1 from n.
    t = int(input())
    
    for _ in range(t):
          n = int(input())
          count = 0
          while n > 1 and n <= 10**9:
                if n % 6 == 0:
                      n //= 6
                else:
                      n *= 2
                count += 1
    
          print(-1) if n >= 10**9 else print(count)
