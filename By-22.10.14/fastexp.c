/* Fast exponentiation
by Sokolova Polina */

#include <stdio.h>
int main() {
    int a;
    int n;
    int z = 1;
    scanf ("%d", &a);
    scanf ("%d", &n);
    for (; n; a *= a, n >>= 1) {
        if (n & 1) {
            z *= a;
	}
    }	
    printf ("%d\n", z);
}
