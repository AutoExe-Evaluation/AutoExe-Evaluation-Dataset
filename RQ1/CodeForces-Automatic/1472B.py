def main():
    # PRE:
    # Input Format:
    # The first line contains one integer t (1 \le t \le 10^4) — the number of test cases. Then t test cases follow.The first line of each test case contains an integer n (1 \le n \le 100) — the number of candies that Alice and Bob received.The next line contains n integers a_1, a_2, \ldots, a_n — the weights of the candies. The weight of each candy is either 1 or 2.It is guaranteed that the sum of n over all test cases does not exceed 10^5.
    # POST:
    # Program Description:
    # Alice and Bob received n candies from their parents. Each candy weighs either 1 gram or 2 grams. Now they want to divide all candies among themselves fairly so that the total weight of Alice's candies is equal to the total weight of Bob's candies.Check if they can do that.Note that candies are not allowed to be cut in half.
    # Output Format:
    # For each test case, output on a separate line:   "YES", if all candies can be divided into two sets with the same weight;  "NO" otherwise. You can output "YES" and "NO" in any case (for example, the strings yEs, yes, Yes and YES will be recognized as positive).
    t = int(input())
    
    for _ in range(t):
          n = int(input())
          weights = list(map(int, input().split()))
          if sum(weights) % 2 == 0:
                target = sum(weights) // 2
                c = 0
                temp = weights.copy()
                for weight in sorted(weights, reverse=True):
                      if c + weight <= target:
                            c += weight
                            temp.pop(temp.index(weight))
          
                if sum(temp) == target:
                      print('YES')
                else:
                      print('NO')
          else:
                print('NO')
