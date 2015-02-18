/* Fast exponentiation with a negative power 
by Sokolova Polina */

#include <stdio.h>
int main() {
  int a;
  int n;
	float b;
	int m;
  int z = 1;
	float y = 1;
  printf ("Введите число\n");
  scanf ("%d", &a);
  printf ("Введите степень\n");
  scanf ("%d", &n);
	m = n;
	b = a;
  for (; n && !(n >> 31); a *= a, n >>= 1) {
    if (n & 1) {
      z *= a;
		}
  }
	if (m >> 31) {
		m = ~(m - 1);
		for (b = (float) 1 / a ; m; b *= b, m >>= 1) {
			if (m & 1) {
				y *= b;
			}
		}		
		
	}
	if (m) {
    printf ("%d\n", z);
	} 
	else {
		printf ("%f\n", y);
	}	
}
