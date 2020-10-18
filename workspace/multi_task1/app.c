/* multi_task1/app.c */
#include "ev3api.h"
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define COUNT 10000		/* カウント数を10000に定義 */
#define TIME_LOOP 1000000000

void main_task(intptr_t unused) {	
	int i,j,k;
	char buf[5];
	
	ev3_lcd_set_font(EV3_FONT_MEDIUM);
	
	act_tsk(SUB_TASK);
		
	for(i=0 ; i<=COUNT ; i++){		/* カウント数だけ繰り返す */		
		sprintf(buf, "MAIN TASK= %d", i);	         
		ev3_lcd_draw_string(buf, 0, 10);
			
		for(j=0; j<=TIME_LOOP; j++){		/* 時間待ちを行う */
			for(k=0; k<=TIME_LOOP; k++){
			}
		};
	}
	
	ext_tsk();					/* 処理終了 */
}


void sub_task(intptr_t unused) {
	int i,j,k;
	char buf[5];
	
	ev3_lcd_set_font(EV3_FONT_MEDIUM);	
		
	for(i=0 ; i<=COUNT ; i++){		/* カウント数だけ繰り返す */		
		sprintf(buf, "SUB  TASK= %d", i);
		ev3_lcd_draw_string(buf, 0, 10+18*2);
			
		for(j=0; j<=TIME_LOOP; j++){		/* 時間待ちを行う */
			for(k=0; k<=TIME_LOOP; k++){
			}
		}
	}

	ext_tsk();					/* 処理終了 */
}
