#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにメッセージを出す
#include <CS_S1.h>
#include "spike/pup/colorsensor.h" // カラーセンサーを使う

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに表示
    syslog(LOG_NOTICE, "Program started.");

    // Dポートに接続されたカラーセンサーを取得
    // pup_device_t* はセンサーを操作するための変数
    pup_device_t *ColorSensor = pup_color_sensor_get_device(PBIO_PORT_ID_D);

    // ──────────────────────────────
    // 反射光の強さ（明るさ）を読み取って表示するループ
    // ──────────────────────────────
    while (1)
    {
        // 反射光の明度を取得（0〜100 の範囲）
        int32_t reflection = pup_color_sensor_reflection(ColorSensor);

        // シリアルモニタに表示
        syslog(LOG_NOTICE, "Reflection: %ld", reflection);

        // 0.5秒待つ（マイクロ秒単位）
        dly_tsk(500000);
    }

    // 実際にはここには到達しない（無限ループのため）
    exit(0);
}
