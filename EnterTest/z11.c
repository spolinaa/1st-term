/* Task 11
Sokolova Polina */

#include <stdio.h>
main()
{
    int a = 3;
    int i;
    int n;
    scanf("%d", &n);
    if (n < 3)
        for (i = 1; i <= n; i++)
            printf("%d ", i);
    else
        for (i = 3; i <= n; i++)
            a = a + i;
    printf("%d\n", a);
        
    
}
