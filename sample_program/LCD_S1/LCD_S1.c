#include <kernel.h>           // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>           // exit() を使うため
#include <t_syslog.h>         // システムログ出力
#include <LCD_S1.h>           // ディスプレイ表示関連
#include "spike/hub/display.h"  // ハブの画面表示

// ──────────────────────────────
// Main関数（RTOSが最初に動かす関数）
// ※普通のC言語の main() とは異なり、RTOSが呼び出します。
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // シリアルモニタにメッセージを送る
    // → SPIKEをPCにUSB接続し、TeraTermなどで確認できます。
    syslog(LOG_NOTICE, "Program started.");

    // 3秒待機（単位はマイクロ秒）
    dly_tsk(3000000);

    // ハブのLEDマトリクスに文字を表示
    hub_display_text("hello, world", 200, 200);

    // プログラムを終了
    // SPIKE-RTでは return 0 ではなく exit(0) を使います。
    exit(0);
}
