#include "gptim.h"

static __IO TIMx_SR_t *tim2_sr = (__IO TIMx_SR_t *)(TIM2_BASE_RD + TIMx_SR_OFFSET);

void tim2_1hz_init(void)
{
	// Initialize structures
	__IO RCC_APB1ENR_t *apb1 = (__IO RCC_APB1ENR_t *)(RCC_BASE_RD + RCC_APB1ENR_OFFSET);
	__IO TIMx_PSC_t *tim2_psc = (__IO TIMx_PSC_t *)(TIM2_BASE_RD + TIMx_PSC_OFFSET);
	__IO TIMx_ARR_t *tim2_arr = (__IO TIMx_ARR_t *)(TIM2_BASE_RD + TIMx_ARR_OFFSET);
	__IO TIMx_CNT_t *tim2_cnt = (__IO TIMx_CNT_t *)(TIM2_BASE_RD + TIMx_CNT_OFFSET);
	__IO TIMx_CR1_t *tim2_cr1 = (__IO TIMx_CR1_t *)(TIM2_BASE_RD + TIMx_CR1_OFFSET);
	
	// Enable clock for TIM2
	apb1->fields.tim2_en = 1;
	
	// Set prescaler value
	tim2_psc->fields.psc = 7200 - 1; // 72 000 000 / 7200 = 10 000
	
	// Set auto-reload value
	tim2_arr->fields.arr = 10000 - 1; // 10 000 / 10 000 = 1Hz
	
	// Clear counter
	tim2_cnt->fields.cnt = 0;
	
	// Enable timer
	tim2_cr1->fields.cen = 1;
}

void tim2_output_compare(void)
{
	// Initialize structures
	__IO RCC_APB1ENR_t *apb1 = (__IO RCC_APB1ENR_t *)(RCC_BASE_RD + RCC_APB1ENR_OFFSET);
	__IO TIMx_PSC_t *tim2_psc = (__IO TIMx_PSC_t *)(TIM2_BASE_RD + TIMx_PSC_OFFSET);
	__IO TIMx_ARR_t *tim2_arr = (__IO TIMx_ARR_t *)(TIM2_BASE_RD + TIMx_ARR_OFFSET);
	__IO TIMx_CNT_t *tim2_cnt = (__IO TIMx_CNT_t *)(TIM2_BASE_RD + TIMx_CNT_OFFSET);
	__IO TIMx_CR1_t *tim2_cr1 = (__IO TIMx_CR1_t *)(TIM2_BASE_RD + TIMx_CR1_OFFSET);
	
	// Enable clock for TIM2
	apb1->fields.tim2_en = 1;
	
	// Set prescaler value
	tim2_psc->fields.psc = 7200 - 1; // 72 000 000 / 7200 = 10 000
	
	// Set auto-reload value
	tim2_arr->fields.arr = 10000 - 1; // 10 000 / 10 000 = 1Hz
	
	// Clear counter
	tim2_cnt->fields.cnt = 0;
	
	// Enable timer
	tim2_cr1->fields.cen = 1;
}

void tim3_input_capture(void)
{
	// Initialize structures
	__IO RCC_APB1ENR_t *apb1 = (__IO RCC_APB1ENR_t *)(RCC_BASE_RD + RCC_APB1ENR_OFFSET);
	__IO TIMx_PSC_t *tim3_psc = (__IO TIMx_PSC_t *)(TIM3_BASE_RD + TIMx_PSC_OFFSET);
	__IO TIMx_ARR_t *tim3_arr = (__IO TIMx_ARR_t *)(TIM3_BASE_RD + TIMx_ARR_OFFSET);
	__IO TIMx_CNT_t *tim3_cnt = (__IO TIMx_CNT_t *)(TIM3_BASE_RD + TIMx_CNT_OFFSET);
	__IO TIMx_CR1_t *tim3_cr1 = (__IO TIMx_CR1_t *)(TIM3_BASE_RD + TIMx_CR1_OFFSET);
	
	// Enable clock for TIM3
	apb1->fields.tim3_en = 1;
	
	// Set prescaler value
	tim3_psc->fields.psc = 7200 - 1; // 72 000 000 / 7200 = 10 000
	
	// Set auto-reload value
	tim3_arr->fields.arr = 10000 - 1; // 10 000 / 10 000 = 1Hz
	
	// Clear counter
	tim3_cnt->fields.cnt = 0;
	
	// Enable timer
	tim3_cr1->fields.cen = 1;
}

bool getUpdateInterruptFlag(void)
{
	return tim2_sr->fields.uif;
}

void resetUpdateInterruptFlag(void)
{
	tim2_sr->fields.uif = 0;
}
