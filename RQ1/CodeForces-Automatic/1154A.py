def main():
    # PRE:
    # Input Format:
    # The only line of the input contains four positive integers x_1, x_2, x_3, x_4 (2 \le x_i \le 10^9) — numbers written on a board in random order. It is guaranteed that the answer exists for the given number x_1, x_2, x_3, x_4.
    # POST:
    # Program Description:
    # Polycarp has guessed three positive integers a, b and c. He keeps these numbers in secret, but he writes down four numbers on a board in arbitrary order — their pairwise sums (three numbers) and sum of all three numbers (one number). So, there are four numbers on a board in random order: a+b, a+c, b+c and a+b+c.You have to guess three numbers a, b and c using given numbers. Print three guessed integers in any order.Pay attention that some given numbers a, b and c can be equal (it is also possible that a=b=c).
    # Output Format:
    # Print such positive integers a, b and c that four numbers written on a board are values a+b, a+c, b+c and a+b+c written in some order. Print a, b and c in any order. If there are several answers, you can print any. It is guaranteed that the answer exists.
    vals = list(map(int, input().split()))
    t = vals.pop(vals.index(max(vals)))
    x = vals[0]
    y = vals[1]
    z = vals[2]
    
    c = t - x
    a = y - c
    b = z - c
    
    print(a, b, c)
