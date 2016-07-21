#ifndef _HTOI_H
#define _HTOI_H
#include<string.h>

int htoi(char s[])
{
    int i,n = 0;
    int c;
    if(strlen(s) == 0)
        return 0;
    for(i=0; i < strlen(s);i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            c = s[i] - '0';
        if (s[i] >= 'a' && s[i] <= 'z')
            c = s[i] - 'a';
        if (s[i] >= 'A' && s[i] <= 'Z')
            c = s[i] - 'A';
        n = 16*n + c;
    } 
    return n;
};
#endif
