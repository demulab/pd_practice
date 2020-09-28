#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf)
{
	int count;
	char str[32];					   /* カウントを表示するための文字列 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM); /* LCDに表示するフォントの設定 */

	while (1)
	{
		sprintf(str, "COUNT:%d", count); /* カウントを表示用の文字列作成 */
		ev3_lcd_draw_string(str, 30, 60); /* 指定した位置にカウントを表示 */
		tslp_tsk(10000);				 //　シミュレーションのみ必要 10,000us); 

		ev3_lcd_fill_rect(10, 10, 100, 20, EV3_LCD_BLACK); /* 指定した位置に矩形表示 */
		tslp_tsk(10000);				 //　シミュレーションのみ必要 10,000us); 
		/* 100000us(1000ms) 刻みで実行 */ 
		count++; 
	}
	
	/* LCD画面全体を白く塗り潰す（クリアする）*/ 
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE); 
	tslp_tsk(5000000);
	ext_tsk();						 /* タスク終了処理 */
}