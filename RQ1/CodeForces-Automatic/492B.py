def main():
    # PRE:
    # Input Format:
    # The first line contains two integers n, l (1 ≤ n ≤ 1000, 1 ≤ l ≤ 109) — the number of lanterns and the length of the street respectively. The next line contains n integers ai (0 ≤ ai ≤ l). Multiple lanterns can be located at the same point. The lanterns may be located at the ends of the street.
    # POST:
    # Program Description:
    # Vanya walks late at night along a straight street of length l, lit by n lanterns. Consider the coordinate system with the beginning of the street corresponding to the point 0, and its end corresponding to the point l. Then the i-th lantern is at the point ai. The lantern lights all points of the street that are at the distance of at most d from it, where d is some positive number, common for all lanterns. Vanya wonders: what is the minimum light radius d should the lanterns have to light the whole street?
    # Output Format:
    # Print the minimum light radius d, needed to light the whole street. The answer will be considered correct if its absolute or relative error doesn't exceed 10 - 9.
    n, l = map(int, input().split())
    locs = sorted(list(map(int, input().split())))
    maxDiff = 0
    
    for i in range(len(locs)-1):
          if locs[i+1]-locs[i] > maxDiff:
                maxDiff = locs[i+1]-locs[i]            
    
    distance = maxDiff / 2
    leftEdge = min(locs)
    rightEdge = l - max(locs) # l (L) is the input we took from the user
    
    if distance < leftEdge or distance < rightEdge:
          distance = max(leftEdge, rightEdge)
          
    print(distance)
