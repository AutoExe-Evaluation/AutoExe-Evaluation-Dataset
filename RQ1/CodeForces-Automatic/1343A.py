def main():
    # PRE:
    # Input Format:
    # The first line of the input contains one integer t (1 \le t \le 10^4) — the number of test cases. Then t test cases follow.The only line of the test case contains one integer n (3 \le n \le 10^9) — the number of candy wrappers Vova found. It is guaranteed that there is some positive integer x and integer k>1 that x + 2x + 4x + \dots + 2^{k-1} x = n.
    # POST:
    # Program Description:
    # Recently Vova found n candy wrappers. He remembers that he bought x candies during the first day, 2x candies during the second day, 4x candies during the third day, \dots, 2^{k-1} x candies during the k-th day. But there is an issue: Vova remembers neither x nor k but he is sure that x and k are positive integers and k > 1.Vova will be satisfied if you tell him any positive integer x so there is an integer k>1 that x + 2x + 4x + \dots + 2^{k-1} x = n. It is guaranteed that at least one solution exists. Note that k > 1.You have to answer t independent test cases.
    # Output Format:
    # Print one integer — any positive integer value of x so there is an integer k>1 that x + 2x + 4x + \dots + 2^{k-1} x = n.
    t = int(input())
    
    for i in range(t):
          n = int(input())
    
          for k in range(2, 10**9):
                x = n % (2**k-1)
                if x == 0:
                      print(int(n / (2**k-1)))
                      break
