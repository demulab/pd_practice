#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // シリアルモニタにメッセージを出す
#include <M_S3.h>
#include "spike/pup/motor.h"     // PUPモータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行される関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに出力
    syslog(LOG_NOTICE, "Motor angle read started.");

    // Aポートのモータを初期化
    // 第2引数：回転方向（時計回り or 反時計回り）
    pup_motor_t *motorA = pup_motor_init(PBIO_PORT_ID_A, PUP_DIRECTION_COUNTERCLOCKWISE);

    // ──────────────────────────────
    // モータの角度（回転位置）を繰り返し取得して表示
    // ──────────────────────────────
    while (1)
    {
        // モータの回転角度を取得（単位：度）
        int32_t degree = pup_motor_get_count(motorA);

        // シリアルモニタに角度を出力
        syslog(LOG_NOTICE, "Angle: %ld deg", degree);

        // 0.1秒（100ミリ秒）待機して更新間隔を調整
        dly_tsk(100000);
    }

    // 実際にはここには到達しません（無限ループのため）
    exit(0);
}
