#ifndef RENDER_H_INCLUDE
#define RENDER_H_INCLUDE

#include <curses.h>
#include "generator.h"
#include "position.h"

enum colors {
    green = 1, red, yellow, blue, magenta, cyan, white
};
enum { color_count = 8 };
extern const int all_colors[color_count];

void draw_snow(pl_item* first, pl_item* last);
void paint_over_snow(pl_item* first, pl_item* last);
void draw_balls(pl_item* first, pl_item* last, int mode);
void draw_tree(int row, int col, int height, field tree);
void update_geom(int* row, int* col, int* height);
void init_color_pairs();
int star_y(int height, int row);
int width(int height);
void fill_screen_black(int row, int col);

#endif
