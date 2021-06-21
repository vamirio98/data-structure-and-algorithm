/*=======================================================
 * is_prime.c - determine whether a number is a prime
 *
 * Created by Haoyuan Li on 2021/06/20
 * Last Modified: 2021/06/21 09:11:39
 *=======================================================
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>

int is_prime(int n)
{
        if (n <= 3) {
                return n > 1;
        }
        if (n % 6 != 1 && n % 6 != 5) {
                return 0;
        }
        int s = sqrt(n);
        for (int i = 5; i <= s; i += 6) {
                if ((n % i == 0) || (n % (i + 2) == 0)) {
                        return 0;
                }
        }
        return 1;
}

int main(void)
{
        assert(1 == is_prime(2));
        assert(0 == is_prime(35));
        assert(1 == is_prime(37));

        return 0;
}
