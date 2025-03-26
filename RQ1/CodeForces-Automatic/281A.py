def main():
    # PRE:
    # Input Format:
    # A single line contains a non-empty word. This word consists of lowercase and uppercase English letters. The length of the word will not exceed 103.
    # POST:
    # Program Description:
    # Capitalization is writing a word with its first letter as a capital letter. Your task is to capitalize the given word.Note, that during capitalization all the letters except the first one remains unchanged.
    # Output Format:
    # Output the given word after capitalization.
    word = input()
    
    new = ''
    
    new += word[0].capitalize() + word[1:]
    
    print(new)
