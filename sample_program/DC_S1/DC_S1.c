#include <kernel.h>                  // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                  // exit() を使うため
#include <t_syslog.h>                // シリアルモニタにメッセージを出す
#include <DC_S1.h>
#include "spike/pup/ultrasonicsensor.h"  // 超音波センサーを使う

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動時のメッセージをシリアルモニタに出力
    syslog(LOG_NOTICE, "Program started.");

    // Eポートに接続された超音波センサーを取得
    // pup_device_t* はセンサーを操作するための変数
    pup_device_t *UltraSonicSensor = pup_ultrasonic_sensor_get_device(PBIO_PORT_ID_E);

    // ──────────────────────────────
    // 距離を測定して表示するループ
    // ──────────────────────────────
    while (1)
    {
        // 距離を取得（単位：ミリメートル）
        int32_t distance = pup_ultrasonic_sensor_distance(UltraSonicSensor);

        // シリアルモニタに距離を表示
        syslog(LOG_NOTICE, "Distance: %ld mm", distance);

        // 0.01秒（10ミリ秒）待つ（マイクロ秒単位）
        dly_tsk(10000);
    }

    // 実際にはここには到達しない（無限ループのため）
    exit(0);
}
