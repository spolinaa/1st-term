/* With pointers
 by Sokolova Polina */

#include <stdio.h>
int main(){
    float b = 1./2.;
    float mant = 0;
    float val;
    float val2;
    int ival;
    unsigned int s;
    unsigned int e;
    unsigned int m;
    printf("Введите числа\n");
    scanf("%f%f", &val, &val2);
    val = (float) val / val2;
    ival = * ((int * )(void *)(&val));
    s = ival;
    e = ival;
    m = ival;
    s = s & (~0x7FFFFFFF);
    s = !!s;
    printf("Знак = %d\n", s);
    e = e & (0x7F800000);
    e >>= 23;
    printf("Порядок = %d\n", e);
    m = m & (0x7FFFFF);
    m <<= 9;
    while (m) {
        mant = mant + b * (m >> 31);
        b /= 2;
        m <<= 1;
    }
    printf("Мантисса = %f\n", mant);
    if ((e == 0) && (mant == 0)) {
        printf("0\n");
    }
    else {
        if ((e == 255) && (mant == 0)) {
            if (s == 1) {
                printf("- infinity\n");
            }
            else printf("+ infinity\n");
        }
        else {
            if ((e == 255) && (mant != 0)) {
                printf("NaN\n");
            }	
            else {
                if (s == 1) {
                    printf("-");
                }	
                printf("2^(%d - 127) * %f\n", e, mant + 1);
            }
        }	
    }		
}