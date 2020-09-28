#include "ev3api.h"
#include "app.h"

#define TEMPO 250                                        /* 基本の音声出力持続時間の指定 */
#define VOLUME 10                                        /* 音量の指定（0～+100） */

void RingTone(int freq, int time, int vol){              /* 音符を再生するユーザー関数を定義 */
	ev3_speaker_set_volume(vol);                         /* 音量設定（0～+100) */
	ev3_speaker_play_tone(freq, time-50);                /* 音を鳴らす．周波数はHz，出力持続時間はミリ秒で指定． */
	tslp_tsk(time);                                      /* 指定時間待機 */
}

void main_task(intptr_t unused) {
	ev3_lcd_draw_string("START...", 20, 25);             /* 開始表示 */
	tslp_tsk(10000);                                     /*シミュレータではこれがないと文字が表示されない */

	RingTone(523, TEMPO*2, VOLUME);                      /* 指定した周波数と時間，音量で音を鳴らす */
	RingTone(587, TEMPO*2, VOLUME);
	RingTone(659, TEMPO*2, VOLUME);
	RingTone(698, TEMPO*2, VOLUME);
	RingTone(659, TEMPO*2, VOLUME);
	RingTone(587, TEMPO*2, VOLUME);
	RingTone(523, TEMPO*3, VOLUME);
	RingTone(659, TEMPO*2, VOLUME);
	RingTone(698, TEMPO*2, VOLUME);
	RingTone(784, TEMPO*2, VOLUME);
	RingTone(880, TEMPO*2, VOLUME);
	RingTone(784, TEMPO*2, VOLUME);
	RingTone(698, TEMPO*2, VOLUME);
	RingTone(659, TEMPO*3, VOLUME);
	tslp_tsk(TEMPO*3000);                                  /* 指定時間待機 */

	RingTone(523, TEMPO*2, VOLUME);
	tslp_tsk(TEMPO*2*3000);                                /* 指定時間待機 */
	RingTone(523, TEMPO*2, VOLUME);
	tslp_tsk(TEMPO*2*3000);                                /* 指定時間待機 */
	RingTone(523, TEMPO*2, VOLUME);
	tslp_tsk(TEMPO*2*3000);                                /* 指定時間待機 */
	RingTone(523, TEMPO*2, VOLUME);
	tslp_tsk(TEMPO*2*3000);                                /* 指定時間待機 */

	RingTone(523, TEMPO, VOLUME);
	RingTone(523, TEMPO, VOLUME);
	RingTone(587, TEMPO, VOLUME);
	RingTone(587, TEMPO, VOLUME);
	RingTone(659, TEMPO, VOLUME);
	RingTone(659, TEMPO, VOLUME);
	RingTone(698, TEMPO, VOLUME);
	RingTone(698, TEMPO, VOLUME);
	RingTone(659, TEMPO, VOLUME);
	tslp_tsk(TEMPO*3000);                                  /* 指定時間待機 */
	RingTone(587, TEMPO, VOLUME);
	tslp_tsk(TEMPO*3000);                                  /* 指定時間待機 */
	RingTone(523, TEMPO*3, VOLUME);
	tslp_tsk(TEMPO*3000);                                  /* 指定時間待機 */
	
	ev3_lcd_draw_string("THAT'S ALL !", 20, 40);           /* 終了表示 */

	ext_tsk();                                                /* タスク終了処理 */
}