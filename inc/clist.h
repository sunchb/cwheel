#ifndef _CLIST_
#define _CLIST_

#ifdef __cplusplus
extern "C" {
#endif

#include "cdef.h"

typedef struct cListNode {
    void*               value;
    struct cListNode*   next;
}cListNode;

typedef struct cList{
    cListNode*          head;
    int                 size;
}cList;

typedef int (*clist_cond_func_t)(cListNode* node, void* args);

int clist_init(cList* list);
int clist_deinit(cList* list);
int clist_add_head(cList* list, void* value);
int clist_remove_head(cList* list);
int clist_reverse(cList* list);
int clist_remove_forward(cList* list, int index);
int clist_remove_reverse(cList* list, int index);
int clist_remove_cond(cList* list, clist_cond_func_t condFunc, void* args);
cListNode* clist_find_cond(cList* list, clist_cond_func_t condFunc, void* args);

#if 0
int size();
boolean isEmpty();
boolean contains(Object o);
Iterator<E> iterator();
Object[] toArray();
<T> T[] toArray(T[] a);
boolean add(E e);
boolean remove(Object o);
boolean containsAll(Collection<?> c);
boolean addAll(Collection<? extends E> c);
boolean addAll(int index, Collection<? extends E> c);
boolean removeAll(Collection<?> c);
boolean retainAll(Collection<?> c);
void replaceAll(UnaryOperator<E> operator);
void sort(Comparator<? super E> c);
void clear();
E get(int index);
E set(int index, E element);
void add(int index, E element);
E remove(int index);
int indexOf(Object o);
int lastIndexOf(Object o);
ListIterator<E> listIterator();
ListIterator<E> listIterator(int index);
List<E> subList(int fromIndex, int toIndex);
#endif

#ifdef __cplusplus
}
#endif

#endif