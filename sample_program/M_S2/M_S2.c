#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // シリアルモニタにメッセージを出す
#include <M_S2.h>
#include "spike/pup/motor.h"     // PUPモータを使うためのヘッダ

// ──────────────────────────────
// Main関数（RTOSが最初に実行する関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    // 起動メッセージをシリアルモニタに表示
    syslog(LOG_NOTICE, "Motor test started.");

    // Aポートのモータを初期化（反時計回りを正方向として設定）
    pup_motor_t *motorA = pup_motor_init(PBIO_PORT_ID_A, PUP_DIRECTION_COUNTERCLOCKWISE);

    // ──────────────────────────────
    // モータを1秒ごとに順転→逆転→順転させる
    // ──────────────────────────────

    pup_motor_set_speed(motorA, 500);   // 正転（500度/秒）
    dly_tsk(1000000);                   // 1秒待つ

    pup_motor_set_speed(motorA, -500);  // 逆転（-500度/秒）
    dly_tsk(1000000);                   // 1秒待つ

    pup_motor_set_speed(motorA, 500);   // 再び正転
    dly_tsk(1000000);                   // 1秒待つ

    // モータを停止してプログラム終了
    pup_motor_brake(motorA);            // モータ停止（慣性で回転しない。すぐ止まる）
    exit(0);
}
