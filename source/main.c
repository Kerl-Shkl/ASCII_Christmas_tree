#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include "../header/engine.h"
#include "../header/render.h"

enum { key_escape = 27 };
enum { tick_delay=100 };

static const char* Menu_message[] = { " ---------------- ", 
                                      "|esc: quit       |",
                                      "|m: switch mode  |",
                                      " ---------------- " };

static void print_menu(int col)
{
    int i;
    attrset(COLOR_PAIR(white));
    for (i = 0; i < 4; i++) {
        mvaddstr(i, col-strlen(Menu_message[0]), Menu_message[i]);
    }
}

static void handle_resize(int* row, int* col, int* height, field* tree,
                          pl_item** first, pl_item** last)
{
    if (*tree)
        delete_tree(*tree, *height);
    if (*first)
        clear_pl(first, last);
    update_geom(row, col, height);
    if (*row < 10 || *col < 6) {
        endwin();
        fprintf(stderr, "To small terminal\n");
        exit(0);
    }
    *tree = generate_tree(*height);
    collect_balls(first, last, *tree, *height, *row, *col);
    fill_screen_black(*row, *col);
    draw_tree(*row, *col, *height, *tree);
}

int main(void)
{
    field tree = NULL;
    int row, col, height, key;
    int mode = series, color = red;
    const int update_balls_ticks=10, update_snow_ticks=7;
    int balls_ticks=update_balls_ticks, snow_ticks = update_snow_ticks;
    pl_item *first_ball = NULL, *last_ball = NULL;
    pl_item *first_snowflake = NULL, *last_snowflake = NULL;

    srand(time(NULL));
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    start_color();

    init_color_pairs();
    handle_resize(&row, &col, &height, &tree, &first_ball, &last_ball);


    timeout(tick_delay);
    while ((key = getch()) != key_escape) {

        switch (key) {
        case KEY_RESIZE:
            handle_resize(&row, &col, &height,
                          &tree, &first_ball, &last_ball);
            draw_snow(first_snowflake, last_snowflake);
            break;
        case 'm':
            mode = mode == rnd ? series : rnd;
        }

        balls_ticks++;
        snow_ticks++;
        if (balls_ticks >= update_balls_ticks) {
            balls_ticks = 0;
            update_balls(first_ball, last_ball, mode, &color);
        }
        if (snow_ticks >= update_snow_ticks) {
            snow_ticks = 0;
            paint_over_snow(first_snowflake, last_snowflake);
            update_snow(&first_snowflake, &last_snowflake, tree, height, row, col);
            add_snow(col, &first_snowflake, &last_snowflake);
            draw_snow(first_snowflake, first_snowflake);
        }
        
        print_menu(col);
        refresh();
    }
        
    endwin();

    return 0;
}
