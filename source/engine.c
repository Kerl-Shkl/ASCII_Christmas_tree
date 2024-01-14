#include "../header/engine.h"

void collect_balls(pl_item** first, pl_item** last,
                   field tree, int height,
                   int row, int col)
{
    int i, j; 
    for (i = 0; i < height; i++) {
        for (j = 0; j < width(height); j++) {
            if (tree[i][j] == Ball) {
                ascii_symbol symbol;
                symbol.x = (col - width(height)) / 2 + j;
                symbol.y = star_y(height, row) + i;
                symbol.symbol = Ball;
                push_back_pl(first, last, symbol);
            }
        }
    }
}

void update_balls(pl_item* first, pl_item* last, int mode, int* color)
{
    switch (mode) {
    case rnd:
        draw_balls(first, last, -1); 
        break;
    case series:
        draw_balls(first, last, *color);
        (*color)++;
        if (*color >= color_count)
            *color = green + 1;
        break;
    }
}

void add_snow(int col, pl_item** first, pl_item** last) 
{
    int i;
    for (i = 0; i < col; i++) {
        if (rand() % 5 == 0) {
            ascii_symbol snow_flake;
            snow_flake.x = i;
            snow_flake.y = 0;
            push_back_pl(first, last, snow_flake);
        }
    }
}

static int is_on_tree( int x, int y, const field tree, 
                        int height, int row, int col )
{
    int lx, ly;
    lx = x - (col-width(height))/2;
    ly = y - (row - height);

    if ((lx < 0 || lx >= width(height)) || (ly < 0 || ly >= height))
        return 0;

    if (tree[ly][lx] != ' ')
        return 1;

    return 0;
}

void update_snow( pl_item** first, pl_item** last, const field tree,
                  int height, int row, int col ) 
{
    pl_item* current = *first;    
    while (current) {
        /*mvaddch(current->pos.y, current->pos.x, ' ');*/
        current->pos.y = current->pos.y + 1;
        if (is_on_tree(current->pos.x, current->pos.y, tree, height, row, col) || 
            current->pos.x >= col || current->pos.y >= row) 
        {
            if (current == *first) {
                pop_front_pl(first, last);
                current = *first;
            } else {
                pl_item* tmp = current->prev;
                remove_pl(first, last, current);
                current = tmp;
            }
        }
        if (!current)
            break;
        current = current->next;
    }
}

