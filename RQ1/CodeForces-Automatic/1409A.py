def main():
    # PRE:
    # Input Format:
    # The first line of the input contains one integer t (1 \le t \le 2 \cdot 10^4) — the number of test cases. Then t test cases follow.The only line of the test case contains two integers a and b (1 \le a, b \le 10^9).
    # POST:
    # Program Description:
    # You are given two integers a and b.In one move, you can choose some integer k from 1 to 10 and add it to a or subtract it from a. In other words, you choose an integer k \in [1; 10] and perform a := a + k or a := a - k. You may use different values of k in different moves.Your task is to find the minimum number of moves required to obtain b from a.You have to answer t independent test cases.
    # Output Format:
    # For each test case, print the answer: the minimum number of moves required to obtain b from a.
    n = int(input())
    
    for _ in range(n):
          a, b = map(int, input().split())
          diff = abs(a - b)
          if a == b:
                print(0)
          elif diff % 10 == 0:
                print(diff // 10)
          else:
                print(int((diff / 10) + 1))
