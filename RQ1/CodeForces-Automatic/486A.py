def main():
    # PRE:
    # Input Format:
    # The single line contains the positive integer n (1 ≤ n ≤ 1015).
    # POST:
    # Program Description:
    # For a positive integer n let's define a function f:f(n) =  - 1 + 2 - 3 + .. + ( - 1)nn Your task is to calculate f(n) for a given integer n.
    # Output Format:
    # Print f(n) in a single line.
    n = int(input())
    
    if n % 2 == 0:
          print(n // 2)
    else:
          print(-1*(n+1)//2)
    
    
