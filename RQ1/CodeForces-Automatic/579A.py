def main():
    # PRE:
    # Input Format:
    # The only line containing one integer x (1 ≤ x ≤ 109).
    # POST:
    # Program Description:
    # You are a lover of bacteria. You want to raise some bacteria in a box. Initially, the box is empty. Each morning, you can put any number of bacteria into the box. And each night, every bacterium in the box will split into two bacteria. You hope to see exactly x bacteria in the box at some moment. What is the minimum number of bacteria you need to put into the box across those days?
    # Output Format:
    # The only line containing one integer: the answer.
    x = int(input())
    c = 0
    
    while x != 0:
          if x % 2 == 1:
                c += 1
          x //= 2
          
    print(c)
    
