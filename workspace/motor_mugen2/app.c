#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	int32_t left_angle, right_angle;
	uint32_t power = 10;                      /* 回転スピード（パワー）-100〜+100 */
	uint32_t count = 0;
	char left_angle_str[32];                   /* パワーを表示用の文字列 */
	char right_angle_str[32];                  /* パワーを表示用の文字列 */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);         /* LCDフォント設定 */

	ev3_motor_config(EV3_PORT_A, LARGE_MOTOR); /* PORT AにモーターLを設定 */
	ev3_motor_config(EV3_PORT_B, LARGE_MOTOR); /* PORT BにモーターLを設定 */

	while (1) {
		if (count++ == 100) power = - power;
		ev3_motor_set_power(EV3_PORT_A, power);    /* 指定したパワーで回転動作 */
		ev3_motor_set_power(EV3_PORT_B, power);    /* 指定したパワーで回転動作 */
		left_angle = ev3_motor_get_counts(EV3_PORT_A);
		right_angle = ev3_motor_get_counts(EV3_PORT_B);
		sprintf(left_angle_str,  "LEFT  ANGLE[deg]: %4ld", left_angle);  /* 回転角度を表示するための文字列作成 */
		sprintf(right_angle_str, "RIGHT ANGLE[deg]: %4ld", right_angle); /* 回転角度を表示するための文字列作成 */
		ev3_lcd_draw_string(left_angle_str,  0, 10);                /* 回転角度の値を表示 */
		tslp_tsk(10000);                                            /* シミュレータLCD用のスリープ */
		ev3_lcd_draw_string(right_angle_str, 0, 30);                /* 回転角度の値を表示 */
		tslp_tsk(90000);                                            /*  90,000us 刻みで動作 */

	}
		
	ext_tsk();                                 /* タスク終了処理 */
}
	