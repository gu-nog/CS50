import re
text = input("Text: ")
words = text.count(' ') + 1
letters = len(text) - len(re.sub(r'[a-z]', '', re.sub(r'[A-Z]', '', text)))
sentences = text.count(".") + text.count('!') + text.count("?")
grade = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8
if grade >= 16:
    print('Grade 16+')
elif grade <= 0:
    print('Before Grade 1')
else:
    print(f"Grade {round(grade)}")