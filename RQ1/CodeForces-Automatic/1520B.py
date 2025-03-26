def main():
    # PRE:
    # Input Format:
    # The first line contains one integer t (1 \le t \le 10^4). Then t test cases follow.Each test case is characterized by one integer n (1 \le n \le 10^9).
    # POST:
    # Program Description:
    # Let's call a positive integer n ordinary if in the decimal notation all its digits are the same. For example, 1, 2 and 99 are ordinary numbers, but 719 and 2021 are not ordinary numbers.For a given number n, find the number of ordinary numbers among the numbers from 1 to n.
    # Output Format:
    # For each test case output the number of ordinary numbers among numbers from 1 to n.
    t = int(input())
    
    for i in range(t):
        n = int(input())
        l = len(str(n))
        print(9*(l-1) + n//int('1'*l))
