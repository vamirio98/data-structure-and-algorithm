/*=======================================================
 * binary_search.c -
 *
 * Created by Haoyuan Li on 2021/06/22
 * Last Modified: 2021/06/22 19:58:06
 *=======================================================
 */

#include <stdio.h>
#include <assert.h>


/*-------------------------------------------------------
 * lower_bound - search the first element not less than
 * @value in the range [@left, @right) of a non-descending
 * array @a
 *-------------------------------------------------------
 */
size_t lower_bound(int *a, size_t left, size_t right, int value)
{
        size_t mid;

        while (left < right) {
                mid = left + (right - left) / 2;
                if (a[mid] < value) {
                        left = mid + 1;
                } else {
                        right = mid;
                }
        }

        return left;
}


/*-------------------------------------------------------
 * binary_search - binary search @value in the range
 * [@left, @rigth) of a non-descending array @a, store the
 * index in @idx
 *-------------------------------------------------------
 */
int binary_search(int *a, size_t left, size_t right, int value, size_t *idx)
{
        *idx = lower_bound(a, left, right, value);
        if (*idx < right && a[*idx] == value) {
                return 1;
        } else {
                return 0;
        }
}


int main(void)
{
        int a[10] = { 1, 1, 2, 3, 3, 4, 5, 6, 6, 7 };
        size_t idx;

        assert(0 == binary_search(a, 0, 10, 10, &idx));
        assert(1 == binary_search(a, 0, 10, 3, &idx));
        assert(3 == idx);

        return 0;
}
