#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにメッセージを出す
#include <CS_S2.h>
#include "spike/pup/colorsensor.h" // カラーセンサーを使う

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに表示
    syslog(LOG_NOTICE, "Program started.");

    // Dポートに接続されたカラーセンサーを取得
    // pup_device_t* センサーを操作するための変数
    pup_device_t *ColorSensor = pup_color_sensor_get_device(PBIO_PORT_ID_D);

    // ──────────────────────────────
    // カラーセンサーが認識した色を定期的に表示
    // ──────────────────────────────
    while (1)
    {
        // 1秒待つ（マイクロ秒単位）
        dly_tsk(1000000);

        // 認識した色の名前を1文字で取得（例：'R'、'G'、'B'など）
        char color = pup_color_sensor_color_name(ColorSensor, true);

        // シリアルモニタに色を表示
        syslog(LOG_NOTICE, "Color: %c", color);
    }

    // 実際にはここには到達しない（無限ループのため）
    exit(0);
}
