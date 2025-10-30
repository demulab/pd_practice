
#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <multi_task1.h>
#include "kernel_cfg.h"

#include "spike/hub/battery.h"
#include "spike/hub/button.h"
#include "spike/hub/display.h"
#include "spike/hub/imu.h"
#include "spike/hub/light.h"
#include "spike/hub/speaker.h"
#include "spike/pup/colorsensor.h"
#include "spike/pup/forcesensor.h"
#include "spike/pup/motor.h"
#include "spike/pup/ultrasonicsensor.h"


pup_motor_t *motorA;             // モータAを使う変数
pup_motor_t *motorB;             // モータBを使う変数
pup_device_t *ColorSensor;       // カラーセンサーを使う変数
pup_device_t *ForceSensor;       // フォースセンサーを使う変数
pup_device_t *UltraSonicSensor;  // 距離センサーを使う変数

#define COUNT 10000		/* �J�E���g����10000�ɒ�` */
#define TIME_LOOP 1000000000

void main_task(intptr_t unused) {	
	int i,j,k;
	char buf[5];
		
	for(i=0 ; i<=COUNT ; i++){		/* �J�E���g�������J��Ԃ� */		
		syslog(LOG_NOTICE, "MAIN TASK= %d", i);	     

			tslp_tsk(5);
		
	}
	act_tsk(SUB_TASK);
	ext_tsk();					/* �����I�� */
}

void sub_task(intptr_t unused) {
	int i,j,k;
	char buf[5];
		
	for(i=0 ; i<=COUNT ; i++){		/* �J�E���g�������J��Ԃ� */		
		syslog(LOG_NOTICE, "SUB  TASK= %d", i);
        
			tslp_tsk(5);
	
	}

	ext_tsk();					/* �����I�� */
}
