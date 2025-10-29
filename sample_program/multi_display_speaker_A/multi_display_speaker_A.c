#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "multi_display_speaker_A.h"

#include "spike/hub/display.h"   // 5x5表示
#include "spike/hub/speaker.h"   // サウンド

#define TEMPO   18   /* 音符の相対長 (ms 相当) */
#define VOLUME  50   /* 0～100 程度 */

static inline void RingTone(int freq, int time_ms)
{
    // 音はハード側が再生、ここではインターバルを us で待つ
    hub_speaker_set_volume(VOLUME);
    hub_speaker_play_tone(freq, time_ms);
    dly_tsk(time_ms * 1000);   // [us]
}

/* ===== LCD カウント専用タスク ===== */
void lcd_task(intptr_t exinf)
{
    int count = 0;
    for(;;){
        hub_display_number(++count);   // 1秒ごとにインクリメント表示
        dly_tsk(1000000);              // 1,000,000us = 1s
    }
}

/* ===== サウンド専用タスク ===== */
void sound_task(intptr_t exinf)
{
    const int32_t quarter = 250;
    const int32_t half    = 500;
    const int32_t full    = 1000;

    hub_speaker_set_volume(VOLUME);

    for (;;) {
        // 音階を順番に鳴らす（依頼いただいた並び）
        hub_speaker_play_tone(NOTE_C4, full);       // ド
        hub_speaker_play_tone(NOTE_G4, full);       // ソ
        hub_speaker_play_tone(NOTE_F4, quarter);    // ファ
        hub_speaker_play_tone(NOTE_E4, quarter);    // ミ
        hub_speaker_play_tone(NOTE_D4, quarter);    // レ
        hub_speaker_play_tone(NOTE_C5, full);       // 高いド
        hub_speaker_play_tone(NOTE_G4, half);       // ソ
        hub_speaker_play_tone(NOTE_F4, quarter);    // ファ
        hub_speaker_play_tone(NOTE_E4, quarter);    // ミ
        hub_speaker_play_tone(NOTE_D4, quarter);    // レ
        hub_speaker_play_tone(NOTE_C5, full);       // 高いド
        hub_speaker_play_tone(NOTE_G4, half);       // ソ
        hub_speaker_play_tone(NOTE_F4, quarter);    // ファ
        hub_speaker_play_tone(NOTE_E4, quarter);    // ミ
        hub_speaker_play_tone(NOTE_F4, quarter);    // ファ
        hub_speaker_play_tone(NOTE_D4, full);       // レ

        // 小休止（ループ間の区切り）
        dly_tsk(300000); // 300ms
    }
}

/* ===== 起動タスク：2タスクを起動して寝るだけ ===== */
void main_task(intptr_t exinf)
{
    act_tsk(LCD_TASK);
    act_tsk(SOUND_TASK);
    slp_tsk();   
}

