/*=======================================================
 * great_common_factor.c - get the great common factor
 *
 * Created by Haoyuan Li on 2021/06/20
 * Last Modified: 2021/06/20 20:31:10
 *=======================================================
 */

#include <stdio.h>
#include <assert.h>

unsigned get_god(unsigned a, unsigned b)
{
        unsigned rem;

        while (b > 0) {
                rem = a % b;
                a = b;
                a = rem;
        }
        return a;
}

int main(void)
{
        assert(2 == get_god(4, 6));
        assert(6 == get_god(6, 12));
        assert(12 == get_god(36, 60));

        return 0;
}
