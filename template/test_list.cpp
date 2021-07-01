/*=======================================================
 * test_list.cpp - test the class list
 *
 * Created by Haoyuan Li on 2021/06/30
 * Last Modified: 2021/07/01 15:42:27
 *=======================================================
 */

#include <iostream>
#include <assert.h>
#include "list.hpp"

typedef singly_linked_list<int> sll;
typedef doubly_linked_list<int> dll;


void test_sll()
{
        std::cout << "Start testing class singly_linked_list<int>:"
                << std::endl;
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
        p = head->find(2);
        assert(2 == p->elem);
        p = (head->find(0))->remove(head);
        std::cout << "Execpted output: 1 2\nActual output:   ";
        head->print();
        p = (p->find_prev_node(head))->append(3);
        std::cout << "Execpted output: 1 3 2\nActual output:   ";
        head->print();
        p = p->remove(head, 3);
        std::cout << "Execpted output: 1 2\nActual output:   ";
        head->print();
        head->clear();
        assert(1 == head->is_tail());
        delete head;
        std::cout << "End testing." << std::endl;
}


void test_dll()
{
        std::cout << "Start testing class doubly_linked_list<int>:"
                << std::endl;
        dll *head = new dll();
        dll *p;
        assert(1 == head->is_head());
        assert(1 == head->is_tail());
        p = head->append(2);
        p = p->append(new dll(3, p, p->next));
        p = (head->find(2))->insert(1);
        p = p->insert(new dll(0));
        std::cout << "Execpted output: 0 1 2 3\nActual output:   ";
        head->print();

        p = (head->find(3))->rfind(1);
        assert(1 == p->elem);
        p = p->remove();
        std::cout << "Execpted output: 0 2 3\nActual output:   ";
        head->print();
        p = head->clear();
        assert(1 == head->is_tail());
        delete head;
        std::cout << "End testing." << std::endl;
}


int main()
{
        test_sll();
        std::cout << std::endl;
        test_dll();

        return 0;
}
