#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	int angle = 300;                           /* ��]�p�x�̒l[deg] */
	uint32_t power = 100;                      /* �p���[�@0�`+100 */
	char angle_str[32];                       /* ��]�p�x��\�����邽�߂̕����� */
	char power_str[32];                       /* �p���[��\�����邽�߂̕����� */

	sprintf(angle_str, "ANGLE: %d", angle);   /* ��]�p�x��\�����邽�߂̕�����쐬 */
	sprintf(power_str, "POWER: %d", power);   /* �p���[��\�����邽�߂̕�����쐬 */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);        /* LCD�t�H���g�ݒ� */
	ev3_lcd_draw_string(angle_str, 0, 10);    /* ��]�p�x�̒l��\�� */
	tslp_tsk(10000);                          /* 10,000us���� */
	ev3_lcd_draw_string(power_str, 0, 30);    /* �p���[�̒l��\�� */
	tslp_tsk(10000);                          /* 10,000us���� */

	ev3_motor_config(EV3_PORT_C, MEDIUM_MOTOR); /* PORT C�Ƀ��[�^M��ݒ� */
	ev3_motor_reset_counts(EV3_PORT_C);         /* PORT C�̃��[�^�̊p�ʒu���[���Ƀ��Z�b�g */

	//ev3_motor_rotate(EV3_PORT_C, angle, power, false); /* �w�肵����]�p�x�A��]�X�s�[�h�i�p���[�j�ŉ�]���� */
                      
	ev3_motor_set_power(EV3_PORT_C, 10);
	tslp_tsk(5000000);                        /* 3,000,000[us]=3[s]���� */

	//ev3_motor_rotate(EV3_PORT_C, -angle, power, false); /* �w�肵����]�p�x�A��]�X�s�[�h�i�p���[�j�ŉ�]���� */
 	ev3_motor_set_power(EV3_PORT_C, -10);
 	tslp_tsk(5000000);                        /* 3,000,000[us]=3[s]���� */

	ev3_motor_stop(EV3_PORT_C, true);         /* ���[�^�̒�~ */
	                                  /* �u���[�L���[�h�̎w�� true: �u���[�L���[�h  false: �t���[�g���[�h */
	tslp_tsk(1000000);                        /* 1,000,000us�ҋ@ */

	ext_tsk();                                /* �^�X�N�I������ */
}
