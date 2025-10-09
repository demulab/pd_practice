#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <M_S4.h>
#include "spike/pup/motor.h"     // PUPモータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // AポートとBポートのモータを初期化
    // 回転方向は、Aは反時計回り、Bは時計回りに設定
    pup_motor_t *motorA = pup_motor_init(PBIO_PORT_ID_A, PUP_DIRECTION_COUNTERCLOCKWISE);
    pup_motor_t *motorB = pup_motor_init(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

    // ──────────────────────────────
    // 2つのモータを同時に回転させるループ
    // ──────────────────────────────
    while (1)
    {
        // AモータとBモータを同時に回転（500度/秒）
        pup_motor_set_speed(motorA, 500);
        pup_motor_set_speed(motorB, 500);
    }

    exit(0);
}
