/* Binary representation
by Sokolova Polina */

#include <stdio.h>
int main() {
	int num = 0;
	int size = sizeof(int) * 8 - 1;
	printf ("Введите число\n");
	scanf ("%d", &num);
    for (; size >= 0; size--, num <<= 1) {
		printf ("%d", ((num >> 31) & 1));
    }
	printf("\n");
    
}	
