#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにログを出す
#include <TS_S3.h>
#include "spike/pup/forcesensor.h" // フォースセンサーを使う

// ──────────────────────────────
// Main関数（RTOSが最初に実行する）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに出力
    syslog(LOG_NOTICE, "Program started.");

    // Dポートのフォースセンサーを取得
    // pup_device_t* は「センサーを操作するための変数）」
    pup_device_t *ForceSensor = pup_force_sensor_get_device(PBIO_PORT_ID_D);

    // ──────────────────────────────
    // フォースセンサーの値を読み取って表示し続けるループ
    // ──────────────────────────────
    while (1)
    {  
        // 押す力を取得（単位：ニュートン[N]）
        float force = pup_force_sensor_force(ForceSensor);

        // シリアルモニタに小数点以下2桁まで出力
        syslog(LOG_NOTICE, "Force: %.2f [N]", force);

        // 0.05秒（50ミリ秒）待機して更新を繰り返す
        dly_tsk(50000);
    }

    // 実際には到達しない（無限ループのため）
    exit(0);
}
