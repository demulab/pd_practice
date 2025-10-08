#include <kernel.h>          // RTOSの基本機能
#include <stdlib.h>          // exit() を使うため
#include <t_syslog.h>        // ログ出力
#include <LCD_S2.h>
#include "spike/hub/display.h"  // ディスプレイ表示


// ──────────────────────────────
// メインタスク（RTOSが最初に動かす関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    int count = 0;  // 表示する数字

    // プログラム開始メッセージを出力（PCのシリアルモニタに表示される）
    syslog(LOG_NOTICE, "Program started.");

    // ──────────────────────────────
    // 1秒ごとに数値をカウントアップして表示
    // ──────────────────────────────
    while (1)
    {
        hub_display_number(count);   // 数字をSPIKEハブの画面に表示
        dly_tsk(1000000);            // 1秒待つ（マイクロ秒単位）
        count++;                     // 数字を1増やす
    }

    // 実際にはここには来ません（無限ループのため）
    exit(0);
}
