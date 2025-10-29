#ifndef MULTI_DISPLAY_SPEAKER_A_H
#define MULTI_DISPLAY_SPEAKER_A_H

#include <kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

void main_task(intptr_t exinf);
void lcd_task(intptr_t exinf);
void sound_task(intptr_t exinf);

#ifdef __cplusplus
}
#endif
#endif

