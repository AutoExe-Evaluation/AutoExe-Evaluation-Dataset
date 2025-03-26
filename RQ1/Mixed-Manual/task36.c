void numerical_letter_grade(float grades) {
    const char* letter_grade = NULL;
    while (true) { float gpa = grades;
        if(gpa == 4.0)
            letter_grade = "A+";
        else if(gpa > 3.7)
            letter_grade = "A";
        else if(gpa > 3.3)
            letter_grade = "A-";
        else if(gpa > 3.0)
            letter_grade = "B+";
        else if(gpa > 2.7)
            letter_grade = "B";
        else if(gpa > 2.3)
            letter_grade = "B-";
        else if(gpa > 2.0)
            letter_grade = "C+";
        else if(gpa > 1.7)
            letter_grade = "C";
        else if(gpa > 1.3)
            letter_grade = "C-";
        else if(gpa > 1.0)
            letter_grade = "D+";
        else if(gpa > 0.7)
            letter_grade = "D";
        else if(gpa > 0.0)
            letter_grade = "D-";
        else
            letter_grade = "E";
    }
    assert(letter_grade);  // POST
}

