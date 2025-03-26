def main():
    # PRE:
    # Input Format:
    # The only line of input contains integers n and k (1 ≤ k ≤ n ≤ 1012).Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specifier.
    # POST:
    # Program Description:
    # Being a nonconformist, Volodya is displeased with the current state of things, particularly with the order of natural numbers (natural number is positive integer number). He is determined to rearrange them. But there are too many natural numbers, so Volodya decided to start with the first n. He writes down the following sequence of numbers: firstly all odd integers from 1 to n (in ascending order), then all even integers from 1 to n (also in ascending order). Help our hero to find out which number will stand at the position number k.
    # Output Format:
    # Print the number that will stand at the position number k after Volodya's manipulations.
    from math import  floor
    n, k = map(int, input().split())
    
    odds = range(1, n+1, 2)
    evens = range(2, n+1, 2)
    
    try:
          print(odds[k-1])
    except IndexError:
          try:
                idx = k - len(odds)
                print(evens[idx-1])
          except OverflowError:
                try:
                      idx = k - floor(n/2)
                      print(evens[idx-1])
                except IndexError:
                      print(evens[idx-2])
