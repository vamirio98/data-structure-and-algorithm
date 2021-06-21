/*=======================================================
 * find_maj_elem.c - find the majority element in a array
 *
 * Created by Haoyuan Li on 2021/06/21
 * Last Modified: 2021/06/21 21:03:49
 *=======================================================
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


/*-------------------------------------------------------
 * count - count how many times @elem appear in @a
 * @a      : array
 * @len    : length of @a
 * @elem   : the element to be count
 *-------------------------------------------------------
 */
size_t count(int *a, size_t len, int elem)
{
        size_t i, cnt;
        for (i = 0, cnt = 0; i < len; ++i) {
                if (a[i] == elem) {
                        ++cnt;
                }
        }
        return cnt;
}


int find_maj_elem(int *a, size_t len, int *elem)
{
        size_t tail = len;      /* number of elements remains in the copy */
        size_t i, j, cnt;
        int *a_cpy;

        /* when @len is odd, if the first @len - 1 elements have a majority
         * element, then the last element can't change this. Otherwise, the
         * last element could be a majority
         */
        if (tail & 1) {
                --tail;
        }

        a_cpy = (int *)malloc(sizeof(int) * tail);
        if (a_cpy == NULL) {
                fprintf(stderr, "Error: no enough memory.\n");
                return 0;
        }
        for (i = 0; i < tail; ++i) {
                a_cpy[i] = a[i];
        }

        while (tail > 1) {
                for (i = 0, j = 0; i < tail; i += 2) {
                        if (a_cpy[i] == a_cpy[i + 1]) {
                                a_cpy[j++] = a_cpy[i];
                        }
                }
                tail = j;
        }

        *elem = a_cpy[0];
        free(a_cpy);
        if (tail == 1) {
                cnt = count(a, len, *elem);
        } else if (len & 1) {
                *elem = a[len - 1];
                cnt = count(a, len, *elem);
        } else {
                return 0;
        }
        if (cnt > (len >> 1)) {
                return 1;
        }
        return 0;
}

int main(void)
{
        int a[9] = { 3, 3, 4, 2, 4, 4, 2, 4, 4 };
        int b[8] = { 3, 3, 4, 2, 4, 4, 2, 4 };
        int c[8] = { 3, 3, 4, 3, 4, 2, 3, 3 };

        int elem;
        assert(1 == find_maj_elem(a, 9, &elem));
        assert(4 == elem);
        assert(0 == find_maj_elem(b, 8, &elem));
        assert(1 == find_maj_elem(c, 8, &elem));
        assert(3 == elem);

        return 0;
}
