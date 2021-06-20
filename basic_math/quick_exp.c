/*=======================================================
 * quick_exp.c - quick exponentiation
 *
 * Created by Haoyuan Li on 2021/06/20
 * Last Modified: 2021/06/20 21:48:23
 *=======================================================
 */
#include <stdio.h>
#include <assert.h>

float quick_exp(float base, unsigned exp)
{
        float pow = 1;
        /* expressing exponent in binary can help understand */
        while (exp) {
                if (exp & 1) {
                        pow *= base;
                }
                base *= base;
                exp >>= 1;
        }
        return pow;
}

int main(void)
{
        assert(64 == quick_exp(2, 6));
        assert(27 == quick_exp(3, 3));

        return 0;
}
