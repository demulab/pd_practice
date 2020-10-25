#include "ev3api.h"
#include "app.h"

#define TEMPO 18                                        /* ��{�̉����o�͎������Ԃ̎w�� */
#define VOLUME 1                                        /* ���ʂ̎w��i0�`+100�j */

void test_ev3_cychdr(intptr_t idx){
	static int count = 0;
	char buf[100];
	sprintf(buf, "EV3CYC %d count %d", idx, ++count);
	ev3_lcd_draw_string(buf, 0, 0);						// EV3��LCD�ɕ����� buf ��\��
}

void RingTone(int freq, int time, int vol){              /* �������Đ����郆�[�U�[�֐����` */
	ev3_speaker_set_volume(vol);                         /* ���ʐݒ�i0�`+100�D0�̓~���[�g�D100�������+100�ɂȂ�D�j */
	ev3_speaker_play_tone(freq, time);                   /* ����炷�D���g����Hz�C�o�͎������Ԃ̓~���b�Ŏw��D */
	tslp_tsk(time);                                      /* �w�莞�ԑҋ@ [us] */
}

void main_task(intptr_t unused) {
	
	sta_cyc(TEST_EV3_CYC1);								/* �����n���h�����J�n���� */

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
	
	ev3_lcd_draw_string("Star Wars Theme Terminated!", 0, 40);    /* �I���\�� */
	
	ext_tsk();                                              /* �^�X�N�I������ */
}
