/* With bitfields
by Sokolova Polina */


#include <stdio.h>
int main(){
	float b = 1./2.;
	float mant = 0;
    float fval2;
	union {
		float fval;
		struct {
			unsigned int m:23;
			unsigned int e:8;
			unsigned s:1;
		} data;
	} val;
	printf ("Введите числа\n");
	scanf("%f%f", &val.fval, &fval2);
    val.fval = val.fval / fval2;
	printf ("Знак = %d\n", val.data.s);
	printf ("Порядок = %d\n", val.data.e);
	while (val.data.m) {
		mant = mant + b * (val.data.m >> 22);
		b /= 2;
		val.data.m <<= 1;
	}
	printf ("Мантисса = %f\n", mant);
    if ((val.data.e == 0) && (mant == 0)) {
        printf ("0\n");
    }
    else {
        if ((val.data.e == 255) && (mant == 0)) {
            if (val.data.s == 1) {
                printf ("- infinity\n");
            }
            else {
                printf ("+ infinity\n");
            }
        }
        else {
            if ((val.data.e == 255) && (mant != 0)) {
                printf ("NaN\n");
            }
            else {
                if 	(val.data.s == 1) {
                    printf ("- ");
                }
            printf ("2ˆ(%d - 127) * %f\n", val.data.e, mant + 1);
            }
        }
    }
}