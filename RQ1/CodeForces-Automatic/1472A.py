def main():
    # PRE:
    # Input Format:
    # The first line contains one integer t (1 \le t \le 10^4) — the number of test cases. Then t test cases follow.Each test case consists of one line containing three integers w, h, n (1 \le w, h \le 10^4, 1 \le n \le 10^9) — the width and height of the sheet Polycarp has and the number of friends he needs to send a postcard to.
    # POST:
    # Program Description:
    # For the New Year, Polycarp decided to send postcards to all his n friends. He wants to make postcards with his own hands. For this purpose, he has a sheet of paper of size w \times h, which can be cut into pieces.Polycarp can cut any sheet of paper w \times h that he has in only two cases:   If w is even, then he can cut the sheet in half and get two sheets of size \frac{w}{2} \times h;  If h is even, then he can cut the sheet in half and get two sheets of size w \times \frac{h}{2}; If w and h are even at the same time, then Polycarp can cut the sheet according to any of the rules above.After cutting a sheet of paper, the total number of sheets of paper is increased by 1.Help Polycarp to find out if he can cut his sheet of size w \times h at into n or more pieces, using only the rules described above.
    # Output Format:
    # For each test case, output on a separate line:   "YES", if it is possible to cut a sheet of size w \times h into at least n pieces;  "NO" otherwise. You can output "YES" and "NO" in any case (for example, the strings yEs, yes, Yes and YES will be recognized as positive).
    t = int(input())
    
    for _ in range(t):
          w, h, n = map(int, input().split())
          m = 1
    
          while w > 0 or h > 0:
                if w % 2 == 0:
                      w //= 2
                      m *= 2
                elif h % 2 == 0:
                      h //= 2
                      m *= 2
                else:
                      break
          print('YES') if m >= n else print('NO')
