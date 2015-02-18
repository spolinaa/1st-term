/* Task 5
Sokolova Polina */

#include <stdio.h>
int main()
{
    int a[10000];
    int i;
    int f = 1;
    int n;
    printf("Введите размер\n");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (i = 1; i <= (n / 2); i++)
        if (a[i] != a[n + 1 - i])
        {
            f = 0;
            break;
        }
    if (f == 1)
        printf("Симметричный\n");
    else
        printf("Несимметричный\n");


}
