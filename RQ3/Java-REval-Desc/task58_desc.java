public class DateValidator {
    public static void valid_date(String date) {
        boolean _result = true;
        date = date.trim();
        String[] mdy = date.split("-");
        int month = Integer.parseInt(mdy[0]);
        int day = Integer.parseInt(mdy[1]);
        int year = Integer.parseInt(mdy[2]);
        if (month < 1 || month > 12) {
            _result = false;
        }
        if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day < 1 || day > 31)) {
            _result = false;
        }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && (day < 1 || day > 30)) {
            _result = false;
        }
        if (month == 2 && (day < 1 || day > 29)) {
            _result = false;
        }

        assert func(_result);  // POST: func is equivalent to: You have to write a function which validates a given date string and returns True if the date is valid otherwise False. The date is valid if all of the following rules are satisfied: 1. The date string is not empty. 2. The number of days is not less than 1 or higher than 31 days for months 1,3,5,7,8,10,12. And the number of days is not less than 1 or higher than 30 days for months 4,6,9,11. And, the number of days is not less than 1 or higher than 29 for the month 2. 3. The months should not be less than 1 or higher than 12. 4. The date should be in the format: mm-dd-yyyy for example: valid_date('03-11-2000') => True valid_date('15-01-2012') => False valid_date('04-0-2040') => False valid_date('06-04-2020') => True valid_date('06/04/2020') => False
    }
}