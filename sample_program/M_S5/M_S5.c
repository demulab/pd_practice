#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <M_S5.h>
#include "spike/pup/motor.h"     // モータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行される） 
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // AポートとBポートのモータを初期化
    // Aは反時計回り、Bは時計回りを正方向に設定
    pup_motor_t *motorA = pup_motor_setup(PBIO_PORT_ID_A, PUP_DIRECTION_COUNTERCLOCKWISE);
    pup_motor_t *motorB = pup_motor_setup(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

    // 1秒待ってからスタート
    dly_tsk(1000000);

    // モータA・Bを同時に500度/秒で回転
    pup_motor_set_speed(motorA, 500);
    pup_motor_set_speed(motorB, 500);
    dly_tsk(1000000);  // 1秒間回転

    // モータA・Bを停止
    pup_motor_stop(motorA);
    pup_motor_stop(motorB);
    dly_tsk(850000);  // 0.85秒待機

    // モータAだけ再び回転
    pup_motor_set_speed(motorA, 500);
    dly_tsk(1000000);  // 1秒間回転

    // すべてのモータを停止して終了
    pup_motor_stop(motorA);
    pup_motor_stop(motorB);

    exit(0);
}
