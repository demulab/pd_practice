#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "multi_display_speaker_B.h"

#include "spike/hub/display.h"   // Hub表示
#include "spike/hub/speaker.h"   // スピーカ（環境により header 名が異なる場合あり）

#define TEMPO   18          /* 基本の音長(相対) */
#define VOLUME  50          /* 音量 (0～100 程度) */

// 周期ハンドラ: 1秒ごとにカウントを表示
void test_spike_cychdr(intptr_t exinf)
{
    static int count = 0;
    
    hub_display_number(++count);   // 数字だけを表示（テキストが無ければ数字でOK）
}

// EV3 の RingTone 相当（freq[Hz], time[ms], 音量は固定VOLUME）
static inline void RingTone(int freq, int time_ms)
{
    hub_speaker_set_volume(VOLUME);          // 必要なら1回だけでもOK
    hub_speaker_play_tone(freq, time_ms);    // 周波数Hz, 長さms
    dly_tsk(time_ms * 1000);                 // [us]指定で待つ（音が鳴り終わるまで）
}

void main_task(intptr_t exinf)
{   

    const int32_t quarter = 250;
    const int32_t half    = 500;
    const int32_t full    = 1000;
    // 周期ハンドラ開始（app.cfg で TEST_SPIKE_CYC1 を定義）
    sta_cyc(TEST_SPIKE_CYC1);

    hub_speaker_set_volume(VOLUME);

    while (1) {
        // 音階を順番に鳴らす（依頼いただいた並び）
        hub_speaker_play_tone(NOTE_C4, full);        // ド
        hub_speaker_play_tone(NOTE_G4, full);        // ソ
        hub_speaker_play_tone(NOTE_F4, quarter);     // ファ
        hub_speaker_play_tone(NOTE_E4, quarter);     // ミ
        hub_speaker_play_tone(NOTE_D4, quarter);     // レ
        hub_speaker_play_tone(NOTE_C5, full);        // 高いド
        hub_speaker_play_tone(NOTE_G4, half);        // ソ
        hub_speaker_play_tone(NOTE_F4, quarter);     // ファ
        hub_speaker_play_tone(NOTE_E4, quarter);     // ミ
        hub_speaker_play_tone(NOTE_D4, quarter);     // レ
        hub_speaker_play_tone(NOTE_C5, full);        // 高いド
        hub_speaker_play_tone(NOTE_G4, half);        // ソ
        hub_speaker_play_tone(NOTE_F4, quarter);     // ファ
        hub_speaker_play_tone(NOTE_E4, quarter);     // ミ
        hub_speaker_play_tone(NOTE_F4, quarter);     // ファ
        hub_speaker_play_tone(NOTE_D4, full);        // レ

        // 小休止（ループ間の区切り）
        dly_tsk(300000); // 300ms
    }

    // 到達しないが、書式上の終了
    // ext_tsk();
}

// （任意）サブラベル：元コードに合わせて残す場合
// 表示は周期ハンドラに任せ、ここでは1秒周期で小さな処理を継続
void sub_task(intptr_t exinf)
{
    int cnt = 0;
    while (1) {
        // 周期ハンドラの表示と衝突させないため表示しない／もしくは軽い処理だけ
        // hub_display_number(1000 + (++cnt));
        (void)cnt;
        dly_tsk(1000 * 1000); // 1秒
    }
}
