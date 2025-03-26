public class Translation {
    private static int getStrength(String s) {
        int upperCount = 0;
        int lowerCount = 0;
        for (char c : s.toCharArray()) {
            if (Character.isUpperCase(c)) {
                upperCount++;
            } else if (Character.isLowerCase(c)) {
                lowerCount++;
            }
        }
        return upperCount - lowerCount;
    }

    public static String Strongest_Extension(String class_name, String[] extensions) {
        String strong = extensions[0];
        int my_val = getStrength(extensions[0]);
        for (String s : extensions) {
            int val = getStrength(s);
            if (val > my_val) {
                strong = s;
                my_val = val;
            }
        }
        String ans = class_name + "." + strong;
        String _result = ans;

        assert func(_result);  // POST: func is equivalent to: You will be given the name of a class (a string) and a list of extensions. The extensions are to be used to load additional classes to the class. The strength of the extension is as follows: Let CAP be the number of the uppercase letters in the extension's name, and let SM be the number of lowercase letters in the extension's name, the strength is given by the fraction CAP - SM. You should find the strongest extension and return a string in this format: ClassName.StrongestExtensionName. If there are two or more extensions with the same strength, you should choose the one that comes first in the list. For example, if you are given "Slices" as the class and a list of the extensions: ['SErviNGSliCes', 'Cheese', 'StuFfed'] then you should return 'Slices.SErviNGSliCes' since 'SErviNGSliCes' is the strongest extension (its strength is -1). Example: for Strongest_Extension('my_class', ['AA', 'Be', 'CC']) == 'my_class.AA'
    }
}
