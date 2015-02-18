/* FitsBits (1 - Yes, 0 - No)
by Sokolova Polina */

#include <stdio.h>
int main() {
	int num = 0;
	int sd;
	int mach = 0;
	printf ("Введите число\n");
	scanf("%d", &num);
	printf ("Введите размер машинного слова в битах\n");
	scanf("%d", &mach);
	mach--;
	sd = num >> 31;
	num = !!sd * (~ (num - 1) - 1) + (!sd) * num;
	printf ("%d\n", !(num >> mach));
		
}
