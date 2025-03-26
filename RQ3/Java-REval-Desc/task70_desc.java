public class FileNameCheck {
    public static void file_name_check(String file_name) {
        String[] suf = {"txt", "exe", "dll"};
        String[] lst = file_name.split("\\.");
        String _result = "Yes";
        if (lst.length != 2) {
            _result = "No";
        }
        boolean isValidSuffix = false;
        for (String suffix : suf) {
            if (lst[1].equals(suffix)) {
                isValidSuffix = true;
                break;
            }
        }
        if (!isValidSuffix) {
            _result = "No";
        }
        if (lst[0].length() == 0) {
            _result = "No";
        }
        if (!Character.isAlphabetic(lst[0].charAt(0))) {
            _result = "No";
        }
        long t = lst[0].chars().filter(Character::isDigit).count();
        if (t > 3) {
            _result = "No";
        }

        assert func(_result);  // POST: func is equivalent to: Create a function which takes a string representing a file's name, and returns 'Yes' if the file's name is valid, and returns 'No' otherwise. A file's name is considered to be valid if and only if all the following conditions are met: - There should not be more than three digits ('0'-'9') in the file's name. - The file's name contains exactly one dot '.' - The substring before the dot should not be empty, and it starts with a letter the latin alphapet ('a'-'z' and 'A'-'Z'). - The substring after the dot should be one of these: ['txt', 'exe', 'dll'] Examples: file_name_check("example.txt") # => 'Yes' file_name_check("1example.dll") # => 'No' (the name should start with a latin alphapet letter)
    }
}