/* Task 4
Sokolova Polina */

#include <stdio.h>
main()
{
    int i;
    int k = 0;
    int n;
    int a[10000];
    printf("Введите количество элементов\n");
    scanf("%d", &n);
    for(i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
            k = k + (!a[i]);
    }
    printf("Количество нулевых элементов - %d\n", k);
}
