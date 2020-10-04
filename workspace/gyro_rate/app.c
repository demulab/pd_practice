#include "ev3api.h"
#include "app.h"

#define GYRO_PORT EV3_PORT_4

void main_task(intptr_t exinf) {
	int16_t angular_velocity;                                    /* 角速度の値[deg/s] */
	char angular_velocity_str[32];                               /* 角速度を表示するための文字列 */
	
	ev3_sensor_config(GYRO_PORT, GYRO_SENSOR);                  /* PORT1にジャイロセンサを設定 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                           /* LCDフォント設定 */
	ev3_gyro_sensor_reset(GYRO_PORT);                           /* ジャイロセンサの角位置をゼロにリセット */
	
	while(1){
		angular_velocity = ev3_gyro_sensor_get_rate(GYRO_PORT); /* 角速度を取得 */
		sprintf(angular_velocity_str, "RATE[deg/s]: %d", angular_velocity);
		ev3_lcd_draw_string(angular_velocity_str, 0, 10);        /* 角速度の値を表示 */
		syslog(LOG_NOTICE, "RATE[deg/s]: %d", angular_velocity);
		tslp_tsk(10000);                                         /* 10000us刻みで実行 */
	}
	
	ext_tsk();                                                   /* タスク終了処理 */
}
