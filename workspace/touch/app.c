#include "ev3api.h"
#include "app.h"

#define TOUCH_PORT EV3_PORT_1

void main_task(intptr_t exinf) {
	ev3_sensor_config(TOUCH_PORT, TOUCH_SENSOR);            /* タッチセンサを設定 */

	ev3_lcd_draw_string("Waiting...", 0, 30);
	while(!ev3_touch_sensor_is_pressed(TOUCH_PORT)){        /* タッチセンサの状態を確認 */
		tslp_tsk(100000);                                   /* 100,000us刻みで実行 */
	}
	ev3_lcd_draw_string("Pressed!", 0, 30);                 /* タッチセンサが押されたことを表示 */

	ext_tsk();                                              /* タスク終了処理 */
}