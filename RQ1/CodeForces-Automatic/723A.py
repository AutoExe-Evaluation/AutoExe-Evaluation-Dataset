def main():
    # PRE:
    # Input Format:
    # The first line of the input contains three distinct integers x1, x2 and x3 (1 ≤ x1, x2, x3 ≤ 100) — the coordinates of the houses of the first, the second and the third friends respectively.
    # POST:
    # Program Description:
    # There are three friend living on the straight line Ox in Lineland. The first friend lives at the point x1, the second friend lives at the point x2, and the third friend lives at the point x3. They plan to celebrate the New Year together, so they need to meet at one point. What is the minimum total distance they have to travel in order to meet at some point and celebrate the New Year?It's guaranteed that the optimal answer is always integer.
    # Output Format:
    # Print one integer — the minimum total distance the friends need to travel in order to meet together.
    x1, x2, x3 = sorted(map(int, input().split()))
    
    d1 = abs((x3-x1)+(x2-1))
    d2 = abs((x2-x1)+(x3-x2))
    
    print(min(d1,d2))
