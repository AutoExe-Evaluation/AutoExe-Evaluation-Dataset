def correct_bracketing(brackets: str):
    depth = 0
    _result = True
    for b in brackets:
        if b == "<":
            depth += 1
        else:
            depth -= 1
        if depth < 0:
            _result = False
    if _result:
        _result = depth == 0

    assert func(_result)  # POST: func is equivalent to: brackets is a string of "<" and ">". return True if every opening bracket has a corresponding closing bracket. >>> correct_bracketing("<") False >>> correct_bracketing("<>") True >>> correct_bracketing("<<><>>") True >>> correct_bracketing("><<>") False
