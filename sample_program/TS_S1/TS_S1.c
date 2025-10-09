#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにメッセージを出す
#include <TS_S1.h>
#include "spike/hub/display.h"     // ハブのLEDマトリクス表示
#include "spike/pup/forcesensor.h" // フォースセンサー（押す強さを検出）

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動時にメッセージをシリアルモニタに出力（デバッグ用）
    syslog(LOG_NOTICE, "Program started.");

    // ──────────────────────────────
    // フォースセンサーを使うための変数を宣言
    // pup_device_t は「センサーやモータなどの装置（デバイス）」を表す型です。
    // *（アスタリスク）は「ポインタ」と呼ばれ、実際のセンサーを直接持たず、
    // その“場所（アドレス）”を指す。    
    // つまり、ForceSensor は「Dポートに接続されたフォースセンサーを操作するためのリモコン」
    // のようなもの。
    // ──────────────────────────────
    pup_device_t *ForceSensor;

    // Dポートに接続されたフォースセンサーを取得
    ForceSensor = pup_force_sensor_get_device(PBIO_PORT_ID_D);

    // ──────────────────────────────
    // センサーが押されるまで待機するループ
    // pup_force_sensor_touched() は「センサーが押されたら true（1）」を返す。
    // 押されていない間は 0（false）なので、while内で待ち続ける。
    // ──────────────────────────────
    while (!pup_force_sensor_touched(ForceSensor)) {
        dly_tsk(100000);  // 0.1秒待つ（CPUを休ませる）
    }

    // センサーが押されたらメッセージを表示
    hub_display_text("Pressed!", 200, 200);　// x=200, y=200 は表示位置

    // プログラムを終了
    exit(0);
}
