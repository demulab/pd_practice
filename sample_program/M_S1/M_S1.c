#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // シリアルモニタにメッセージを出す
#include <M_S1.h>
#include "spike/pup/motor.h"     // PUPモータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに出力
    syslog(LOG_NOTICE, "Program started.");

    // Aポートのモータを初期化
    // 第2引数：回転方向（PUP_DIRECTION_CLOCKWISE または COUNTERCLOCKWISE）
    pup_motor_t *motorA = pup_motor_setup(PBIO_PORT_ID_A, PUP_DIRECTION_COUNTERCLOCKWISE);

    // ──────────────────────────────
    // モータを一定速度で回転させるループ
    // ──────────────────────────────
    while (1)
    {
        // 回転速度を設定（単位：度/秒）
        pup_motor_set_speed(motorA, 500);
    }

    // 実際にはここには到達しない（無限ループのため）
    exit(0);
}
