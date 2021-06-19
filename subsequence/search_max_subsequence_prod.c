/*=======================================================
 * search_max_subsequence_prod.c - search the max
 * subsequence product
 *
 * Created by Haoyuan Li on 2021/06/18
 * Last Modified: 2021/06/18 19:54:55
 *=======================================================
 */

#include <stdio.h>
#include <assert.h>

float search_max_subsequence_prod(float *a, size_t len, size_t *begin,
        size_t *end){
        float this_prod = 0.0;
        float max_prod = a[0];
        size_t i;

        *begin = *end = 0;
        for (i = 0; i < len; ++i) {
                this_prod *= a[i];
                if (this_prod > max_prod) {
                        max_prod = this_prod;
                        *end = i;
                } else if (this_prod < 1.0) {
                        this_prod = 1.0;
                        *begin = i + 1;
                }
        }
        return max_prod;
}

int main(void)
{
        float a[10] = { 1, 3, 0.1, 2, 12, 0.5, 1, 3, 0.1, 3 };
        size_t begin, end;

        assert(36 == search_max_subsequence_prod(a, 10, &begin, &end));
        assert(3 == begin);
        assert(7 == end);

        return 0;
}
