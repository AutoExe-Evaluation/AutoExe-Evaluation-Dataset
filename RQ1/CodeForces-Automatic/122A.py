def main():
    # PRE:
    # Input Format:
    # The single line contains an integer n (1 ≤ n ≤ 1000) — the number that needs to be checked.
    # POST:
    # Program Description:
    # Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.Petya calls a number almost lucky if it could be evenly divided by some lucky number. Help him find out if the given number n is almost lucky.
    # Output Format:
    # In the only line print "YES" (without the quotes), if number n is almost lucky. Otherwise, print "NO" (without the quotes).
    s = input()
    n = int(s)
    
    if n % 4 ==0 or n % 7 == 0 or n % 47 == 0:
          print('YES')
    else:
          s = s.replace('4', '')
          s = s.replace('7', '')
          if s == '':
                print('YES')
          else:
                print('NO')
    
    
    
    
    
    
