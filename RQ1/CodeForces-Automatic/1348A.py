def main():
    # PRE:
    # Input Format:
    # The input consists of multiple test cases. The first line contains an integer t (1 \le t \le 100) — the number of test cases.The first line of each test case contains an integer n (2 \le n \le 30; n is even) — the number of coins that Phoenix has.
    # POST:
    # Program Description:
    # Phoenix has n coins with weights 2^1, 2^2, \dots, 2^n. He knows that n is even.He wants to split the coins into two piles such that each pile has exactly \frac{n}{2} coins and the difference of weights between the two piles is minimized. Formally, let a denote the sum of weights in the first pile, and b denote the sum of weights in the second pile. Help Phoenix minimize |a-b|, the absolute value of a-b.
    # Output Format:
    # For each test case, output one integer — the minimum possible difference of weights between the two piles.
    t  = int(input()) # test cases
    weight = lambda x: 2**x
    
    for _ in range(t):
          n = int(input())
          coins = [weight(i) for i in range(1, n+1)]
          a = []
          maxy = True
          for i in range(n//2): # this loop creates the first list which consists of one coin with max weight and the remaining are have min weight
                if maxy:
                      a.append(coins.pop(coins.index(max(coins))))
                      maxy = False
                else:
                      a.append(coins.pop(coins.index(min(coins))))
          
          print(sum(a) - sum(coins))
