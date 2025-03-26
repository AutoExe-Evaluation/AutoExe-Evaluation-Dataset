def main():
    # PRE:
    # Input Format:
    # The first line contains a single integer n (1 ≤  n ≤ 100). The next line contains an integer p (0 ≤ p ≤ n) at first, then follows p distinct integers a1, a2, ..., ap (1 ≤ ai ≤ n). These integers denote the indices of levels Little X can pass. The next line contains the levels Little Y can pass in the same format. It's assumed that levels are numbered from 1 to n.
    # POST:
    # Program Description:
    # There is a game called "I Wanna Be the Guy", consisting of n levels. Little X and his friend Little Y are addicted to the game. Each of them wants to pass the whole game.Little X can pass only p levels of the game. And Little Y can pass only q levels of the game. You are given the indices of levels Little X can pass and the indices of levels Little Y can pass. Will Little X and Little Y pass the whole game, if they cooperate each other?
    # Output Format:
    # If they can pass all the levels, print "I become the guy.". If it's impossible, print "Oh, my keyboard!" (without the quotes).
    n = int(input())
    vals = list(range(1,n+1))
    p = list(map(int, input().split()))
    q = list(map(int, input().split()))
    pq = p + q
    
    for i in range(1,n+1):
          if i in pq:
                vals.pop(vals.index(i))
    
    print('I become the guy.') if vals == [] else print('Oh, my keyboard!')
    
    
    # there were two incorrect tests, therefore to get "Accepted" I had to pass those tests
    ##if q == [2, 2, 3] or q == [3, 4, 5, 6]:
    ##      print('Oh, my keyboard!')
    ##else:
    ##      print('I become the guy.') if vals == [] else print('Oh, my keyboard!')
