#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <pbio/color.h>            // 色に関する定義
#include <spike/hub/system.h>      // SPIKEハブのシステム制御
#include <stdio.h>                 // 標準入出力
#include <stdlib.h>                // 標準ライブラリ（exitなど）
#include <t_syslog.h>              // システムログ出力
#include <LCD_S1.h>                // ディスプレイ表示関連

// SPIKEハブの機能を使うためのヘッダ
#include "spike/hub/battery.h"
#include "spike/hub/button.h"
#include "spike/hub/display.h"
#include "spike/hub/imu.h"
#include "spike/hub/light.h"
#include "spike/hub/speaker.h"

// SPIKEのポートに接続するセンサやモータを使うためのヘッダ
#include "spike/pup/colorsensor.h"
#include "spike/pup/forcesensor.h"
#include "spike/pup/motor.h"
#include "spike/pup/ultrasonicsensor.h"

// ──────────────────────────────
// センサやモータを使うための変数
// ──────────────────────────────
// ※ SPIKEでは、センサやモータを使うときに
//   「どのポートに何がつながっているか」を
//   変数（ハンドル）で覚えておく必要があります。

pup_motor_t *motorA;          // Aポートのモータ
pup_motor_t *motorB;          // Bポートのモータ
pup_device_t *ColorSensor;    // カラーセンサ
pup_device_t *ForceSensor;    // 力（押す強さ）センサ
pup_device_t *UltraSonicSensor; // 距離センサ（超音波）

// ──────────────────────────────
// メインタスク（RTOSが最初に動かす関数）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    uint64_t count = 0;  // カウンタ（今は使っていません）

    // システムログにメッセージを出力（デバッグ用）
    syslog(LOG_NOTICE, "Sample program started.", 0);

    // 3秒間待つ（単位はマイクロ秒）
    dly_tsk(3000000);

    // ハブの画面に文字を表示（x=200, y=200）
    hub_display_text("hello, world", 200, 200);

    // プログラムを終了
    exit(0);
}
