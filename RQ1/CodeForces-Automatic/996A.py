def main():
    # PRE:
    # Input Format:
    # The first and only line of input contains a single integer n (1 \le n \le 10^9).
    # POST:
    # Program Description:
    # Allen has a LOT of money. He has n dollars in the bank. For security reasons, he wants to withdraw it in cash (we will not disclose the reasons here). The denominations for dollar bills are 1, 5, 10, 20, 100. What is the minimum number of bills Allen could receive after withdrawing his entire balance?
    # Output Format:
    # Output the minimum number of bills that Allen could receive.
    n = int(input())
    bills = [100, 20, 10, 5, 1]
    c = 0
    
    while n > 0:
          if (n >= bills[0]) and (n % bills[0] != n):
                c =c + (n // bills[0])
                n %= bills[0]
          else:
                bills.pop(0)
    
    print(c)
    
    
