/* With union
by Sokolova Polina */

#include <stdio.h>
int main(){
    float b = 1./2.;
    float mant = 0;
    float fval1;
    float fval2;
    struct {
		unsigned s;
		unsigned int e;
		unsigned int m;
		union {
			int ival;
			float fval;
		} val;
    } data;
    printf ("Введите числа\n");
    scanf("%f%f", &fval1, &fval2);
    data.val.fval = fval1 / fval2;
    data.s = data.val.ival;
    data.e = data.val.ival;
    data.m = data.val.ival;
    data.s = data.s & (~0x7FFFFFFF);
    data.s = !!data.s;
    printf ("Знак = %d\n", data.s);
    data.e = data.e & (0x7F800000);
    data.e >>= 23;
    printf ("Порядок = %d\n", data.e);
    data.m = data.m & (0x7FFFFF);
    data.m <<= 9;
    while (data.m) {
	mant = mant + b * (data.m >> 31);
	b /= 2;
	data.m <<= 1;
    }
    printf ("Мантисса = %f\n", mant);
    if ((data.e == 0) && (mant == 0)) {
        printf ("0\n");
    }
    else {
        if ((data.e == 255) && (mant == 0)) {
            if (data.s == 1) {
                printf ("- infinity\n");
            }
            else {
                printf ("+ infinity\n");
            }
        }
        else {
            if ((data.e == 255) && (mant != 0)) {
                printf ("NaN\n");
            }
            else {
                if (data.s == 1) {
                    printf ("- ");
                }
                printf ("2ˆ(%d - 127) * %f\n", data.e, mant + 1);
            }
        }
    }
}
