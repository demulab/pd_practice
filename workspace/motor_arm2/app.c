#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	int32_t arm_angle;
	uint32_t power = 1;                      /* ��]�X�s�[�h�i�p���[�j-100�`+100 */
	uint32_t count = 0;
	char angle_str[32];                      /* �p�x�\���p�̕����� */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);         /* LCD�t�H���g�ݒ� */

	ev3_motor_config(EV3_PORT_C, MEDIUM_MOTOR); /* PORT C�Ƀ��[�^ M��ݒ� */

	while (1) {
		if (count++ == 30) power = - power;
		ev3_motor_set_power(EV3_PORT_C, power);    /* �w�肵���p���[�ŉ�]���� */
		arm_angle = ev3_motor_get_counts(EV3_PORT_C);
		syslog(LOG_NOTICE, "ARM ANGLE[deg]: %4ld", arm_angle);
		sprintf(angle_str, "ARM ANGLE[deg]: %4ld", arm_angle);  /* ��]�p�x��\�����邽�߂̕�����쐬 */		
		ev3_lcd_draw_string(angle_str,  0, 50);              /* ��]�p�x�̒l��\�� */
		//tslp_tsk(100000);                                    /*  100,000us ���݂œ��� */
		tslp_tsk(100000);                                    /*  100,000us ���݂œ��� */
	}
		
	ext_tsk();                                 /* �^�X�N�I������ */
}
	