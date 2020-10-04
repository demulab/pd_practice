#include "ev3api.h"
#include "app.h"

#define GYRO_PORT EV3_PORT_4

void main_task(intptr_t exinf) {
	int16_t angle;                                      /* 角位置の値[deg] */
	char angle_str[32];                                 /* 角位置を表示するための文字列 */
	
	ev3_sensor_config(GYRO_PORT, GYRO_SENSOR);          /* PORTにジャイロセンサを設定 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                  /* LCDフォント設定 */
	ev3_gyro_sensor_reset(GYRO_PORT);                   /* ジャイロセンサの角位置をゼロにリセット */
	
	while(1){
		angle = ev3_gyro_sensor_get_angle(GYRO_PORT);   /* 角位置を取得 */
		sprintf(angle_str, "ANGLE[deg]: %-4d", angle);
		syslog(LOG_NOTICE, "angle=%d", angle);
		ev3_lcd_draw_string(angle_str, 0, 10);          /* 角位置の値を表示 */
		tslp_tsk(10000);                                /* 10000us刻みで実行 */
	}
	
	ext_tsk();                                          /* タスク終了処理 */
}