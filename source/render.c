#include "../header/render.h"

const int all_colors[color_count] = {
    COLOR_BLACK, COLOR_GREEN, COLOR_RED, COLOR_YELLOW,
    COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE
};

int width(int height)
{
    return top_width + ((height - pot_height - top_height) & (~1));
}

int star_y(int height, int row) 
{
    return row - height;
}

void init_color_pairs()
{
    int i;
    for (i = green; i < color_count; i++)
        init_pair(i, all_colors[i], COLOR_BLACK);
}

void update_geom(int* row, int* col, int* height) 
{
    getmaxyx(stdscr, *row, *col);
    *height = 0.7 * (*row);
   
    while (width(*height) >= *col) {
        (*height)--;
    }
}

void draw_tree(int row, int col, int height, field tree)
{
    int i, j;
    int start_y = star_y(height, row);
    int tree_margin = (col - width(height)) / 2;

    attrset(COLOR_PAIR(white) | A_BOLD);
    move(start_y, tree_margin);
    addstr(tree[0]);
    attroff(A_BLINK);

    attrset(COLOR_PAIR(green) | A_BOLD);
    for (i = 1; i < height-2; i++) {
        move(start_y+i, tree_margin);
        addstr(tree[i]);
    }

    move(start_y+i, tree_margin);
    for (j = 0; j < width(height); j++) {
        if (tree[i][j] != '^')
            attrset(COLOR_PAIR(yellow) | A_BOLD);
        else 
            attrset(COLOR_PAIR(green) | A_BOLD);
        addch(tree[i][j]);
    }

    i++;
    move(start_y+i, tree_margin);
    attrset(COLOR_PAIR(yellow));
    addstr(tree[i]);

}

void draw_snow(pl_item* first, pl_item* last) 
{
    pl_item* current = first;
    attrset(COLOR_PAIR(white));
    while (current != NULL) {
        move(current->pos.y, current->pos.x);
        addch('.');
        current = current->next;
    }
}

void paint_over_snow(pl_item* first, pl_item* last)
{
    pl_item* current = first;
    attrset(COLOR_PAIR(white));
    while (current != NULL) {
        move(current->pos.y, current->pos.x);
        addch(' ');
        current = current->next;
    }
}

void draw_balls(pl_item* first, pl_item* last, int mode)
{
    pl_item* current = first;
    attrset(COLOR_PAIR(mode) | A_BOLD);
    while (current != NULL) {
        move(current->pos.y, current->pos.x);
        if (mode < 0) {
            attrset(COLOR_PAIR(rand() % (color_count-2) + 2) | A_BOLD);
        }
        addch(current->pos.symbol);

        current = current->next;
    }
}

void fill_screen_black(int row, int col)
{
    int i, j;
    move(0, 0);
    attrset(COLOR_PAIR(green));
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            addch(' ');
        }
    }
}


