#ifndef POSITION_H_INCLUDE
#define POSITION_H_INCLUDE

#include "stdlib.h"

typedef struct {
    int x;
    int y;
    int color;
    int symbol;
} ascii_symbol;

struct t_pl_item {
    ascii_symbol pos;
    struct t_pl_item* next;
    struct t_pl_item* prev;
};

typedef struct t_pl_item pl_item;
typedef pl_item* list_points;

void push_front_pl(pl_item** first, pl_item** last, ascii_symbol pos);
void push_back_pl(pl_item** first, pl_item** last, ascii_symbol pos);
void pop_front_pl(pl_item** first, pl_item** last);
void pop_back_pl(pl_item** first, pl_item** last);
void clear_pl(pl_item** first, pl_item** last);
void remove_pl(pl_item** first, pl_item** last, pl_item* item);

#endif
