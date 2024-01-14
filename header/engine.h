#ifndef ENGINE_H_INCLUDE
#define ENGINE_H_INCLUDE

#include "render.h"

enum mode { rnd, series };

void collect_balls( pl_item** first, pl_item** last,
                    field tree,  int height, int row,   int col );
void update_balls(pl_item* first, pl_item* last, int mode, int* color);
void add_snow(int col, pl_item** first, pl_item** last);
void update_snow( pl_item** first, pl_item** last, const field tree,
                  int height, int row, int col );

#endif
