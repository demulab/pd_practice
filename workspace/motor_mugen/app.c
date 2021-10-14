#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	uint32_t power = 100;                      /* 回転スピード（パワー）-100～+100 */
	char power_str[32];                        /* パワーを表示用の文字列 */

	sprintf(power_str, "POWER: %d",(int) power);   /* パワーを表示用の文字列作成 */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);         /* LCDフォント設定 */
	ev3_lcd_draw_string(power_str, 0, 30);     /* パワーの値を表示 */

	ev3_motor_config(EV3_PORT_A, LARGE_MOTOR); /* PORT AにモーターLを設定 */
	ev3_motor_config(EV3_PORT_B, LARGE_MOTOR); /* PORT BにモーターLを設定 */

	ev3_motor_set_power(EV3_PORT_A, power);    /* 指定したパワーで回転動作 */
	ev3_motor_set_power(EV3_PORT_B, power);    /* 指定したパワーで回転動作 */
	
	ext_tsk();                                 /* タスク終了処理 */
}
	
