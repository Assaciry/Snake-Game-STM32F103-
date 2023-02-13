#ifndef GPTIM_H
#define GPTIM_H

#include "RegisterDefinitions.h"
#include <stdbool.h>

void tim2_1hz_init(void);
void tim2_output_compare(void);
void tim3_input_capture(void);
bool getUpdateInterruptFlag(void);
void resetUpdateInterruptFlag(void);

#endif
