#ifndef _ITOB_H_
#define _ITOB_H_

 /*reverse the string*/
void reverse(char s[])
{
    int i,j;
    char c;
    for (i = 0, j = strlen(s)-1; i < j; i++,j--)
    {
        c = s[i];
        s[i] =  s[j];
        s[j] = c;
    }
};

void itob(int n, char *s, int b)
{
    int i,sign;
    if ((sign = n) < 0)
        n = -n;
    for (i = 0; n > 0; i++)
    {
        if (b > 10 && n >= 0)
            s[i] = n%b -10 + 'a';
        else
            s[i] = n%b + '0';
        n /= b;
    }
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
};
 #endif
