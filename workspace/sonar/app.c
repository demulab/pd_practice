#include "ev3api.h"
#include "app.h"

#define SONAR_PORT EV3_PORT_3

void main_task(intptr_t exinf) {
	int16_t distance;                                              /* 距離の値[cm] */
	char distance_str[32];                                         /* 距離を表示するための文字列 */
	
	ev3_sensor_config(SONAR_PORT, ULTRASONIC_SENSOR);              /* ポートに超音波センサを設定 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                             /* LCDフォント設定 */

	while(1){
		distance = ev3_ultrasonic_sensor_get_distance(SONAR_PORT); /* 距離の値を取得 */
		sprintf(distance_str, "DISTANCE: %3d [cm]", distance);
		ev3_lcd_draw_string(distance_str, 0, 10);                  /* 距離を表示 */

		tslp_tsk(100000);                                          /* 100000us刻みで実行 */
	}
	
	ext_tsk();                                                     /* タスク終了処理 */
}
