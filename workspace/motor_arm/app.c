#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	int angle = 300;                           /* 回転角度の値[deg] */
	uint32_t power = 100;                      /* パワー　0～+100 */
	char angle_str[32];                       /* 回転角度を表示するための文字列 */
	char power_str[32];                       /* パワーを表示するための文字列 */

	sprintf(angle_str, "ANGLE: %d", angle);   /* 回転角度を表示するための文字列作成 */
	sprintf(power_str, "POWER: %d", power);   /* パワーを表示するための文字列作成 */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);        /* LCDフォント設定 */
	ev3_lcd_draw_string(angle_str, 0, 10);    /* 回転角度の値を表示 */
	tslp_tsk(10000);                          /* 10,000us動作 */
	ev3_lcd_draw_string(power_str, 0, 30);    /* パワーの値を表示 */
	tslp_tsk(10000);                          /* 10,000us動作 */

	ev3_motor_config(EV3_PORT_C, MEDIUM_MOTOR); /* PORT CにモータMを設定 */
	ev3_motor_reset_counts(EV3_PORT_C);         /* PORT Cのモータの角位置をゼロにリセット */

	//ev3_motor_rotate(EV3_PORT_C, angle, power, false); /* 指定した回転角度、回転スピード（パワー）で回転動作 */
                      
	ev3_motor_set_power(EV3_PORT_C, 10);
	tslp_tsk(5000000);                        /* 3,000,000[us]=3[s]動作 */

	//ev3_motor_rotate(EV3_PORT_C, -angle, power, false); /* 指定した回転角度、回転スピード（パワー）で回転動作 */
 	ev3_motor_set_power(EV3_PORT_C, -10);
 	tslp_tsk(5000000);                        /* 3,000,000[us]=3[s]動作 */

	ev3_motor_stop(EV3_PORT_C, true);         /* モータの停止 */
	                                  /* ブレーキモードの指定 true: ブレーキモード  false: フロートモード */
	tslp_tsk(1000000);                        /* 1,000,000us待機 */

	ext_tsk();                                /* タスク終了処理 */
}
