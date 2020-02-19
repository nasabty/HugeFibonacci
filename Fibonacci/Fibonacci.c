//Nicholas Asbaty   |   5591

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "Fibonacci.h"


HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    if (p == NULL || q == NULL)
        return NULL; //checks if hugeint parameters are filled with stuff

    int carry = 0, n, i; //variable declarations

    //sets n to largest length +1 (to accommodate for possible carry)
    if (p->length > q->length)
        n = p->length + 1;
    else if (p->length <= q->length)
        n = p->length + 1;

    int *sum = calloc(n, sizeof(int) * (n)); //create temporary int array
    int temp = 0, a = 1, b = 1, pL = p->length, qL = q->length; //declare more variables

    for (i = 0; i < n; i++)
    {
        //statements where a number returns 0 if it iterates through every digit
        a = (pL <= 0) ? 0 : p->digits[i];
        b = (qL <= 0) ? 0 : q->digits[i];

        //calculates the sum
        temp = a + b + carry;
        carry = temp / 10;
        sum[i] = temp%10;
        pL--;
        qL--;
    }

    //removes extra carry digit if not used
    if (sum[n-1] == 0)
        n -= 1;

    HugeInteger *r = malloc(sizeof(HugeInteger)); //allocate memory

    if (r == NULL) //check if memory allocation was successful
        return NULL;

    r->digits = malloc(sizeof(int) * n); //allocate memory
    for (i = 0; i < n; i++)
        r->digits[i] = sum[i]; //fill digits with sum

    r->length = n; //set length to n

    return r;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
    int i;
    if (p != NULL)
    {
    for (i = 0; i < p->length; i++)
        p->digits[i] = NULL; //sets every digit to null

    for (i = 0; i < p->length; i++)
        free(p->digits[i]); //frees every digit
    free(p); //frees p
    }


    return NULL;
}

HugeInteger *parseString(char *str)
{
    int i, temp; //variable declaration
    if (str == NULL) //Check if string is null
        return NULL;

    HugeInteger *huge = malloc(sizeof(HugeInteger)); //allocate memory

    if (huge == NULL) //check if memory allocation was successful
        return NULL;

    huge->length = strlen(str);
    huge->digits = malloc(sizeof(int) * (huge->length));

    if (huge->digits == NULL)
        return NULL; //check if memory allocation was successful

    //if (str == "")


    for(i = 0; i < huge->length; i++)
       {
        temp = str[i] - '0'; //converts number from char to int
        huge->digits[(huge->length - 1) - i] = temp; //fills digits
       }
    return huge;
}

HugeInteger *parseInt(unsigned int n)
{
    //variable declarations
    int i;
    unsigned int temp = n;

    HugeInteger *huge = malloc(sizeof(HugeInteger)); //allocate memory

    if (huge == NULL) //check if memory allocation was successful
        return NULL;

    //special case if n == 0
    if (n == 0)
    {
        huge->length = 1;
        huge->digits = malloc(sizeof(int) * (huge->length)); //allocate memory

        if (huge->digits == NULL)
            return NULL; //check if memory allocation was successful

        huge->digits[0] = 0;
        return huge;
    }

    huge->length = 0; //sets length to 0


    while (temp >= 1 )
    {
        temp /= 10;
        huge->length += 1;
    }

    huge->digits = malloc(sizeof(int) * (huge->length)); //allocate memory

    if (huge->digits == NULL)
        return NULL; //check if memory allocation was successful

    temp = n;
    for (i = 0; i < huge->length; i++)
    {
        huge->digits[i] = temp % 10; //sets digits[i] to one digit of temp
        temp /= 10; //moves to next digit
    }

    return huge;
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
    //variable declarations
    int len = 0;
    unsigned int *n = malloc(sizeof(unsigned int)); //allocate new unsigned int
    unsigned int temp;

    //checks if p is null
    if (p == NULL)
        return NULL;





    //check if memory allocation was successful
    if (n == NULL)
        return NULL;

    //special case for if hugeint is just 0
    if (p->digits[0] == 0 && p->length == 1)
    {
        *n = 0;
        return n;
    }

    *n = 0;
    unsigned int x = 10;
    int i = p->length - 1;
    x = (int)((pow(x, p->length) + 0.5)/10); //used to determine how many digits are in the number

    while (x >= 1)
    {

        *n += p->digits[i] * x; //assigns number to correlated digit
        x /= 10; //moves to next digit to assign
        i--;
    }

    //determines length of number
    temp = *n;
    while (temp >= 1 )
    {
        temp /= 10;
        len += 1;
    }

    //checks if the number converted wrong
    if (p->length != len)
        return NULL;

    return n;
}

HugeInteger *fib(int n)
{
    int i; //variable declarations
    HugeInteger **a = malloc((n + 1) * sizeof *a); //allocate memory

    if (a == NULL)
        return NULL; //check if memory allocation was successful

    a[0] = parseInt(0);
    a[1] = parseInt(1);

    //preforms fibonacci
    for (i = 2; i <= n; ++i)
    {
        a[i] = hugeAdd(a[i - 1] , a[i - 2]);
    }

    return a[n];
}

double difficultyRating(void)
{
    return 3.0; //returns difficulty
}

double hoursSpent(void)
{
    return 13.0; //returns hours spent
}
