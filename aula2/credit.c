#include <stdio.h>
#include <cs50.h>

int sum_digits(int n) 
{
    int sum = 0;
    while (n > 0)
    {
        sum += (n - (n / 10) * 10);
        n = n / 10;
    }
    return sum;
}

int main(void)
{
    long int card_number = get_long("Number: ");
    long int aux_number = card_number;
    int length = 0;
    int first_digit, second_digit;
    while (aux_number > 0)
    {
        length++;
        first_digit = aux_number;
        if (aux_number > 10)
        {
            second_digit = aux_number;
        }
        aux_number = aux_number / 10;
    }
    int counter = 1;
    int sum = 0;
    while (card_number > 0)
    {
        if (counter % 2 == 0)
        {
            sum += sum_digits((card_number - (card_number / 10) * 10) * 2);
            card_number = card_number / 10;
        }
        else
        {
            sum += sum_digits(card_number - (card_number / 10) * 10);
            card_number = card_number / 10;
        }
        counter++;
    }
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (first_digit == 4 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else if (first_digit == 5 && (second_digit >= 51 && second_digit <= 55) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (first_digit == 3 && (second_digit == 34 || second_digit == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
