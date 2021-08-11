#include <stdio.h>

int main()
{
    double p;
    double n = 1;
    double m = n + 1;
    int i;
    int times = 1000;
    double result;
    //n / (n + 1);
    for (i = 0; i < times; i++)
    {
        p = n;
        n = m;
        m = m + p;
        result = n / m;
        printf(" %lf\n", result);
    }
}