#include "ev3api.h"
#include "app.h"

#define SONAR_PORT EV3_PORT_3

void main_task(intptr_t exinf) {
	int16_t distance;                                       /* 距離の値[cm] */
	bool_t listen;                                          /* 超音波を検出したかどうかを判定する値 */
	char listen_str[32];                                    /* 超音波を検出したかどうかを判定する値を表示するための文字列 */
	char distance_str[32]; 	
	
	// ev3_sensor_config(SONAR_PORT, ULTRASONIC_SENSOR);       /* PORT1に超音波センサを設定 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                      /* LCDフォント設定 */

	while(1){
		listen = ev3_ultrasonic_sensor_listen(SONAR_PORT);   /* 超音波を検出したかどうかを判定する値を取得 */
		if (listen) {
			ev3_lcd_draw_string("LISTEN:  TRUE", 0, 10);    /* 超音波を検出した */
			tslp_tsk(10000);
		} else {
			ev3_lcd_draw_string("LISTEN: FALSE", 0, 10);    /* 超音波を検出しなかった */
			tslp_tsk(10000);
		}
		sprintf(listen_str, "SIGNAL: %d", listen);
		ev3_lcd_draw_string(listen_str, 0, 30);             /* 超音波を検出したかどうかを判定する値を表示 */
		tslp_tsk(10000);

		distance = ev3_ultrasonic_sensor_get_distance(SONAR_PORT); /* 距離の値を取得 */
		sprintf(distance_str, "DISTANCE: %3d [cm]", distance);
		ev3_lcd_draw_string(distance_str, 0, 50);                  /* 距離を表示 */

		ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE); /* 画面クリア */
		tslp_tsk(100000);                                   /* 100000ms刻みで実行 */
	}
	
	ext_tsk();                                              /* タスク終了処理 */
}
