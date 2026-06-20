#include <stdio.h>

int my_atoi(char* s)
{
    int is_negative = 0;
    if (s[0] == '-')
    {
        is_negative = 1;
        s++;
    }

    int sum = 0;
    for (int i = 0; s[i] != '\0'; ++i)
    {
        sum = 10 * sum + s[i] - '0';
    }
    return is_negative ? -sum : sum;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <number>\n", argv[0]);
        return -1;
    }
    printf("Number = %d\n", my_atoi(argv[1]));
    return 0;
}