#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにメッセージを出す
#include <TS_S2.h>
#include "spike/hub/display.h"     // ハブのLEDマトリクス表示
#include "spike/pup/forcesensor.h" // フォースセンサーを使う

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに出力（デバッグ用）
    syslog(LOG_NOTICE, "Program started.");

    // Dポートに接続されたフォースセンサーを取得
    // pup_device_t はセンサーを操作するための変数型
    pup_device_t *ForceSensor = pup_force_sensor_get_device(PBIO_PORT_ID_D);

    // ──────────────────────────────
    // 押す力を読み取って表示するループ
    // ──────────────────────────────
    while (1)
    {
        // 押す力を取得（単位：ニュートン[N]）
        float force = pup_force_sensor_force(ForceSensor);

        // 押す力をハブのLEDマトリクスに表示
        // 小数点以下は切り捨てられる
        hub_display_number((int)force);

        // 0.05秒（50ミリ秒）待機
        dly_tsk(50000);
    }

    // 実際にはここには到達しない（無限ループのため）
    exit(0);
}
