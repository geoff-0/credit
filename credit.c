#include <stdio.h>
#include <math.h>

long long nlength(long long n);

long long luhn(long long n);

char *cardType(long long n);

long long cut_number(long long n, int place);

long long get_digit(long long number, int place);


int main(void)
{
    long long cardNumber;
    printf("Card number: ");
    scanf("%lld",&cardNumber);
    long long checksum = luhn(cardNumber);
    if(checksum == 1)
    {
        printf("%s", cardType(cardNumber));
    }
    if(checksum != 1)
    {
        printf("INVALID\n");
    }
}




// Gets the amount of digits in number n
long long nlength(long long n)
{
    int count = 0;

    do
    {
        count += 1;
        n /= 10;
    } while (n != 0);

    return count;
}


// Verifies card number
long long luhn(long long n)
{
    long long valid;

    long long num = n / 10;

    long long addedProduct = 0;

    long long lol = num % 10;
    long long digit = lol * 2;

    if (nlength((num % 10) * 2) == 1)
    {
        addedProduct += digit;
    }
    if (nlength((num % 10) * 2) == 2)
    {
        addedProduct += (digit / 10) + (digit % 10);
    }

    //printf("Added: %lli\n", addedProduct);

    long long digits = nlength(n);

    long long narray[digits];
    long long o_narray[digits];
    long long counter = 1;


    // Get every other number and multiply them by 2, then add all of it together
    o_narray[0] = n % 10;
    //printf("Stored nonmultiple number: %lli\n", o_narray[0]);
    do
    {
        if (num > 0)
        {
            if (nlength((num / 10) % 10) == 1)
            {
                o_narray[counter] = (num / 10) % 10;
                //printf("Stored nonmultiple number: %lli\n\n", o_narray[counter]);
            }

            num /= 100;
            counter += 1;
            if (nlength((num % 10) * 2) == 1)
            {
                addedProduct += (num % 10) * 2;
                //printf("Added: %lli, addedProduct: %lli\n", (num % 10) * 2, addedProduct);
            }

            if (nlength((num % 10) * 2) == 2)
            {
                lol = num % 10;
                digit = lol * 2;
                addedProduct += digit / 10  + digit % 10;
                //("Digit: %lli on iteration: %lli, Added: %lli + %lli = %lli\n", lol, counter, digit / 10, digit % 10, addedProduct);
            }
        }
    } while (num > 0);


   // printf("OtherAddedProduct: %lli\n\n", addedProduct);

    for (long long o = 0; o < counter; o++)
    {
        if (nlength((num / 10) % 10) == 1)
        {
            addedProduct += o_narray[o];
       // printf("Added original number: %lli\n", o_narray[o]);
        }


    } //printf("\nFinal product: %lli, Mod10: %lli\n", addedProduct, addedProduct % 10);


     //Number is valid if numMod10 equals 0
    if (addedProduct % 10 == 0)
    {
        valid = 1;
    }
    if (addedProduct % 10 != 0)
    {
        valid = 0;
    }

    return valid;
}


// Checks for type of card
char *cardType(long long n)
{
    long long i;
    int type;
    char *finalType;

    // Card number length
    long long digits = nlength(n);

    // American Express prefixes
    long long AE[2] = {34, 37};

    // MasterCard prefixes
    long long MC[5] = {51, 52, 53, 54, 55};

    // Visa's only given prefix being 4
    long long VISA = 4;


    // American Express check
    for (i = 0; i < 2; i++)
    {
        if (cut_number(n, 2) == AE[i] && digits == 15)
        {
            type = 1;
        }
    }


    // MasterCard check
    for (i = 0; i < 5; i++)
    {
        if (cut_number(n, 2) == MC[i] && digits == 16)
        {
            type = 2;
        }
    }

    // Visa check
    if (get_digit(n, 1) == 4 && digits == 13)
    {
        type = 3;
    }
    if (get_digit(n, 1) == 4 && digits == 16)
    {
        type = 3;
    }


    if (type == 1)
    {
        finalType = "AMEX\n";
    }

    if (type == 2)
    {
        finalType = "MASTERCARD\n";
    }

    if (type == 3)
    {
        finalType = "VISA\n";
    }

    if (type != 1 & type != 2 & type != 3)
    {
        finalType = "INVALID\n";
    }


    return finalType;
}

// Gets every digit before the Nth place
long long cut_number(long long n, int place)
{
    do
    {
        n /= 10;
    } while (n >= pow(10, place));

    return n;
}

// Gets a digit from a number
long long get_digit(long long number, int place)
{
    do
    {
        number /= 10;
    } while (number >= pow(10, place));

    return number % 10;
}