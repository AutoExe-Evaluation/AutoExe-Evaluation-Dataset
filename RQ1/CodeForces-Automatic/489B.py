def main():
    # PRE:
    # Input Format:
    # The first line contains an integer n (1 ≤ n ≤ 100) — the number of boys. The second line contains sequence a1, a2, ..., an (1 ≤ ai ≤ 100), where ai is the i-th boy's dancing skill.Similarly, the third line contains an integer m (1 ≤ m ≤ 100) — the number of girls. The fourth line contains sequence b1, b2, ..., bm (1 ≤ bj ≤ 100), where bj is the j-th girl's dancing skill.
    # POST:
    # Program Description:
    # The Berland State University is hosting a ballroom dance in celebration of its 100500-th anniversary! n boys and m girls are already busy rehearsing waltz, minuet, polonaise and quadrille moves.We know that several boy&girl pairs are going to be invited to the ball. However, the partners' dancing skill in each pair must differ by at most one.For each boy, we know his dancing skills. Similarly, for each girl we know her dancing skills. Write a code that can determine the largest possible number of pairs that can be formed from n boys and m girls.
    # Output Format:
    # Print a single number — the required maximum possible number of pairs.
    n = int(input())
    boys = sorted(list(map(int, input().split())))
    m = int(input())
    girls = sorted(list(map(int, input().split())))
    pairs = 0
    
    for boy in boys:
          for girl in girls:
                if boy == girl:
                      pairs += 1
                      girls.remove(boy)
                      break
                      
                elif (boy + 1) == girl:
                      pairs += 1
                      girls.remove(boy+1)
                      break
                      
                elif (boy - 1) == girl:
                      pairs += 1
                      girls.remove(boy-1)
                      break
                
    print(pairs)
