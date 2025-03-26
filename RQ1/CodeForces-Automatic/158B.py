def main():
    # PRE:
    # Input Format:
    # The first line contains integer n (1 ≤ n ≤ 105) — the number of groups of schoolchildren. The second line contains a sequence of integers s1, s2, ..., sn (1 ≤ si ≤ 4). The integers are separated by a space, si is the number of children in the i-th group.
    # POST:
    # Program Description:
    # After the lessons n groups of schoolchildren went outside and decided to visit Polycarpus to celebrate his birthday. We know that the i-th group consists of si friends (1 ≤ si ≤ 4), and they want to go to Polycarpus together. They decided to get there by taxi. Each car can carry at most four passengers. What minimum number of cars will the children need if all members of each group should ride in the same taxi (but one taxi can take more than one group)?
    # Output Format:
    # Print the single number — the minimum number of taxis necessary to drive all children to Polycarpus.
    n = int(input())
    groups = input()
    
    count = {}
    count[1] = groups.count('1')
    count[2] = groups.count('2')
    count[3] = groups.count('3')
    count[4] = groups.count('4')
    
    total = count[4] + count[3] + count[2] // 2
    count[1] -= count[3]
    
    if (count[2] % 2 == 1):
          total += 1;
          count[1] -= 2;
    
    if (count[1] > 0):
          total += (count[1] + 3) // 4;
    
    print(total)
