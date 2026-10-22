// TS_S3.c 力センサのサンプルプログラム 2026-10-22
#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにログを出す
#include <TS_S3.h>
#include "spike/pup/forcesensor.h" // フォースセンサーを使う

// 押す力を mN 単位で返す（例：3.14 N → 3140）
static int32_t force_sensor_mN(pup_device_t *pdev)
{
    // 校正値（static なので、関数を抜けても値が残る）
    static bool    calibrated = false;  // 校正値をもう読んだか
    static int32_t raw_offset;          // オフセット
    static int32_t raw_released;        // ボタンを離しているときの値
    static int32_t raw_end;             // いっぱいまで押したときの値

    // 最初の1回だけ、センサーから校正値を読み込む
    if (!calibrated) {
        int32_t calib[8];
        pup_device_get_values(pdev, PBIO_IODEV_MODE_PUP_FORCE_SENSOR__CALIB, calib);
        raw_offset   = calib[1];
        raw_released = calib[2];
        raw_end      = calib[6];
        calibrated   = true;
    }

    // 生の値を読んで mN に変換（ライブラリ内部と同じ計算）
    int32_t raw;
    pup_device_get_values(pdev, PBIO_IODEV_MODE_PUP_FORCE_SENSOR__FRAW, &raw);
    int32_t mN = 10000 * (raw - raw_released - raw_offset) / (raw_end - raw_released);
    return (mN < 0) ? 0 : mN;
}

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
        float force = force_sensor_mN(ForceSensor);

        // syslog は小数（%f）を表示できないので、100倍して整数にする
        int32_t f100 = (force_sensor_mN(ForceSensor) + 5) / 10;   // 0.01 N 単位に四捨五入
        
        // 「整数部 . 小数部2桁」に分けて表示（%02d で 0.05 の「0」も表示される）
        syslog(LOG_NOTICE, "Force: %d.%02d [N]", f100 / 100, f100 % 100);   

        // 0.05秒（50ミリ秒）待機して更新を繰り返す
        dly_tsk(50000);
    }

    // 実際には到達しない（無限ループのため）
    exit(0);
}
