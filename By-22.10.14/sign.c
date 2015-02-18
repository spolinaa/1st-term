/* Sign of a number
by Sokolova Polina */

#include <stdio.h>
int main() {
	int num = 0;
	int test = 0;
	printf ("Введите число\n");
	scanf ("%d", &num);
	test = num >> 31;
	num = test | (!!num);
	printf ("%d\n", num);
	
}
