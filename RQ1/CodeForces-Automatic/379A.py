def main():
    # PRE:
    # Input Format:
    # The single line contains two integers, a and b (1 ≤ a ≤ 1000; 2 ≤ b ≤ 1000).
    # POST:
    # Program Description:
    # Vasily the Programmer loves romance, so this year he decided to illuminate his room with candles.Vasily has a candles.When Vasily lights up a new candle, it first burns for an hour and then it goes out. Vasily is smart, so he can make b went out candles into a new candle. As a result, this new candle can be used like any other new candle.Now Vasily wonders: for how many hours can his candles light up the room if he acts optimally well? Help him find this number.
    # Output Format:
    # Print a single integer — the number of hours Vasily can light up the room for.
    a, b = map(int, input().split())
    candles = 0
    counter = 0
    
    while a > 0:
          candles += 1
          counter += 1
          if counter == b:
                a += 1
                counter = 0
          a -= 1 
    
    print(candles)
