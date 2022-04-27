#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct _linkedlist Linkedlist;
typedef struct _node Node;

void init_list(Linkedlist *list);
Node *insert_at_tail(Linkedlist *list, const char val);
Node *insert_at_head(Linkedlist *list, const char val);
char remove_last(Linkedlist *list);
char remove_first(Linkedlist *list);
void print_list(const Linkedlist *list);
char get(Linkedlist *list, int i);
int8_t sizeof_list(Linkedlist *list);

#endif // LINKEDLIST_H