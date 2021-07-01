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
                sll *find(const T &elem);
                sll *insert(const sll *const head, sll *const node);
                sll *insert(const sll *const head, const T &elem);
                sll *append(sll *const node);
                sll *append(const T &elem);
                sll *remove();
                sll *remove(const sll *const head);
                sll *remove(const sll *const head, const T &elem);
                sll *clear();
                void print();
};


template <typename T>
class doubly_linked_list {
        private:
                typedef doubly_linked_list<T> dll;
        public:
                T elem;
                dll *prev;
                dll *next;

        public:
                doubly_linked_list();
                doubly_linked_list(const T &elem);
                doubly_linked_list(const T &elem, const dll *const prev,
                                const dll *const next);
                bool is_head();
                bool is_tail();
                dll *find(const T &elem);
                dll *rfind(const T &elem);
                dll *insert(dll *const node);
                dll *insert(const T &elem);
                dll *append(dll *const node);
                dll *append(const T &elem);
                dll *remove();
                dll *clear();
                void print();
};


/*-------------------------------------------------------
 * singly_linked_list
 *-------------------------------------------------------
 */
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
 * find - find the first node with element @elem
 * after this node, return the pointer point to the node
 * found, NULL if not found
 *-------------------------------------------------------
 */
template <typename T>
singly_linked_list<T> *singly_linked_list<T>::find(const T &elem)
{
        sll *p = this->next;
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
        sll *p = NULL;
        sll *prev = this->find_prev_node(head);
        if (prev)
                p = prev->append(node);
        return p;
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
        sll *p = NULL;
        sll *prev = this->find_prev_node(head);
        if (prev)
                p = prev->append(elem);
        return p;
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
        if (p)
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
        while (!this->is_tail())
                this->remove();
        return this;
}


/*-------------------------------------------------------
 * print - print all nodes after this node
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


/*-------------------------------------------------------
 * doubly_linked_list
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T>::doubly_linked_list()
{
        this->elem = T();
        this->prev = NULL;
        this->next = NULL;
}


template <typename T>
doubly_linked_list<T>::doubly_linked_list(const T &elem)
{
        this->elem = elem;
        this->prev = NULL;
        this->next = NULL;
}


template <typename T>
doubly_linked_list<T>::doubly_linked_list(const T &elem, const dll *const prev,
                const dll *const next)
{
        this->elem = elem;
        this->prev = const_cast<dll *>(prev);
        this->next = const_cast<dll *>(next);
}


/*-------------------------------------------------------
 * is_head - check whether this node is the head node
 *-------------------------------------------------------
 */
template <typename T>
bool doubly_linked_list<T>::is_head()
{
        return !this->prev;
}


/*-------------------------------------------------------
 * is_tail - check whether this node is the last node
 *-------------------------------------------------------
 */
template <typename T>
bool doubly_linked_list<T>::is_tail()
{
        return !this->next;
}


/*-------------------------------------------------------
 * find - find the first node with element @elem after
 * this node, return the pointer point to the node found,
 * NULL if not found
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::find(const T &elem)
{
        dll *p = this->next;
        while (p && p->elem != elem)
                p = p->next;
        return p;
}


/*-------------------------------------------------------
 * rfind - inverse find the first node with the element
 * @elem, return the pointer point to the node found,
 * NULL if not found
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::rfind(const T &elem)
{
        if (this->is_head())
                return NULL;
        dll *p = this->prev;
        while (!p->is_head() && p->elem != elem)
                p = p->prev;
        if (p->is_head())
                p = NULL;
        return p;
}


/*-------------------------------------------------------
 * insert - insert the node @node before this node,
 * return the pointer point to @node, NULL if failed
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::insert(dll *const node)
{
        if (this->is_head())
                return NULL;
        this->prev->append(node);
        return node;
}


/*-------------------------------------------------------
 * insert - insert a new node with element @elem before
 * this node, return the pointer point to the new node,
 * NULL if failed
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::insert(const T &elem)
{
        if (this->is_head())
                return NULL;
        dll *p = this->prev->append(elem);
        return p;
}


/*-------------------------------------------------------
 * append - append the node @node after this node, return
 * the pointer point to @node
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::append(dll *const node)
{
        if (!this->is_tail())
                this->next->prev = node;
        node->prev = this;
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
doubly_linked_list<T> *doubly_linked_list<T>::append(const T &elem)
{
        dll *p = new (std::nothrow) dll(elem, this, this->next);
        if (p) {
                if (!this->is_tail())
                        this->next->prev = p;
                this->next = p;
        }
        return p;
}


/*-------------------------------------------------------
 * remove - remove this node, return the poniter point to
 * the next node
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::remove()
{
        if (this->is_head())    /* it's illegal to remove a head node */
                return NULL;
        dll *p = this->next;
        if (!this->is_tail())
                p->prev = this->prev;
        this->prev->next = this->next;
        delete this;
        return p;
}


/*-------------------------------------------------------
 * clear - clear all nodes behind this node, return the
 * pointer point to this node
 *-------------------------------------------------------
 */
template <typename T>
doubly_linked_list<T> *doubly_linked_list<T>::clear()
{
        while (!this->is_tail())
                this->next->remove();
        return this;
}


/*-------------------------------------------------------
 * print - print all nodes after this node
 *-------------------------------------------------------
 */
template <typename T>
void doubly_linked_list<T>::print()
{
        dll *p = this->next;
        while (p) {
                std::cout << p->elem << " ";
                p = p->next;
        }
        std::cout << "\n";
}


#endif /* LIST_HPP */
