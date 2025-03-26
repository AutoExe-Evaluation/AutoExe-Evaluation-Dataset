def main():
    # PRE:
    # Input Format:
    # The only line contains an integer n (12 ≤ n ≤ 106).
    # POST:
    # Program Description:
    # One way to create a task is to learn from math. You can generate some random math statement or modify some theorems to get something new and build a new task from that.For example, there is a statement called the "Goldbach's conjecture". It says: "each even number no less than four can be expressed as the sum of two primes". Let's modify it. How about a statement like that: "each integer no less than 12 can be expressed as the sum of two composite numbers." Not like the Goldbach's conjecture, I can prove this theorem.You are given an integer n no less than 12, express it as a sum of two composite numbers.
    # Output Format:
    # Output two composite integers x and y (1 < x, y < n) such that x + y = n. If there are multiple solutions, you can output any of them.
    def checker(num: int) -> bool: #composite checker
          lst = [2, 3, 5, 7]
          if num not in lst:
                if num % 2 == 0 or num % 3 == 0 or num % 5 == 0:
                      return True
                else:
                      return False
          
    
    n = int(input())
    a = 4
    b = 0
    
    while a + b != n:
          b = n - a
          if not checker(b): # if b is not composite
                a += 1
                while not checker(a): # if a is not composite 
                      a += 1 # keep increasing until a becomes composite
                
          
          
    print(a, b)
    
