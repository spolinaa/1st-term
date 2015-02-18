/* Task 7
Sokolova Polina */

#include <stdio.h>
#include <math.h>
main()
{
    int i;
    int n;
    int j;
    int f = 1;
    scanf("%d", &n);
    for (i = 2; i <= n; i++)
    {
        f = 1;
        for (j = 2; j <= round(sqrt(i)); j++)
            if (i%j == 0)
                f = 0;
    if (f == 1)
        printf("%d ", i);
    }
    printf("\n");
    
}
