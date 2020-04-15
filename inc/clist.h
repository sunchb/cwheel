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
typedef int (*clist_compare_func_t)(void* a, void* b);

int clist_init(cList* list);
int clist_deinit(cList* list);

int clist_size(cList* list);
int clist_is_empty(cList* list);

int clist_contains(cList* list, void* value, clist_compare_func_t func);
void* clist_get(cList* list, int index);
int clist_set(cList* list, int index, void* value);

int clist_add_head(cList* list, void* value);
int clist_add(cList* list, int index, void* value);

int clist_remove(cList* list, int index);
int clist_remove_head(cList* list);
int clist_remove_object(cList* list, void* object);
int clist_remove_cond(cList* list, clist_cond_func_t condFunc, void* args);

cListNode* clist_find_cond(cList* list, clist_cond_func_t condFunc, void* args);
int clist_index_of(cList* list, void* value, clist_compare_func_t func);
int clist_last_index_of(cList* list, void* value, clist_compare_func_t func);

int clist_sub_list(cList* srcList, cList* dstList, int fromIndex, int toIndex);
int clist_reverse(cList* list);
void** clist_to_array(cList* list, int* size);

#if 0
Iterator<E> iterator();
boolean add(E e);
boolean containsAll(Collection<?> c);
boolean addAll(Collection<? extends E> c);
boolean addAll(int index, Collection<? extends E> c);
boolean removeAll(Collection<?> c);
boolean retainAll(Collection<?> c);
void replaceAll(UnaryOperator<E> operator);
void sort(Comparator<? super E> c);
void clear();
ListIterator<E> listIterator();
ListIterator<E> listIterator(int index);
#endif

#ifdef __cplusplus
}
#endif

#endif