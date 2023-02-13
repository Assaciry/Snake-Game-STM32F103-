#include "Snake.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

const int XMAX = 83;
const int YMAX = 40;
#define MAXSIZE 100

typedef struct loc_xy{
	int x;
	int y;
} loc_xy_t;

loc_xy_t snake_locs[MAXSIZE];
loc_xy_t food_pos;

int snake_size;
int current_direction;
volatile uint32_t score;
volatile uint32_t difficulty;

int warp_to_other_side(int val, int max)
{
  if(val <= 0){
		val = max-1;
	} else if(val >= max){
		val = 1;
	}
	return val;
}

/*
	Helper function to spawn food at a pseudo-random position
*/
loc_xy_t spawn_food(void){
	int x,y;
	loc_xy_t pos; 
	
	// generate random location in range 1-81 and 1-45
	x = next_int()%(XMAX-2) + 1;
	y = next_int()%(YMAX-2) + 1;
	
	pos.x = x;
	pos.y = y;
	
	return pos;
}

/*
	Initialize snake at the center of the LED
	headed towards right with total snake size = 3
*/
void snake_init(void){
	// Init head piece
	const int hwidth = XMAX/2;
	const int hheight = YMAX/2;
	
	loc_xy_t temp = {hwidth,hheight};
	
	// Init random seed
	seed(9803161);
	
	snake_size = 3;
	current_direction = RIGHT;
	difficulty = 0;
	score = 0;
	
	// Init two body pieces
	snake_locs[0] = temp;
	temp.x = hwidth-1;
	snake_locs[1] = temp;
	temp.x = hwidth-2;
	snake_locs[2] = temp;
	
	// Spawn the initial food
	food_pos = spawn_food();
}

/*
	Move snake towards {direction}, check self-intersection
	return false if it intersect with itself, return true if not.
*/
bool snake_move_forward(void){
	int i;
	
	loc_xy_t tmp;
	loc_xy_t next = snake_locs[0];
	
	if(current_direction == RIGHT){
		next.x = warp_to_other_side(snake_locs[0].x + 1,XMAX);
	} else if(current_direction == LEFT){
		next.x = warp_to_other_side(snake_locs[0].x - 1,XMAX);
	} else if(current_direction == UP){
		next.y = warp_to_other_side(snake_locs[0].y + 1,YMAX);
	} else if(current_direction == DOWN){
		next.y = warp_to_other_side(snake_locs[0].y - 1,YMAX);
	}
	
	for(i = 0; i < snake_size; ++i){
		tmp = snake_locs[i];
		snake_locs[i] = next;
		next = tmp;
		
		// Check self-intersection after moving snake
		if(i > 0 && snake_locs[0].x == snake_locs[i].x && snake_locs[0].y == snake_locs[i].y){
			return false;
		}
	}
	
	return true;
}

void snake_turn(int direction){
	if(direction == UP && current_direction != DOWN){
		current_direction = UP;
	} 
	if(direction == DOWN && current_direction != UP){
		current_direction = DOWN;
	} 
	if(direction == LEFT && current_direction != RIGHT){
		current_direction = LEFT;
	}
	if(direction == RIGHT && current_direction != LEFT){
		current_direction = RIGHT;
	}
}

bool snake_eat(void){
	loc_xy_t temp;
	//bool is_food_spawned_on_free_space = false;
	//int i;
	
	if(food_pos.x == snake_locs[0].x && food_pos.y == snake_locs[0].y){
		// new snake piece is obtained by relative positions of last two snake pieces
		temp.x = snake_locs[snake_size-1].x+(snake_locs[snake_size-1].x - snake_locs[snake_size-2].x);
		temp.y = snake_locs[snake_size-1].y+(snake_locs[snake_size-1].y - snake_locs[snake_size-2].y);
		
		snake_locs[snake_size] = temp;
		snake_size+=1;
		
		/*
		// To ensure that the food did not spawn on a snake position
		while(!is_food_spawned_on_free_space){
			REP: food_pos = spawn_food();
			for(i=0;i<snake_size;++i){
				if(snake_locs[i].x == food_pos.x && snake_locs[i].y == food_pos.y) goto REP;
			}
			is_food_spawned_on_free_space = true;
		}
		*/
		
		return true;
	}
	return false;
}

void snake_draw(void){
	int i;
	for(i=0;i < snake_size;++i){
		loc_xy_t snk = snake_locs[i];
		set_pixel(snk.x,snk.y,1);
	}
	set_pixel(food_pos.x,food_pos.y,1);
}

