// M_S5.c  モータサンプルプログラム5  2026-10-22
#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <M_S5.h>
#include "spike/pup/motor.h"     // モータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行される） 　
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
