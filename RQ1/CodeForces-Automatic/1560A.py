def main():
    # PRE:
    # Input Format:
    # The first line contains one integer t (1 \le t \le 100) — the number of test cases. Then t test cases follow.Each test case consists of one line containing one integer k (1 \le k \le 1000).
    # POST:
    # Program Description:
    # Polycarp doesn't like integers that are divisible by 3 or end with the digit 3 in their decimal representation. Integers that meet both conditions are disliked by Polycarp, too.Polycarp starts to write out the positive (greater than 0) integers which he likes: 1, 2, 4, 5, 7, 8, 10, 11, 14, 16, \dots. Output the k-th element of this sequence (the elements are numbered from 1).
    # Output Format:
    # For each test case, output in a separate line one integer x — the k-th element of the sequence that was written out by Polycarp.
    t = int(input())
    
    for _ in range(t):
          k = int(input())
          c = 0
          for n in range(1, 3000):
                if n % 3 != 0 and str(n)[-1] != '3': 
                      c += 1
                      if c == k:
                            print(n)
                            break
