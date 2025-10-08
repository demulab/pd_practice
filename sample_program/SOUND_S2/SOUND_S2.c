#include <kernel.h>              // RTOSの基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // シリアルモニタにメッセージを出す
#include <SOUND_S2.h>
#include "spike/hub/display.h"   // 画面表示
#include "spike/hub/speaker.h"   // スピーカー制御
#include "spike/hub/battery.h"   // バッテリー情報

// ──────────────────────────────
// 音を鳴らす関数
// ──────────────────────────────
void play_sound() {
    // 音の長さ（単位：ミリ秒）
    int32_t quarter = 250;
    int32_t half    = 500;
    int32_t full    = 1000;

    // 音階を順番に鳴らす（ド・ソ・ファ・ミ・レ・ド など）
    hub_speaker_play_tone(NOTE_C4, full);    // ド
    hub_speaker_play_tone(NOTE_G4, full);    // ソ
    hub_speaker_play_tone(NOTE_F4, quarter); // ファ
    hub_speaker_play_tone(NOTE_E4, quarter); // ミ
    hub_speaker_play_tone(NOTE_D4, quarter); // レ
    hub_speaker_play_tone(NOTE_C5, full);    // 高いド
    hub_speaker_play_tone(NOTE_G4, half);    // ソ
    hub_speaker_play_tone(NOTE_F4, quarter); // ファ
    hub_speaker_play_tone(NOTE_E4, quarter); // ミ
    hub_speaker_play_tone(NOTE_D4, quarter); // レ
    hub_speaker_play_tone(NOTE_C5, full);    // 高いド
    hub_speaker_play_tone(NOTE_G4, half);    // ソ
    hub_speaker_play_tone(NOTE_F4, quarter); // ファ
    hub_speaker_play_tone(NOTE_E4, quarter); // ミ
    hub_speaker_play_tone(NOTE_F4, quarter); // ファ
    hub_speaker_play_tone(NOTE_D4, full);    // レ
}

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動時のメッセージをシリアルモニタに送信
    syslog(LOG_NOTICE, "Program started.");

    // スピーカーの音量を100%に設定
    hub_speaker_set_volume(100);

    // バッテリー電圧を取得してハブの画面に表示
    uint16_t battery = hub_battery_get_voltage();
    hub_display_number(battery);

    // メロディを再生
    play_sound();

    // 3秒待機（単位：マイクロ秒）
    dly_tsk(3000000);

    // プログラムを終了
    exit(0);
}

