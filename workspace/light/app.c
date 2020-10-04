#include "ev3api.h"
#include "app.h"

#define COLOR_SENSOR_PORT  EV3_PORT_2

void main_task(intptr_t exinf) {
	uint8_t ambient;                                        /* 環境光の強さの値 */
	uint8_t reflect;                                        /* 反射光の強さの値 */
	char ambient_str[32];                                   /* 環境光の強さを表示するための文字列 */
	char reflect_str[32];                                   /* 反射光の強さを表示するための文字列 */
	
	ev3_sensor_config(COLOR_SENSOR_PORT, COLOR_SENSOR);     /* ポートにカラーセンサを設定 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                      /* LCDフォント設定 */

	while(1){
		ambient = ev3_color_sensor_get_ambient(COLOR_SENSOR_PORT); /* 環境光の強さを取得 */
		reflect = ev3_color_sensor_get_reflect(COLOR_SENSOR_PORT); /* 反射光の強さを取得 */
		sprintf(ambient_str, "AMBIENT: %3d", ambient);
                                       
 		sprintf(reflect_str, "REFLECT: %3d", reflect);
		ev3_lcd_draw_string(ambient_str, 0, 10);            /* 環境光の強さの値を表示 */
    	ev3_lcd_draw_string(reflect_str, 0, 30);            /* 反射光の強さの値を表示 */
		tslp_tsk(100000);                                   /* 100us刻みで実行 */
	}
	
	ext_tsk();                                              /* タスク終了処理 */
}
