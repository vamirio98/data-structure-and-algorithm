/*=======================================================
 * test_list.cpp - test the class list
 *
 * Created by Haoyuan Li on 2021/06/30
 * Last Modified: 2021/07/01 09:46:09
 *=======================================================
 */

#include <iostream>
#include <assert.h>
#include "list.hpp"

typedef singly_linked_list<int> sll;
int main()
{
        sll *head = new sll();
        assert(1 == head->is_tail());
        sll *p = head->append(3);
        p = p->insert(head, 2);
        p = p->insert(head, new sll(1));
        p = p->append(new sll(0));
        std::cout << "Execpted output: 1 0 2 3\nActual output:   ";
        head->print();

        p = (p->find_prev_node(head, 3))->remove();
        std::cout << "Execpted output: 1 0 2\nActual output:   ";
        head->print();
        p = (p->find_node(head, 0))->remove(head);
        std::cout << "Execpted output: 1 2\nActual output:   ";
        head->print();
        p = (p->find_prev_node(head))->append(3);
        std::cout << "Execpted output: 1 3 2\nActual output:   ";
        head->print();
        p = p->remove(head, 3);
        std::cout << "Execpted output: 1 2\nActual output:   ";
        head->print();
        p = p->clear(p->find_node(head, 1));
        std::cout << "Execpted output: 1\nActual output:   ";
        head->print();
        head->clear();
        assert(1 == head->is_tail());

        return 0;
}
