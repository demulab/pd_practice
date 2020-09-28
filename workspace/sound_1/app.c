#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	int battery;                                            /* バッテリーの残量（int） */
	char battery_str[32];                                   /* バッテリーの残量を表示するための文字列 */

	battery = ev3_battery_voltage_mV();                     /* バッテリーの残量を取得 */
	sprintf(battery_str, "BATTERY: %d", battery);           /* バッテリーの残量を表示するための文字列作成 */
	ev3_lcd_set_font(EV3_FONT_MEDIUM);                      /* LCDフォント設定 */
	ev3_lcd_draw_string(battery_str, 20, 5);                /* バッテリーの残量を表示 */
	tslp_tsk(10000);
	
	ev3_lcd_draw_string("START...", 20, 25);                /* 開始表示 */
	tslp_tsk(10000);

	ev3_speaker_set_volume(1);                              /* 音量設定（0～100．0はミュート．100超えると+100になる．） */
	ev3_speaker_play_tone(440, 100);                        /* 音を鳴らす（440Hzで100ミリ秒鳴らす．） */
	tslp_tsk(100000);                                       /* 100000us=100ms待機 */
	ev3_speaker_stop();                                     /* 音を停止する */
	ev3_lcd_draw_string("THAT'S ALL !", 20, 45);            /* 終了表示 */

	ext_tsk();                                              /* タスク終了処理 */
} 