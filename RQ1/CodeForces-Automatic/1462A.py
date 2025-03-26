def main():
    # PRE:
    # Input Format:
    # The first line contains a single positive integer t (1 \le t \le 300) — the number of test cases in the test. Then t test cases follow.The first line of each test case contains an integer n (1 \le n \le 300) — the length of the sequence written on the whiteboard.The next line contains n integers b_1, b_2,\ldots, b_n (1 \le b_i \le 10^9) — the sequence written on the whiteboard.
    # POST:
    # Program Description:
    # Polycarp has a favorite sequence a[1 \dots n] consisting of n integers. He wrote it out on the whiteboard as follows:  he wrote the number a_1 to the left side (at the beginning of the whiteboard);  he wrote the number a_2 to the right side (at the end of the whiteboard);  then as far to the left as possible (but to the right from a_1), he wrote the number a_3;  then as far to the right as possible (but to the left from a_2), he wrote the number a_4;  Polycarp continued to act as well, until he wrote out the entire sequence on the whiteboard.   The beginning of the result looks like this (of course, if n \ge 4). For example, if n=7 and a=[3, 1, 4, 1, 5, 9, 2], then Polycarp will write a sequence on the whiteboard [3, 4, 5, 2, 9, 1, 1].You saw the sequence written on the whiteboard and now you want to restore Polycarp's favorite sequence.
    # Output Format:
    # Output t answers to the test cases. Each answer — is a sequence a that Polycarp wrote out on the whiteboard.
    t = int(input())
    
    for _ in range(t):
          n = int(input())
          old = list(map(int, input().split()))
          new = []
          i = 0
          for  i in range(n):
                if i % 2 == 0:
                      new.append(old.pop(0))
                else:
                      new.append(old.pop())
          print(' '.join(map(str, new)))
