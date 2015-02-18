/* Task 10
Sokolova Polina */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
main()
{
    char s[1000];
    char s1[100];
    int k=0;
    int f=1;
    int i;
    int j;
    gets(s);
    gets(s1);
    for ( i = 0; i <= strlen(s); i++)
        s[i] = tolower(s[i]);
    for (i = 0; i <= strlen(s1); i++)
        s1[i] = tolower(s1[i]);
    for (i = 0; i <= (strlen(s) - strlen(s1) + 1); i++)
    {
        f = 1;
        
        for (j = 0; j <= strlen(s1) - 1; j++)
        {
            if (s[i + j - 1] != s1[j])
                f = 0;
        }
        if (f == 1)
            k++;
    }
    printf("%d\n", k);
}
