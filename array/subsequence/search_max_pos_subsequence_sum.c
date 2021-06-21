/*=======================================================
 * search_max_pos_subsequence_sum.c - search the min
 * positive subsequence sum, use the greedy algorithm
 *
 * Created by Haoyuan Li on 2021/06/19
 * Last Modified: 2021/06/20 19:04:58
 *=======================================================
 */
#include <stdio.h>
#include <assert.h>

struct addup {
        int sum;        /* sum from a[0] to a[i] */
        size_t idx;     /* i */
};

void swap(struct addup *a, struct addup *b)
{
        struct addup tmp = *a;
        *a = *b;
        *b = tmp;
}

void quick_sort(struct addup *left, struct addup *right)
{
        if (left >= right)
                return;

        int base;
        struct addup *b, *e;

        b = left;
        e = right;
        base = b->sum;

        while (b < e) {
                while (e->sum >= base) {
                        --e;
                }
                swap(b, e);
                while (b->sum <= base) {
                        ++b;
                }
                swap(b, e);
        }

        quick_sort(left, b);
        quick_sort(b, right);
}

int search_min_pos_subsequence_sum(int *a, size_t len, size_t *begin,
        size_t *end)
{
        struct addup b[len];
        size_t i;
        int this_sum = 0;
        int min_sum = 0;

        for (i = 0; i < len; ++i) {
                this_sum += a[i];
                b[i].sum = this_sum;
                b[i].idx = i;
        }

        quick_sort(b, &b[len-1]);
        i = 0;
        while (b[i].sum < 0) {
                ++i;
        }
        min_sum = b[i].sum;
        *begin = 0;
        *end = b[i].idx;
        for (i = 1; i < len; ++i) {
                this_sum = b[i].sum - b[i-1].sum;
                if (this_sum < min_sum && b[i-1].idx < b[i].idx) {
                        min_sum = this_sum;
                        *begin = b[i-1].idx;
                        *end = b[i].idx;
                }
        }
        return min_sum;
}

int main(void)
{
        int a[10] = { 10, -1, -3, 4, 5, -9, -3, 1 };
        int b[4] = { 2, 2, 1, -1 };
        size_t begin, end;

        assert(1 == search_min_pos_subsequence_sum(a, 10, &begin, &end));
        assert(2 == begin);
        assert(3 == end);
        assert(1 == search_min_pos_subsequence_sum(b, 4, &begin, &end));
        assert(2 == begin);
        assert(2 == end);

        return 0;
}
