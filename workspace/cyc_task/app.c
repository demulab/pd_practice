#include "ev3api.h"
#include "app.h"

#define TEMPO 18                                        /* 基本の音声出力持続時間の指定 */
#define VOLUME 1                                        /* 音量の指定（0～+100） */

void test_ev3_cychdr(intptr_t idx){
	static int count = 0;
	char buf[100];
	sprintf(buf, "EV3CYC %d count %d", idx, ++count);
	ev3_lcd_draw_string(buf, 0, 0);						// EV3のLCDに文字列 buf を表示
}

void RingTone(int freq, int time, int vol){              /* 音符を再生するユーザー関数を定義 */
	ev3_speaker_set_volume(vol);                         /* 音量設定（0～+100．0はミュート．100超えると+100になる．） */
	ev3_speaker_play_tone(freq, time);                   /* 音を鳴らす．周波数はHz，出力持続時間はミリ秒で指定． */
	tslp_tsk(time);                                      /* 指定時間待機 [us] */
}

void main_task(intptr_t unused) {
	
	sta_cyc(TEST_EV3_CYC1);								/* 周期ハンドラを開始する */

	RingTone(695, 14* TEMPO, VOLUME);  
	RingTone(695, 14* TEMPO, VOLUME);  
	RingTone(695, 14* TEMPO, VOLUME);  
	RingTone(929, 83* TEMPO, VOLUME);  
	RingTone(1401, 83* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1188, 14* TEMPO, VOLUME);  
	RingTone(1054, 14* TEMPO, VOLUME);  
	RingTone(1841, 83* TEMPO, VOLUME);  
	RingTone(1401, 41* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1188, 14* TEMPO, VOLUME);  
	RingTone(1054, 14* TEMPO, VOLUME);  
	RingTone(1841, 83* TEMPO, VOLUME);  
	RingTone(1401, 41* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1188, 14* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1054, 55* TEMPO, VOLUME);  
	tslp_tsk(280*3000);
	RingTone(695, 14* TEMPO, VOLUME);  
	RingTone(695, 14* TEMPO, VOLUME);  
	RingTone(695, 14* TEMPO, VOLUME);  
	RingTone(929, 83* TEMPO, VOLUME);  
	RingTone(1401, 83* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1188, 14* TEMPO, VOLUME);  
	RingTone(1054, 14* TEMPO, VOLUME);  
	RingTone(1841, 83* TEMPO, VOLUME);  
	RingTone(1401, 41* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1188, 14* TEMPO, VOLUME);  
	RingTone(1054, 14* TEMPO, VOLUME);  
	RingTone(1841, 83* TEMPO, VOLUME);  
	RingTone(1401, 41* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1188, 14* TEMPO, VOLUME);  
	RingTone(1251, 14* TEMPO, VOLUME);  
	RingTone(1054, 55* TEMPO, VOLUME);  
	
	ev3_lcd_draw_string("Star Wars Theme Terminated!", 0, 40);    /* 終了表示 */
	
	ext_tsk();                                              /* タスク終了処理 */
}
