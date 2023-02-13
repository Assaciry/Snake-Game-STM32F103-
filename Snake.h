#ifndef SNAKE_H
#define SNAKE_H

#include "LCD.h"
#include "xor_random.h"

typedef struct loc_xy loc_xy_t;

void snake_init(void);
bool snake_move_forward(void);
void snake_turn(int direction);
bool snake_eat(void);
void snake_draw(void);

#endif
