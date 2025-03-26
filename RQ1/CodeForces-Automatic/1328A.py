def main():
    # PRE:
    # Input Format:
    # The first line of the input contains one integer t (1 \le t \le 10^4) — the number of test cases. Then t test cases follow.The only line of the test case contains two integers a and b (1 \le a, b \le 10^9).
    # POST:
    # Program Description:
    # You are given two positive integers a and b. In one move you can increase a by 1 (replace a with a+1). Your task is to find the minimum number of moves you need to do in order to make a divisible by b. It is possible, that you have to make 0 moves, as a is already divisible by b. You have to answer t independent test cases.
    # Output Format:
    # For each test case print the answer — the minimum number of moves you need to do in order to make a divisible by b.
    n = int(input())
    
    for _ in range(n):
          a, b = map(int, input().split())
          c = (a + b) - (a % b) # closest integer that is greater than a 
          print(c - a) if a % b != 0 else print(0)
