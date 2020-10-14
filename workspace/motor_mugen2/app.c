#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf) {
	uint64_t time;                             /* �V�X�e������ */
	int32_t left_angle, right_angle;
	uint32_t power = 10;                       /* ��]�X�s�[�h�i�p���[�j-100�`+100 */
	uint32_t count = 0;
	char left_angle_str[32];                   /* �p���[��\���p�̕����� */
	char right_angle_str[32];                  /* �p���[��\���p�̕����� */
	char time_str[32];                         /* �V�X�e�����Ԃ�\�����邽�߂̕����� */

	ev3_lcd_set_font(EV3_FONT_MEDIUM);         /* LCD�t�H���g�ݒ� */

	ev3_motor_config(EV3_PORT_A, LARGE_MOTOR); /* PORT A�Ƀ��[�^�[L��ݒ� */
	ev3_motor_config(EV3_PORT_B, LARGE_MOTOR); /* PORT B�Ƀ��[�^�[L��ݒ� */

	while (1) {
		get_tim(&time);                             /* ���݂̃V�X�e�����Ԃ��擾[usec] */
		if (count++ == 100) power = - power;
		ev3_motor_set_power(EV3_PORT_A, power);    /* �w�肵���p���[�ŉ�]���� */
		ev3_motor_set_power(EV3_PORT_B, power);    /* �w�肵���p���[�ŉ�]���� */
		left_angle  = ev3_motor_get_counts(EV3_PORT_A);
		right_angle = ev3_motor_get_counts(EV3_PORT_B);
		sprintf(time_str, "TIME: %ld", time);               /* �V�X�e�����Ԃ�\�����邽�߂̕�����쐬 */
		sprintf(left_angle_str,  "LEFT  ANGLE[deg]: %4ld", left_angle);  /* ��]�p�x��\�����邽�߂̕�����쐬 */
		sprintf(right_angle_str, "RIGHT ANGLE[deg]: %4ld", right_angle); /* ��]�p�x��\�����邽�߂̕�����쐬 */
		syslog(LOG_NOTICE, "Time=%ld[us]", time);
		syslog(LOG_NOTICE, "Angle[deg] L=%ld R=%ld", left_angle, right_angle);
		
		ev3_lcd_draw_string(time_str,  0, 10);                /* �V�X�e�����Ԃ�\�� */
		tslp_tsk(10000);                                      /* �V�~�����[�^LCD�p�̃X���[�v */
		ev3_lcd_draw_string(left_angle_str,  0, 30);          /* ��]�p�x�̒l��\�� */
		tslp_tsk(10000);                                      /* �V�~�����[�^LCD�p�̃X���[�v */
		ev3_lcd_draw_string(right_angle_str, 0, 50);          /* ��]�p�x�̒l��\�� */
		tslp_tsk(80000);                                      /* 80,000us �X���[�v */


	}
		
	ext_tsk();                                 /* �^�X�N�I������ */
}
	