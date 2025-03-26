def main():
    # PRE:
    # Input Format:
    # The single line contains two numbers, n and t (1 ≤ n ≤ 100, 2 ≤ t ≤ 10) — the length of the number and the number it should be divisible by.
    # POST:
    # Program Description:
    # Olesya loves numbers consisting of n digits, and Rodion only likes numbers that are divisible by t. Find some number that satisfies both of them.Your task is: given the n and t print an integer strictly larger than zero consisting of n digits that is divisible by t. If such number doesn't exist, print  - 1.
    # Output Format:
    # Print one such positive number without leading zeroes, — the answer to the problem, or  - 1, if such number doesn't exist. If there are multiple possible answers, you are allowed to print any of them.
    n, t = map(int, input().split())
    i = int('1' +'0' * (n - 1))
    j = int('1' +'0' * n)
    
    ans = 0
    for num in range(i, j):
          if num % t == 0:
                ans = num
                break
    
    print(-1) if ans == 0 else print(ans)
