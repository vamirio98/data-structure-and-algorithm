/*=======================================================
 * search_max_subsequence_sum.c -
 *
 * Created by Haoyuan Li on 2021/06/18
 * Last Modified: 2021/06/18 19:49:08
 *=======================================================
 */

#include <stdio.h>
#include <assert.h>

int search_max_subsequence_sum(int *a, size_t len, size_t *begin, size_t *end)
{
        int this_sum = 0;
        int max_sum = a[0];
        size_t i;

        *begin = *end = 0;
        for (i = 0; i < len; ++i) {
                this_sum += a[i];
                if (this_sum > max_sum) {
                        max_sum = this_sum;
                        *end = i;
                } else if (this_sum < 0) {
                        this_sum = 0;
                        *begin = i + 1;
                }
        }
        return max_sum;
}

int main(void)
{
        int a[10] = { 0, 3, 5, 1, -10, 2, -1, 10, 12, -3 };
        size_t begin, end;
        assert(23 == search_max_subsequence_sum(a, 10, &begin, &end));
        assert(5 == begin);
        assert(8 == end);

        return 0;
}
