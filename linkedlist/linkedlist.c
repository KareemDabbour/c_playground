#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

#define EMPTYLIST '\0'
#define START_OF_LIST "[ "
#define END_OF_LIST "]\n"

typedef struct _node
{
    char value;
    struct _node *prev;
    struct _node *next;
} Node;

typedef struct _linkedlist
{
    Node *head_node;
    Node *tail_node;
    int8_t size;
} Linkedlist;

void print_list(const Linkedlist *list)
{
    Node *temp;
    temp = list->head_node;
    // while (temp->next != NULL)
    // {
    //     switch (temp->value)
    //     {
    //     case '\a':
    //         printf("[");
    //         break;
    //     case '\b':
    //         printf("]\n");
    //         break;
    //     default:
    //         printf("%c ", temp->value);
    //         break;
    //     }
    //     temp = temp->next;
    // }
    printf(START_OF_LIST);
    if (list->size != 0)
    {
        temp = temp->next;
        for (int i = 0; i < list->size - 1; i++)
        {
            printf("%c, ", temp->value);
            temp = temp->next;
        }
        printf("%c ", temp->value);
    }
    printf(END_OF_LIST);
}

Node *create_node(const char i)
{
    Node *temp;
    if ((temp = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;
    temp->value = i;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void init_list(Linkedlist *list)
{
    list->head_node = create_node('\a');
    list->tail_node = create_node('\b');
    list->size = 0;
    list->head_node->next = list->tail_node;
    list->tail_node->prev = list->head_node;
}

int8_t sizeof_list(Linkedlist *list)
{
    return list->size;
}

/* Removes the first element from a Linkedlist and
 * frees the memory for that element.
 * @param list: Linkedlist pointer
 * @return character that was removed -- '\0' if list is empty.
 **/
char remove_first(Linkedlist *list)
{
    if (list->head_node->next == list->tail_node)
        return EMPTYLIST;
    Node *head, *temp;
    char ret;
    head = list->head_node;
    temp = head->next;
    ret = temp->value;
    head->next = temp->next;
    temp->next->prev = head;
    list->size--;
    free(temp);
    return ret;
}

/* Removes the last element from a Linkedlist and
 * frees the memory for that element.
 * @param *list: Linkedlist pointer
 * @return The character that was removed -- '\0' if list is empty.
 **/
char remove_last(Linkedlist *list)
{
    // Check if the list is empty
    if (list->tail_node->prev == list->head_node)
        return EMPTYLIST;
    Node *tail, *temp;
    char ret;
    tail = list->tail_node;
    temp = tail->prev;
    ret = temp->value;
    tail->prev = temp->prev;
    temp->prev->next = tail;
    list->size--;
    free(temp);
    return ret;
}

/* Inserts a character at the head of a Linkedlist.
 *
 * @param *list: Linkedlist pointer
 * @param val: A character to be inserted
 * @return A pointer to the Node that was added.
 **/
Node *insert_at_head(Linkedlist *list, const char val)
{
    Node *newNode = create_node(val);
    Node *head = list->head_node;
    newNode->next = head->next;
    newNode->prev = head;
    head->next->prev = newNode;
    head->next = newNode;
    list->size++;
    return newNode;
}

/* Inserts a character at the tail of a Linkedlist.
 *
 * @param *list: Linkedlist pointer
 * @param val: A character to be inserted
 * @return A pointer to the Node that was added.
 **/
Node *insert_at_tail(Linkedlist *list, const char val)
{
    Node *newNode = create_node(val);
    Node *tail = list->tail_node;
    newNode->next = tail;
    newNode->prev = tail->prev;
    tail->prev->next = newNode;
    tail->prev = newNode;
    list->size++;
    return newNode;
}

char get(Linkedlist *list, int i)
{
    char ret = EMPTYLIST;
    if (i >= list->size)
        return ret;
    Node *temp = list->head_node;
    while (i-- >= 0 && temp != NULL)
        temp = temp->next;
    if (temp != NULL)
        ret = temp->value;
    return ret;
}

int main()
{
    Linkedlist linkedlist;
    int size;
    char temp;
    int index = 25;
    int num_to_be_removed = 5;
    init_list(&linkedlist);
    char *l = "abcdefghijklmnopqrstuvwxyz~0123456789";
    printf("Initializing LinkedList\n\n");
    for (size_t i = 0; i < strlen(l); i++)
    {
        // Testing the insertion functions
        insert_at_head(&linkedlist, *(l + i));
        insert_at_tail(&linkedlist, *(l + i));
    }

    printf("Looking up %dth index\n", index);
    char found_char = get(&linkedlist, index);
    printf("\n");
    print_list(&linkedlist);
    printf("Found value at index %d: %c\n", index, found_char);

    printf("List size::before removing the first %d elements:%d\n", num_to_be_removed, size = sizeof_list(&linkedlist));

    for (int i = 0; i < num_to_be_removed; i++)
    {
        temp = remove_first(&linkedlist);
        printf("Removed val at index %d: %c\n", i, temp);
    }
    printf("List size::after removing the first %d elements %d\n", num_to_be_removed, sizeof_list(&linkedlist));
    print_list(&linkedlist);

    printf("List size::before removing the last %d elements:%d\n", num_to_be_removed, size);
    for (int i = 0; i < num_to_be_removed; i++)
    {
        temp = remove_last(&linkedlist);
        printf("Removed val at index %d: %c\n", i, temp);
    }
    printf("List size::after removing the last %d elements %d\n", num_to_be_removed, size = sizeof_list(&linkedlist));
    print_list(&linkedlist);

    printf("\nClearing LinkedList\n");
    for (int i = 0; i < size; i++)
    {
        remove_first(&linkedlist);
    }
    print_list(&linkedlist);

    return 0;
}
