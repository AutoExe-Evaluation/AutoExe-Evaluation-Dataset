def main():
    # PRE:
    # Input Format:
    # The first line of the input contains one integer t (1 \le t \le 100) — the number of test cases. Then t test cases follow.The only line of the test case contains one integer n (2 \le n \le 100) — the length of the permutation you have to find.
    # POST:
    # Program Description:
    # You are given one integer n (n > 1).Recall that a permutation of length n is an array consisting of n distinct integers from 1 to n in arbitrary order. For example, [2, 3, 1, 5, 4] is a permutation of length 5, but [1, 2, 2] is not a permutation (2 appears twice in the array) and [1, 3, 4] is also not a permutation (n = 3 but there is 4 in the array).Your task is to find a permutation p of length n that there is no index i (1 \le i \le n) such that p_i = i (so, for all i from 1 to n the condition p_i \ne i should be satisfied).You have to answer t independent test cases.If there are several answers, you can print any. It can be proven that the answer exists for each n > 1.
    # Output Format:
    # For each test case, print n distinct integers p_1, p_2, \ldots, p_n — a permutation that there is no index i (1 \le i \le n) such that p_i = i (so, for all i from 1 to n the condition p_i \ne i should be satisfied).If there are several answers, you can print any. It can be proven that the answer exists for each n > 1.
    t = int(input())
    
    for _ in range(t):
          p = [*range(int(input()), 0, -1)]
          if len(p) > 2:
                t = p[len(p)//2]
                p[len(p)//2] = p[len(p)//2 + 1]
                p[len(p)//2 + 1] = t
                print(*p)
          else:
                print(*p)
