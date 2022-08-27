#include <cs50.h>
#include <stdio.h> // library with some extra native-functions as printf > for input and output in this case

void next_line(void); // just a prototype before we call it but withou implementing yet

long int by_2(long int a){
    return a / 2;
}

int pennies_to_dollars(float pennies){
    return (int) 0;// round(pennies * 100); // this round is because, for example, the result could be 419.9999, which 
    // would give us 419 instead of 420, this is because maybe the computer could for example store the 420 as this
    // 419.999
    // round is from math.h
}

int main(void){ // where the c's compiler start running the code
    string answer = get_string("Are you ok? "); // calling a function that return us a string/response of user, and copying
    // /assign it to our variable answer of type string
    printf("Hello, %s\n", answer); // calling a function, passing a parameter of type "string", that is not a native type
    // %s > placeholder to put our string, %i - int $li - long int...
    printf("Operations: %i\n", 1+1);

    float pennies = get_float("Pennies: ");
    printf("%f.8f\n", pennies * 100);

    // calculator
    const int PI = 3;
    while (true){ // loop > while(condition) {runned if true}
        long int a = get_long("First number: "); // only 32bits +/- -2bi to 2bi if not long > 64bits = 
        long int b = get_long("Second number: ");
        printf("%li + %li = %li\n", a, b, a+b);
        // Conditions / boolean expressions / true/false
        if (a==b){
            printf("%li = %li\n", a, b);
        } else if (a > b){
            printf("%li > %li\n", a, b);
        } else {
            printf("%li != %li\n", a, b);
        }
        // and : && // or : ||
        if ((a == PI || b == PI) && (a == 0 || b == 0)) {
            printf("One number is similar to pi and other is null!!\n");
        }
        for (int counter=0; counter < 20; counter++){ // for (start; condition; execute every iteration)
            printf("=");
        }

        next_line();
        printf("A half of %li is about %li\n", a, by_2(a));
        if (a+b == 0){
            // both 0
            break;
            printf("Thanks!!!");
        }
    }
    // Do something before verification
    // overflow: goes to negative because the first bit indicates positive or negative
}

void next_line(void){
    printf("\n");
}
