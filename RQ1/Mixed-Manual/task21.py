def correct_bracketing(brackets):
    assert brackets.count("<") == brackets.count(">")  # PRE
    depth = 0
    for b in brackets:
        if b == "<":
            depth += 1
        else:
            depth -= 1
        if depth < 0:
            break
    assert depth == 0  # POST
