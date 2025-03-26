def main():
    # PRE:
    # Input Format:
    # The only line of the input contains two integers a and b (1 ≤ a ≤ b ≤ 10) — the weight of Limak and the weight of Bob respectively.
    # POST:
    # Program Description:
    # Bear Limak wants to become the largest of bears, or at least to become larger than his brother Bob.Right now, Limak and Bob weigh a and b respectively. It's guaranteed that Limak's weight is smaller than or equal to his brother's weight.Limak eats a lot and his weight is tripled after every year, while Bob's weight is doubled after every year.After how many full years will Limak become strictly larger (strictly heavier) than Bob?
    # Output Format:
    # Print one integer, denoting the integer number of years after which Limak will become strictly larger than Bob.
    Limak, Bob = map(int, input().split())
    years = 0
    
    if Limak == Bob:
          years += 1
          print(years)
    else:
          while Limak <= Bob:
                Limak *= 3
                Bob *= 2
                years += 1
          print(years)
