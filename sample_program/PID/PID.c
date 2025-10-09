// このプログラムはPIDを実装していない
#include <kernel.h>      // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>      // exit() を使うため
#include <t_syslog.h>    // シリアルモニタにメッセージを出す
#include <PID.h>

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    uint64_t count = 0;  // カウンタ変数

    // 起動メッセージをシリアルモニタに出力
    syslog(LOG_NOTICE, "Program started.");

    // ──────────────────────────────
    // 1秒ごとにカウントを表示するループ
    // ──────────────────────────────
    while (1)
    {
        dly_tsk(1000000);  // 1秒待つ（単位はマイクロ秒）
        syslog(LOG_NOTICE, "count: %ld", count);  // 現在のカウントを表示
        count++;  // カウントを1増やす
    }

    // 実際にはここには到達しません（無限ループのため）
    exit(0);
}
