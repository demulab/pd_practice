#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	uint32_t power = 100;                      /* ��]�X�s�[�h�i�p���[�j-100�`+100 */
	char power_str[32];                        /* �p���[��\���p�̕����� */

	sprintf(power_str, "POWER: %d", power);   /* �p���[��\���p�̕�����쐬 */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);         /* LCD�t�H���g�ݒ� */
	ev3_lcd_draw_string(power_str, 0, 30);     /* �p���[�̒l��\�� */

	ev3_motor_config(EV3_PORT_A, LARGE_MOTOR); /* PORT A�Ƀ��[�^�[L��ݒ� */
	ev3_motor_config(EV3_PORT_B, LARGE_MOTOR); /* PORT B�Ƀ��[�^�[L��ݒ� */

	ev3_motor_set_power(EV3_PORT_A, power);    /* �w�肵���p���[�ŉ�]���� */
	ev3_motor_set_power(EV3_PORT_B, power);    /* �w�肵���p���[�ŉ�]���� */
	
	ext_tsk();                                 /* �^�X�N�I������ */
}
	