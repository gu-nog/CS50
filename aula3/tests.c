/*
    bool - 1 byte instead of 1 bit for simplicity
    char - 1 byte
    double - 8 bytes
    float - 4 bytes
    int - 4 bytes
    long int - 8 bytes
    string - ?
    Stored in RAM memory in an matrix structure
*/
#include <stdio.h>
#include <cs50.h>
#include <string.h>
// library with good functions as strlen that iterates in the string until the NUL byte to return the lenth of it
#include <ctype.h> // islower(string) false > 0 or true > != 0 and toupper()

string uppercase(string);

// it returns an error code int, that you can return 1 to break it because sth went wrong or 0 if works well, 
// or any other to specific errors
int main(int argc, string argv[]) { // it receives the CLI arguments, arg counter and a vector with them > 
    // (null) if you try to access inexistent index of param, else a string of which is write separated by " "s

    printf("result 1(only integers > integer): %i\n", (5 + 7 + 2) / 3);
    printf("result 2(at least one float > float): %.1f\n", (5 + 7 + 2) / 3.0);
    // array: store many values of the same type declaring just one name/variable
    int values[3]; // indexes: 0-2
    values[0] = 3; // value at index/position/local in memory 0 is equal to 3
    // Tip: you can access them using loops
    // Convert values:
    values[0] = (int) 'a';
    // Strings are just arrays of chars:
    string hi = "Hi0";
    printf("%i %i %i %i\n", hi[0], hi[1], hi[2], hi[3]);
    // But in memory, how does the computer understand where one data start or end?
    // Delimitator NUL \0 > 0000 0000 or even the int 0
    // because of that char is also 1 byte, because then everything have a base space of 1 byte
    // But this is only for string that have a changeble length

    // But is not a good idea to everytime see all str to know its len, so we can store it in a variable

    // You can look at documentations / manual pages if there is already some function that do what you need
    // and how to it works
    printf("Uppercase(%s):\n", "test");
    uppercase("test");
}

string uppercase(string s){
    for (int i = 0, n=strlen(s); i < n; i++)
    {
        if (s[i] > 'a' && s[i] < 'z') {
            printf("%c", s[i] - 32); // because of ASCII table
        }
    }
    return s;
};
