#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	int32_t arm_angle;
	uint32_t power = 1;                      /* 回転スピード（パワー）-100～+100 */
	uint32_t count = 0;
	char angle_str[32];                      /* 角度表示用の文字列 */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);         /* LCDフォント設定 */

	ev3_motor_config(EV3_PORT_C, MEDIUM_MOTOR); /* PORT Cにモータ Mを設定 */

	while (1) {
		if (count++ == 30) power = - power;
		ev3_motor_set_power(EV3_PORT_C, power);    /* 指定したパワーで回転動作 */
		arm_angle = ev3_motor_get_counts(EV3_PORT_C);
		syslog(LOG_NOTICE, "ARM ANGLE[deg]: %4ld", arm_angle);
		sprintf(angle_str, "ARM ANGLE[deg]: %4ld", arm_angle);  /* 回転角度を表示するための文字列作成 */		
		ev3_lcd_draw_string(angle_str,  0, 50);              /* 回転角度の値を表示 */
		//tslp_tsk(100000);                                    /*  100,000us 刻みで動作 */
		tslp_tsk(100000);                                    /*  100,000us 刻みで動作 */
	}
		
	ext_tsk();                                 /* タスク終了処理 */
}
	