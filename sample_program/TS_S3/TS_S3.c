// TS_S3.c 力センサのサンプルプログラム 2026-10-22
#include <kernel.h>                // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>                // exit() を使うため
#include <t_syslog.h>              // シリアルモニタにログを出す
#include <TS_S3.h>
#include "spike/pup/forcesensor.h" // フォースセンサーを使う

// 押す力を mN 単位で返す（ライブラリ内部と同じ計算）。
// SPIKE_RTのライブラリにバグがあり小数点以下を切り捨てて返すので、
static int32_t force_sensor_mN(pup_device_t *pdev)
{
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
