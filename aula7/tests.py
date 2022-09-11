# Understand how to learn other languages, understanding its similar structures
# Python - faster to write the code, slower to run
print('oi')
my_var_with_auto_type = f"{2 + 2} = " + "2 + 2"
if 2 + 2 == 4 and 1 + 1 == 2 or 3 * 3 == 9:
    print(f'math: {my_var_with_auto_type}')
while True:
    print("for")
    for i in range(3): # 0 > 2
        print(i)
    break

from cgi import print_form
import cs50 as cs
# python {code_file.py} > interpreter not compiled for the programmer

from PIL import ImageFilter, Image
target_image = input("Image file to find edges: ")
if target_image[-4:] != ".bmp":
    target_image = "test.bmp"
before = Image.open(target_image) # if we import just PIL, would be PIL.Image.open > PIL'd be a namespace
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")

while True: # copy of do-while
    try:
        x = int(input("x: ").capitalize()) # .capitalize() just to show we can do this logic
        print(f"{x} + 10 = {x + 10}")
        x /= 10 # division could be an float, even with only ints
        x //= 10 # division as in c
        break
    except ValueError:
        print("please, put a number as 1")

# with main we will can declare other used functions after main code
def main():
    meow(1)


def meow(n):
    for i in range(n):
        print('meow')

if __name__ == "__main__": # solve problems when creating libraries
    main()

list_1 = [1, 2] + [3]
for c in list_1:
    print(c)

if 2 in list_1:
    print("Found using binary search")

import csv    
name = input("Name: ")
phone = input("Phone: ")
with open("phonebook.csv", 'a') as file: # close the file for you - file.close()
    writer = csv.writer(file) # reader returns an iterator or DictReader to return a dict with key == column name
    writer.writerow([name, phone])
    file.close()

import pyttsx3
engine = pyttsx3.init()
engine.say(f"Hello, {name}")
engine.runAndWait()

import sys
from sys import argv
sys.exit(0)
