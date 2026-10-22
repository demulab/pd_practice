#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <M_S4.h>
#include "spike/pup/motor.h"     // PUPモータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // A, Bポートのモータを取得（変更１）
    pup_motor_t *motorA = pup_motor_get_device(PBIO_PORT_ID_A);
    pup_motor_t *motorB = pup_motor_get_device(PBIO_PORT_ID_B);    
    
    // A, Bポートのモータを初期化（変更２）
    // 第2引数：回転方向（PUP_DIRECTION_CLOCKWISE または COUNTERCLOCKWISE） 
    // 第3引数：リセット。trueで角度を0にする。
    pbio_error_t errA = pup_motor_setup(motorA, PUP_DIRECTION_COUNTERCLOCKWISE, true);
    pbio_error_t errB = pup_motor_setup(motorB, PUP_DIRECTION_CLOCKWISE, true);

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
