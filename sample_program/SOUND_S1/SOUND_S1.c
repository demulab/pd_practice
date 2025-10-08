#include <kernel.h>              // RTOSの基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // ログ出力
#include <SOUND_S1.h>
#include "spike/hub/display.h"   // ディスプレイ表示
#include "spike/hub/speaker.h"   // 音を鳴らす機能
#include "spike/hub/battery.h"   // バッテリー情報

// ──────────────────────────────
// 音を鳴らす関数
// ──────────────────────────────
void play_sound() {
    int32_t duration = 500;  // 音の長さ（ミリ秒）
    hub_speaker_play_tone(NOTE_C4, duration);  // ドの音を再生
}

// ──────────────────────────────
// Main関数（RTOSが最初に動かす関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに出力
    syslog(LOG_NOTICE, "Program started.");

    // 音量を100%に設定
    hub_speaker_set_volume(100);

    // バッテリー電圧を取得して画面に表示
    uint16_t battery = hub_battery_get_voltage();
    hub_display_number(battery);  // 数値をハブのLEDマトリクスに表示

    // 音を鳴らす
    play_sound();

    // 3秒待つ（マイクロ秒単位）
    dly_tsk(3000000);

    // プログラムを終了
    exit(0);
}
