def valid_date(date: str):
    """
    pre: date in ["06-04-2024", "01-01-2020", "12-31-1999"]
    post: _
    """
    answer = True
    date = date.strip()
    month_day_year = date.split('-')
    month = int(month_day_year[0])
    day = int(month_day_year[1])
    year = int(month_day_year[2])
    if month < 1 or month > 12:
        answer = False
    if month in [1,3,5,7,8,10,12] and (day < 1 or day > 31):
        answer = False
    if month in [4,6,9,11] and (day < 1 or day > 30):
        answer = False
    if month == 2 and (day < 1 or day > 29):
        answer = False
    return answer
