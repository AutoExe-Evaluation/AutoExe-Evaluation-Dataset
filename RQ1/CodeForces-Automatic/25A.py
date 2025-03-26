def main():
    # PRE:
    # Input Format:
    # The first line contains integer n (3 ≤ n ≤ 100) — amount of numbers in the task. The second line contains n space-separated natural numbers, not exceeding 100. It is guaranteed, that exactly one of these numbers differs from the others in evenness.
    # POST:
    # Program Description:
    # Bob is preparing to pass IQ test. The most frequent task in this test is to find out which one of the given n numbers differs from the others. Bob observed that one number usually differs from the others in evenness. Help Bob — to check his answers, he needs a program that among the given n numbers finds one that is different in evenness.
    # Output Format:
    # Output index of number that differs from the others in evenness. Numbers are numbered from 1 in the input order.
    n = int(input())
    nums = list(map(int, input().split()))
    loc = {}
    
    for idx, val in enumerate(nums):
          if val % 2 == 0:
                loc[idx] = True 
          else:
                loc[idx] = False
                
    if sum(loc.values()) > 1:
          for k, v in loc.items():
                if v == False:
                      print(k+1)
    else:
          for k, v in loc.items():
                if v == True:
                      print(k+1)
                
    
    
    
    
