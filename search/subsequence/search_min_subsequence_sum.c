/*=======================================================
 * search_min_subsequence_sum.c -
 *
 * Created by Haoyuan Li on 2021/06/18
 * Last Modified: 2021/06/18 19:51:12
 *=======================================================
 */
#include <stdio.h>
#include <assert.h>

int search_min_subsequence_sum(int *a, size_t len, size_t *begin, size_t *end)
{
        int this_sum = 0;
        int min_sum = a[0];
        size_t i;

        *begin = *end = 0;
        for (i = 0; i < len; ++i) {
                this_sum += a[i];
                if (this_sum < min_sum) {
                        min_sum = this_sum;
                        *end = i;
                } else if (this_sum > 0) {
                        this_sum = 0;
                        *begin = i + 1;
                }
        }
        return min_sum;
}

int main(void)
{
        int a[10] = { 10, -1, -3, 4, 5, -9, -3, 1, -5, 10 };
        size_t begin, end;
        assert(-16 == search_min_subsequence_sum(a, 10, &begin, &end));
        assert(5 == begin);
        assert(8 == end);

        return 0;
}
