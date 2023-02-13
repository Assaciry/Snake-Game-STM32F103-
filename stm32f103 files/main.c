#include "RegisterDefinitions.h"
#include "stdio_usart.h"
#include "LCD.h"
#include "Snake.h"
#include "Button_IO.h"
#include <stdbool.h>
#include "delay.h"
#include "xor_random.h"

#define MIN(a,b) a<=b ? a : b

#define LCD_WIDTH   84 // Note: x-coordinates go wide
#define LCD_HEIGHT  48 // Note: y-coordinates go high
#define WHITE       0  // For drawing pixels. A 0 draws white.
#define BLACK       1  // A 1 draws black.

volatile int btn_state = 0;
volatile uint64_t time_val = 0;
const uint32_t base_delay = 180U;

extern volatile uint32_t score;
extern volatile uint32_t difficulty;
extern const int XMAX;
extern const int YMAX;

// For onboard LED
static __IO GPIOx_ODR_t *gpioc_odr = (__IO GPIOx_ODR_t *)(GPIOC_BASE_RD + GPIO_ODR_OFFSET);


/*
TODO: Save high score
TODO: Check food spawn is on a snake location

PINOUT:
	PC15: Onboard LED 
	
	PA:
	PA:
	PA:
	PA:
	
	PB1:  Button for turn down input
	PB4:  Button for turn up input
	PB7:  Button for turn right input
	PB14: Button for turn left input
*/

void power_up_screen()
{
	gpioc_odr->fields.odr15 = 1;
}

void power_down_screen()
{
	gpioc_odr->fields.odr15 = 0;
}

void init_on_board_led_screenlight()
{
	__IO RCC_APB2ENR_t *apb2 = (__IO RCC_APB2ENR_t *)(RCC_BASE_RD + RCC_APB2ENR_OFFSET);
	__IO GPIOx_CRH_t *crh    = (__IO GPIOx_CRH_t *)(GPIOC_BASE_RD + GPIO_CRH_OFFSET);
	
	apb2->fields.iop_c_en = 1;
	crh->fields.cnf13 = GPIO_CNF_GENERAL_OUT_PP;
	crh->fields.mode13 = GPIO_OUT_MODE_2MHz;
	
	// PC15 for screenlight
	crh->fields.cnf15 = GPIO_CNF_GENERAL_OUT_PP;
	crh->fields.mode15 = GPIO_OUT_MODE_2MHz;
}

void init_all()
{
	delayInit();
	init_on_board_led_screenlight();
	usart1_tx_init();
	spi1_init();
	btn_io_init();
	power_up_screen();
	LCD_init();
}

void reset_game(void){
	set_str("Game Over!",15,10,BLACK);
	print_score(score);
	update_display();
	delayMs(3000);
	snake_init();
}

int main(void)
{	
	bool led = false;
	int prev_st = btn_state;
	
	init_all();
	
	snake_init();
	update_display();
	set_contrast(0xBB);
	delayMs(1000);
	clear_display(WHITE);
	
	/* GAME LOOP */
	while(1)
	{
		time_val += 1;
		
		// Blink on-board LED
		gpioc_odr->fields.odr13 = led;
		led = !led;
		
		// Input and movement
		if(prev_st != btn_state)
			snake_turn(btn_state);
		prev_st = btn_state;
		
		// Move snake and check for self-intersection
		if(!snake_move_forward()){
			// Game over, reset
			reset_game();
		}
		
		// Check for food eating
		if(snake_eat()){
			score+=10;
			difficulty=MIN(difficulty+5,160);
		}
		
		// Draw screen border
		set_rect(0,0,XMAX, YMAX, false, BLACK);
		// Draw snake
		snake_draw();
		// Print score on the LED
		print_score(score);
		
		update_display();
		seed(time_val);
		delayMs(base_delay-difficulty);
		clear_display(WHITE);
	}
	
}
