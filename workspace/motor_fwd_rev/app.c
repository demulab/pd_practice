#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	ev3_motor_config(EV3_PORT_A, LARGE_MOTOR);   /* PORT A�Ƀ��[�^�[L��ݒ� */
	ev3_motor_config(EV3_PORT_B, LARGE_MOTOR);   /* PORT B�Ƀ��[�^�[L��ݒ� */

	int count = 0;
	while (1) {
		if (count < 100) {
			ev3_motor_set_power(EV3_PORT_A, 10);
			ev3_motor_set_power(EV3_PORT_B, 10);
		}
		else if (count < 200) {
			ev3_motor_set_power(EV3_PORT_A,-10);
			ev3_motor_set_power(EV3_PORT_B,-10);
		}
		else if (count < 300) {
			ev3_motor_set_power(EV3_PORT_A, 0);
			ev3_motor_set_power(EV3_PORT_B, 0);	
		}
		else {
			break;
		}
		count++;
		tslp_tsk(100000);                        /* 100,000us���� 100ms*/
	}

	ev3_lcd_draw_string("Finished", 0, 30);
	tslp_tsk(1000000);                           /* 1000000us�ҋ@ */
	ext_tsk();                                   /* �^�X�N�I������ */
}