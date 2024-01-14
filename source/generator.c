#include "../header/generator.h"

static void allocate_text(char*** text, int height, int width)
{
    int i;
    (*text) = (char**)malloc(sizeof(char*) * height);
    for (i = 0; i < height; i++) {
        (*text)[i] = (char*)malloc(sizeof(char)*width + 1);
        memset((*text)[i], ' ', width);
        (*text)[i][width] = 0;
    }
}

static int get_row_width(int idx, int width) 
{
    int a;
    a = ((idx + 1 - top_height + 1) & (~1)); /* first one because idx from 0*/
    return top_width + a;
}

static void make_row(char** row, int idx, int width)
{
    int row_width, start, end;
    int i;
    char interm;

    row_width = get_row_width(idx, width);
    start = (width - row_width) / 2;
    end = start + row_width - 1;
    interm = idx % 2 ? '/' : '\\';

    (*row)[start] = '/';
    (*row)[end] = '\\';
    for (i = 1; i < row_width-1; i++) {
        if (i % 2 != 0) 
            (*row)[start + i] = rand() % 3 ? '_' : Ball;
        else 
            (*row)[start + i] = interm;
    }
}

static void fill_tree(field* text, int height, int width)
{
    int i = 0;
    (*text)[i++][width/2] = '*';               /* top star * */
    memcpy((*text)[i++] + width/2 - 1, "/_\\", 3); /* first row /_\ */
    memcpy((*text)[i++] + width/2 - 2, "/_\\_\\", 5); /* second row /o\_\ */
    for (; i < height-pot_height-1; i++) {
        make_row((*text)+i, i, width);
    }
    memset((*text)[i], '^', width);
    if (width >= nice_pot_minimum) {
        memcpy((*text)[i] + (width-pot_width-2)/2, "[_____]", 7);
    }
    memcpy((*text)[i+1] + (width-pot_width)/2, "\\___/", 5);
}

field generate_tree(int height) 
{
    field text;
    int tree_height = height - pot_height;
    int width = top_width + ((tree_height - top_height) & (~1));

    allocate_text(&text, height, width);
    fill_tree(&text, height, width);

    return text;
}

void delete_tree(field tree, int height) 
{
    int i;
    for (i = 0; i < height; i++)
        free(tree[i]);
    free(tree);
}
