#include "ev3api.h"
#include "app.h"

#define TEMPO 25                                            /* 基本の音声出力持続時間の指定 */
#define VOLUME 1                                            /* 音量の指定（0～+100） */


#define TOUCH_PORT EV3_PORT_1
#define COLOR_SENSOR_PORT  EV3_PORT_2
#define left_motor EV3_PORT_A
#define right_motor EV3_PORT_B

static int reflection = 0;
static int button = 0;
static int steer2 = 0;



void ev3_cyc1(intptr_t idx){
	char reflect_str[32];
	char buf2[32];
	reflection = ev3_color_sensor_get_reflect(COLOR_SENSOR_PORT); /* 反射光の強さを取得 */
	sprintf(reflect_str, "REF: %3d", reflection);
	ev3_lcd_draw_string(reflect_str, 0, 0);            /* 反射光の強さの値を表示 */
}

void ev3_cyc2(intptr_t idx){
//	char steer_str2[32];
	ev3_motor_steer(left_motor, right_motor, 12, -steer2);		/*Left:white, Right:black*/
//	sprintf(steer_str2, "st2: %3d", steer2);
//  	ev3_lcd_draw_string(steer_str2, 0, 40);            /* 反射光の強さの値を表示 */
}

void ev3_cyc3(intptr_t idx){
	char steer_str2[32];
//	ev3_motor_steer(left_motor, right_motor, 12, -steer2);		/*Left:white, Right:black*/
	sprintf(steer_str2, "st2: %3d", steer2);
  	ev3_lcd_draw_string(steer_str2, 0, 40);            /* 反射光の強さの値を表示 */
}

void ev3_cyc4(intptr_t idx){
	char touch_str[32];
	button=ev3_touch_sensor_is_pressed(TOUCH_PORT);
	tslp_tsk(1000);                                      /* 指定時間待機 [us] */
	sprintf(touch_str, "SW: %3d", button);
  	ev3_lcd_draw_string(touch_str, 0, 60);            /* 反射光の強さの値を表示 */
}

void RingTone(int freq, int time, int vol){              /* 音符を再生するユーザー関数を定義 */
	ev3_speaker_set_volume(vol);                         /* 音量設定（0～+100．0はミュート．100超えると+100になる．） */
	ev3_speaker_play_tone(freq, time);                   /* 音を鳴らす．周波数はHz，出力持続時間はミリ秒で指定． */
	tslp_tsk(time);                                      /* 指定時間待機 [us] */
}

void main_task(intptr_t unused) {
	
	ev3_lcd_set_font(EV3_FONT_MEDIUM);	

	char buf0[100];

	int32_t powerM = 1;                      /* 回転スピード（パワー）-100～+100 */

	uint8_t reflect;                                        /* 反射光の強さの値 */
	char anlge_str[32];                                   
	char steer_str1[32];                                   

	int motorM_flag = 0;
	uint32_t count = 20;

	int white = 100;
	int black = 20;

	// PID Gain
	float kp = 0.6;
	float ki = 0.0;
	float kd = 0.0;
		
	float delta_T = 0.01; 									/* 10ms */

	ev3_sensor_config(TOUCH_PORT, TOUCH_SENSOR);            /* PORT1 にタッチセンサを設定 */
	ev3_sensor_config(COLOR_SENSOR_PORT, COLOR_SENSOR);     /* PORT2 にカラーセンサを設定 */
	
	ev3_motor_config(left_motor, LARGE_MOTOR); 				/* PORT A にモータLを設定 */
	ev3_motor_config(right_motor, LARGE_MOTOR); 			/* PORT B にモータLを設定 */
	ev3_motor_config(EV3_PORT_C, MEDIUM_MOTOR); 			/* PORT C にモータMを設定 */

    float lasterror = 0.0, integral = 0.0;
	float midpoint = (white + black) / 2; 
	float error = 0.0;

	RingTone(695, 2* TEMPO, VOLUME);  /* debug */
	tslp_tsk(1000);

	sta_cyc(CYC_HDLR1);								/* 周期ハンドラを開始する */
	sta_cyc(CYC_HDLR2);								/* 周期ハンドラを開始する */
	sta_cyc(CYC_HDLR3);								/* 周期ハンドラを開始する */
	sta_cyc(CYC_HDLR4);								/* 周期ハンドラを開始する */


	RingTone(695, 2* TEMPO, VOLUME);  /* debug */
	tslp_tsk(1000);

    while(!button) {
  	    //reflection = ev3_color_sensor_get_reflect(COLOR_SENSOR_PORT); /* 反射光の強さを取得 */
        error = midpoint - reflection;	/*  e = qd - q  */

        integral = integral + (error + lasterror) / 2 * delta_T;
        float steer1 = kp * error + ki * integral + kd * (error - lasterror)/delta_T;
        steer2 = kp * error + ki * integral + kd * (error - lasterror)/delta_T;

		lasterror = error;

	  	sprintf(steer_str1, "st1: %5.2f", steer1);
  		ev3_lcd_draw_string(steer_str1, 0, 20);            /* 反射光の強さの値を表示 */

		tslp_tsk(4000);											 /* 4ms */

	}


	RingTone(695, 2* TEMPO, VOLUME);  /* debug */
	tslp_tsk(1000);

	stp_cyc(CYC_HDLR1);								/* 周期ハンドラを停止する */
	stp_cyc(CYC_HDLR2);								/* 周期ハンドラを停止する */
	stp_cyc(CYC_HDLR3);								/* 周期ハンドラを停止する */
	stp_cyc(CYC_HDLR4);								/* 周期ハンドラを停止する */

	ev3_motor_stop(left_motor, true);
	tslp_tsk(100000);
	ev3_motor_stop(right_motor, true);
	tslp_tsk(100000);

	RingTone(695, 2* TEMPO, VOLUME);  /* debug */
	tslp_tsk(1000);


	ext_tsk();                                              /* タスク終了処理 */
}
