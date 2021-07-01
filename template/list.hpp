#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T>
class singly_linked_list {
        private:
                typedef singly_linked_list<T> sll;
        public:
                T elem;
                sll *next;

        public:
                singly_linked_list();
                singly_linked_list(const T &elem);
                singly_linked_list(const T &elem, const sll *const next);
                bool is_tail();
                sll *find_prev_node(const sll *const head);
                sll *find_prev_node(const sll *const head, const T &elem);
                sll *find_node(const sll *const head, const T &elem);
                sll *insert(const sll *const head, sll *const node);
                sll *insert(const sll *const head, const T &elem);
                sll *append(sll *const node);
                sll *append(const T &elem);
                sll *remove();
                sll *remove(const sll *const head);
                sll *remove(const sll *const head, const T &elem);
                sll *clear();
                sll *clear(sll *const node);
                void print();
};


template <typename T>
singly_linked_list<T>::singly_linked_list()
{
        this->elem = T();
        this->next = NULL;
}

template <typename T>
singly_linked_list<T>::singly_linked_list(const T &elem)
{
        this->elem = elem;
        this->next = NULL;
}


template <typename T>
singly_linked_list<T>::singly_linked_list(const T &elem, const sll *const next)
{
        this->elem = elem;
        this->next = const_cast<sll *const>(next);
}


/*-------------------------------------------------------
 * is_tail - check whether a node is the last node
 *-------------------------------------------------------
 */
template <typename T>
bool singly_linked_list<T>::is_tail()
{
        return !this->next;
}


/*-------------------------------------------------------
 * find_prev_node - find the node before this node,
 * return the pointer point to the node found, NULL if
 * not found
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::find_prev_node(
                const sll *const head)
{
        if (head->next == this)
                return const_cast<sll *>(head);
        sll *p = head->next;
        while (p && p->next != this)
                p = p->next;
        return p;
}


/*-------------------------------------------------------
 * find_prev_node - find the node before the first node
 * with element @T, return the pointer point to the node
 * found, NULL if not found
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::find_prev_node(
                const sll *const head, const T &elem)
{
        if (head->next->elem == elem)
                return const_cast<sll *>(head);
        sll *p = head->next;
        while (!p->is_tail() && p->next->elem != elem)
                p = p->next;
        if (p->is_tail())
                p = NULL;
        return p;
}


/*-------------------------------------------------------
 * find_node - find the first node with element @elem,
 * return the pointer point to the node found, NULL if
 * not found
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::find_node(
                const sll *const head, const T &elem)
{
        sll *p = head->next;
        while (p && p->elem != elem)
                p = p->next;
        return p;
}


/*-------------------------------------------------------
 * insert - insert the node @node before this node,
 * return the pointer point to @node, NULL if failed
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::insert(
                const sll *const head, sll *const node)
{
        sll *prev = this->find_prev_node(head);
        if (prev == NULL)
                return NULL;
        prev->next = node;
        node->next = this;
        return node;
}


/*-------------------------------------------------------
 * insert - insert a new node with element &elem before
 * this node, return the pointer point to the new node,
 * NULL if failed
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::insert(
                const sll * const head, const T &elem)
{
        sll *prev = this->find_prev_node(head);
        sll *node = new (std::nothrow) singly_linked_list<T>(elem, this);
        if (!prev || !node)
                return NULL;
        prev->next = node;
        return node;
}


/*-------------------------------------------------------
 * append - append the node @node to this node, return
 * the pointer point to @node
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::append(sll *const node)
{
        node->next = this->next;
        this->next = node;
        return node;
}


/*-------------------------------------------------------
 * append - append a new node with element @elem to this
 * node, return the pointer point to the new node, NULL
 * if failed
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::append(const T &elem)
{
        sll *p = new (std::nothrow) singly_linked_list<T>(elem, this->next);
        if (!p)
                return NULL;
        this->next = p;
        return p;
}


/*-------------------------------------------------------
 * remove - remove the first node after this node, return
 * the pointer point the the next node
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::remove()
{
        if (this->is_tail())
                return NULL;
        sll *tmp = this->next;
        this->next = tmp->next;
        delete tmp;
        return this->next;
}


/*-------------------------------------------------------
 * remove - remove this node, return the pointer point to
 * the next node, NULL if failed
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::remove(const sll *const head)
{
        sll *prev = this->find_prev_node(head);
        if (!prev)
                return NULL;    /* it's illegal to remove the head node */
        prev->next = this->next;
        delete this;
        return prev->next;
}


/*-------------------------------------------------------
 * remove - remove the first node with element @elem,
 * return the pointer point to the next node, NULL if
 * failed
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::remove(
                const sll *const head, const T &elem)
{
        sll *prev = this->find_prev_node(head, elem);
        if (!prev)
                return NULL;
        sll *tmp = prev->next;
        prev->next = tmp->next;
        delete tmp;
        return prev->next;
}


/*-------------------------------------------------------
 * clear - clear all nodes behind this node, return the
 * pointer point to this node
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::clear()
{
        return this->clear(this);
}


/*-------------------------------------------------------
 * clear - clear all nodes behind the node @node, return
 * the pointer point to @node
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::clear(sll *const node)
{
        while (!node->is_tail())
                node->remove();
        return node;
}


/*-------------------------------------------------------
 * print - print the list
 *-------------------------------------------------------
 */
template <typename T>
void singly_linked_list<T>::print()
{
        sll *p = this->next;
        while (p) {
                std::cout << p->elem << " ";
                p = p->next;
        }
        std::cout << std::endl;
}

#endif /* LIST_HPP */
