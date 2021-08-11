#include<stdio.h>
#include<string.h>
#define SZ 31

int main(void)
{
    char str1[SZ] = "Charlotte's ";
    char str2[SZ] = "Spider's web";
    char str3[SZ] = { 0 };
    strcat(str1, &str2[9]);
    if (!(strcmp(str1, "Charlotte's web")))
    {
        strcpy(str3, " is the ");
    }
    else
    {
        strcpy(str3, " is not the ");
    }
    printf("%s %s %s!\n", str1, str3, str2);
        return 0;
}