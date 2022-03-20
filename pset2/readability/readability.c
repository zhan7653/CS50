#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_grade(char *s);

int main(void)
{
    // get input text
    char *s = get_string("Text:");
    float grade = get_grade(s);
    long grade_round = lroundf(grade);
    if (grade_round >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade_round < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %ld\n", grade_round);
    }
}


// compute the grade of text
float get_grade(char *s)
{
    int letter = 0;
    int sentence = 0;
    int word = 0;
    float grade = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            letter++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentence++;
        }
        else if (s[i] == ' ') // each word matchs a ' ' (maybe after punctuation)
        {
            word++;
        }
    }
    word++; // the last word didn't end with ' '
    
    grade = (5.88 * letter) / word - (29.6 * sentence) / word - 15.8;
    return grade;
}