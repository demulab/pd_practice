#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	colorid_t color;                                        /* カラーの値 */
	char color_str[32];                                     /* 色を表示するための文字列 */
	
	ev3_sensor_config(EV3_PORT_1, COLOR_SENSOR);            /* PORT1にカラーセンサを設定 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                      /* LCDフォント設定 */

	while(1){
		color = ev3_color_sensor_get_color(EV3_PORT_1);     /* カラー情報の取得 */
		switch(color) {
			case COLOR_NONE:
				sprintf(color_str, "COLOR:   NONE(%d)", color);
				break;
			case COLOR_BLACK:
				sprintf(color_str, "COLOR:  BLACK(%d)", color);
				break;
			case COLOR_BLUE:
				sprintf(color_str, "COLOR:   BLUE(%d)", color);
				break;
			case COLOR_GREEN:
				sprintf(color_str, "COLOR:  GREEN(%d)", color);
				break;
			case COLOR_YELLOW:
				sprintf(color_str, "COLOR: YELLOW(%d)", color);
				break;
			case COLOR_RED:
				sprintf(color_str, "COLOR:    RED(%d)", color);
				break;
			case COLOR_WHITE:
				sprintf(color_str, "COLOR:  WHITE(%d)", color);
				break;
			case COLOR_BROWN:
				sprintf(color_str, "COLOR:  BROWN(%d)", color);
				break;
			default:
				sprintf(color_str, "COLOR:   NONE(%d)", color);
				break;
		}
		
		ev3_lcd_draw_string(color_str, 0, 10);              /* 色表示 */
		tslp_tsk(100);                                      /* 100ms刻みで実行 */
	}
	
	ext_tsk();                                              /* タスク終了処理 */
}
