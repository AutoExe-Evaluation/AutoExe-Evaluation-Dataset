def correct_bracketing(brackets: str):
    """
    pre: brackets.count("<") == brackets.count(">")
    post: _ <= 0
    """
    depth = 0
    for b in brackets:
        if b == "<":
            depth += 1
        else:
            depth -= 1
        if depth < 0:
            break
    return depth
