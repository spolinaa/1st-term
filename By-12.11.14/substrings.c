/* Search substrings
by Sokolova Polina */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
const int M = 100;
const int N = 1000;
void reg(int l, char c[N]) {
    int i;
    for (i = 0; i <= l; i++) {
        c[i] = tolower(c[i]);
    }	
}
int com(char s[N], char s1[M], int l, int l1) {
    int f = 1;
    int k = 0;
    int i;
    int j;
    if (l) {
        if (l1) {
            for (i = 0; i < (l - l1 + 2); i++)
            {
                f = 1;
                for (j = 0; j < l1; j++)
                {
                if (s[i + j - 1] != s1[j])
                    f = 0;
                }
                if (f == 1)
                    k++;
            }
        }
        else k = 0;
    }
    else {
        if (l1) {
            k = 0;
        }
        else {
            k = -1;
        }
    }
    return k;
}
int main() {
    char s[N];
    char s1[M];
    int k;
    int len;
    int len1;
    printf ("Введите строку\n");
    gets(s);
    len = strlen(s);
    printf ("Введите подстроку\n");
    gets(s1);
    len1 = strlen(s1);
    reg(len, s);
    reg(len, s1);
    k = com(s, s1, len, len1);
    if (k == -1) {
        printf("Обе строки пусты!\n");
    }
    else {
        printf("%d\n", k);
    }
}
