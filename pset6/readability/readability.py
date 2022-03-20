from cs50 import get_string


def main():
    text = get_string("Text:")
    grade = get_grade(text)
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")
    
    
def get_grade(s):
    letter = 0
    sentence = 0
    word = 0
    grade = 0
    for i in range(len(s)):
        if s[i].isalpha():
            letter += 1
        elif (s[i] == '.' or s[i] == '!' or s[i] == '?'):
            sentence += 1
        elif s[i] == ' ':
            word += 1
    word += 1
    
    grade = (5.88 * letter) / word - (29.6 * sentence) / word - 15.8
    return round(grade)


if __name__ == "__main__":
    main()