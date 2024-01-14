#ifndef GENERATOR_H_INCLUDE
#define GENERATOR_H_INCLUDE

#include <string.h>
#include <stdlib.h>

enum { pot_height = 1,
       pot_width  = 5,
       top_height = 3,
       top_width  = 5,
       nice_pot_minimum = 13 };

#define Ball 'o'

typedef char** field;

field generate_tree(int height);
void delete_tree(field tree, int height);

#endif
