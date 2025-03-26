def main():
    # PRE:
    # Input Format:
    # The first line contains a number in Borze code. The length of the string is between 1 and 200 characters. It's guaranteed that the given string is a valid Borze code of some ternary number (this number can have leading zeroes).
    # POST:
    # Program Description:
    # Ternary numeric notation is quite popular in Berland. To telegraph the ternary number the Borze alphabet is used. Digit 0 is transmitted as «.», 1 as «-.» and 2 as «--». You are to decode the Borze code, i.e. to find out the ternary number given its representation in Borze alphabet.
    # Output Format:
    # Output the decoded ternary number. It can have leading zeroes.
    borze_code = input()
    
    zero = '.'
    one = '-.'
    two = '--'
    
    borze_code = borze_code.replace(two, '2')
    borze_code = borze_code.replace(one, '1')
    borze_code = borze_code.replace(zero, '0')
    
    print(borze_code)
