#include "ev3api.h"
#include "app.h"

void main_task(intptr_t exinf)
{
	int count;
	char str[32];					   /* �J�E���g��\�����邽�߂̕����� */
	ev3_lcd_set_font(EV3_FONT_MEDIUM); /* LCD�ɕ\������t�H���g�̐ݒ� */

	while (1)
	{
		sprintf(str, "COUNT:%d", count); /* �J�E���g��\���p�̕�����쐬 */
		ev3_lcd_draw_string(str, 30, 60); /* �w�肵���ʒu�ɃJ�E���g��\�� */
		tslp_tsk(10000);				 //�@�V�~�����[�V�����̂ݕK�v 10,000us); 

		ev3_lcd_fill_rect(10, 10, 100, 20, EV3_LCD_BLACK); /* �w�肵���ʒu�ɋ�`�\�� */
		tslp_tsk(10000);				 //�@�V�~�����[�V�����̂ݕK�v 10,000us); 
		/* 100000us(1000ms) ���݂Ŏ��s */ 
		count++; 
	}
	
	/* LCD��ʑS�̂𔒂��h��ׂ��i�N���A����j*/ 
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE); 
	tslp_tsk(5000000);
	ext_tsk();						 /* �^�X�N�I������ */
}