/* Task 6
Sokolova Polina */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
main()
{
    char c[1000];
    int i;
    int f = 1;
    long j;
    gets(c);
    j = strlen(c) - 1;
    for (i = 0; i <= j; i++)
        c[i] = tolower(c[i]);
        for (i = 0; i <= strlen(c) / 2 - 1; i++)
    {
        if ((c[i] != ' ') && (j > i))
        {
            if (c[i] != c[j])
            {
                if ((c[i] != ' ') && (c[j] == ' '))
                {
                    i--;
                    j--;
                }
                else
                if ((c[i] != ' ') && (c[j] != ' '))
                {
                    f = 0;
                }
            }
            if (c[i] == c[j])
                j--;
        }
        
    }
    if (f == 1)
    {
        printf("YES!!!\n");
    }
        else
            printf ("NO!!!\n");
    
}
