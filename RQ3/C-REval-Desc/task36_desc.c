void numerical_letter_grade(float grades[], int size, char letter_grade[][3]) {
    for (int i = 0; i < size; i++) {
        float gpa = grades[i];
        if (gpa == 4.0) {
            strcpy(letter_grade[i], "A+");
        } else if (gpa > 3.7) {
            strcpy(letter_grade[i], "A");
        } else if (gpa > 3.3) {
            strcpy(letter_grade[i], "A-");
        } else if (gpa > 3.0) {
            strcpy(letter_grade[i], "B+");
        } else if (gpa > 2.7) {
            strcpy(letter_grade[i], "B");
        } else if (gpa > 2.3) {
            strcpy(letter_grade[i], "B-");
        } else if (gpa > 2.0) {
            strcpy(letter_grade[i], "C+");
        } else if (gpa > 1.7) {
            strcpy(letter_grade[i], "C");
        } else if (gpa > 1.3) {
            strcpy(letter_grade[i], "C-");
        } else if (gpa > 1.0) {
            strcpy(letter_grade[i], "D+");
        } else if (gpa > 0.7) {
            strcpy(letter_grade[i], "D");
        } else if (gpa > 0.0) {
            strcpy(letter_grade[i], "D-");
        } else {
            strcpy(letter_grade[i], "E");
        }
    }
    assert(func(letter_grade));  
}