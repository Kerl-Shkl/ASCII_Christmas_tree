#include "../header/position.h"

void push_front_pl(pl_item** first, pl_item** last, ascii_symbol pos)
{
    pl_item* tmp;
    tmp = malloc(sizeof(pl_item));
    tmp->pos = pos;
    tmp->prev = NULL;
    tmp->next = *first;
    if (*first)
        (*first)->prev = tmp;
    else
        *last = tmp;
    *first = tmp;
}

void push_back_pl(pl_item** first, pl_item** last, ascii_symbol pos)
{
    pl_item* tmp;
    tmp = malloc(sizeof(pl_item));
    tmp->pos = pos;
    tmp->prev = *last;
    tmp->next = NULL;
    if (*last)
        (*last)->next = tmp;
    else
        *first = tmp;
    *last = tmp;
}

void pop_front_pl(pl_item** first, pl_item** last)
{
    if (*first) {
        pl_item* tmp;
        tmp = *first;
        *first = (*first)->next;
        if (*first) 
            (*first)->prev = NULL;
        else
            *last = NULL;
        free(tmp);
    }
}

void pop_back_pl(pl_item** first, pl_item** last)
{
    if (*last) {
        pl_item* tmp;
        tmp = *last;
        *last = (*last)->prev;
        if (*last)
            (*last)->next = NULL;
        else 
            *first = NULL;
        free(tmp);
    }
}

void clear_pl(pl_item** first, pl_item** last) 
{
    if (*first) {
        *first = (*first)->next;
        while (*first) {
            free((*first)->prev);
            *first = (*first)->next;
        }
        free(*last);
        *last = NULL;
    }
}

void remove_pl(pl_item** first, pl_item** last, pl_item* item)
{
    if (item->prev) 
        item->prev->next = item->next;
    else
        *first = item->next;
    if (item->next)
        item->next->prev = item->prev;
    else
        *last = item->prev;

    free(item);
}
