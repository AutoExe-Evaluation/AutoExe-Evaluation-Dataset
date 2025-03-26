def main():
    # PRE:
    # Input Format:
    # The only line of the input contains a single integer n (1 ≤ n ≤ 100) — the number of layers of love and hate.
    # POST:
    # Program Description:
    # Dr. Bruce Banner hates his enemies (like others don't). As we all know, he can barely talk when he turns into the incredible Hulk. That's why he asked you to help him to express his feelings.Hulk likes the Inception so much, and like that his feelings are complicated. They have n layers. The first layer is hate, second one is love, third one is hate and so on...For example if n = 1, then his feeling is "I hate it" or if n = 2 it's "I hate that I love it", and if n = 3 it's "I hate that I love that I hate it" and so on.Please help Dr. Banner.
    # Output Format:
    # Print Dr.Banner's feeling in one line.
    n = int(input())
    edgeOdd= 'I hate it'
    edgeEven = 'I love it'
    middleOdd = 'I hate that'
    middleEven = 'I love that'
    
    for i in range(1, n+1):
          if n == 1:
                print(edgeOdd, end=' ')
          elif i == range(n+1)[-1]:
                print(edgeEven, end=' ') if range(n+1)[-1] % 2 == 0 else print(edgeOdd, end=' ')
          else:
                print(middleEven, end=' ') if i % 2 == 0 else print(middleOdd, end=' ')
          
    
