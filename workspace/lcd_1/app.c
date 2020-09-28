#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	ev3_lcd_draw_string("hello, world", 0, 10); 
	ext_tsk();   /* タスク終了処理 */                                    
}