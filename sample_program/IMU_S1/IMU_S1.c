#include <kernel.h>               // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>               // exit() を使うため
#include <IMU_S1.h>
#include "spike/hub/imu.h"        // IMU（角速度センサー）を使う
#include "spike/hub/light.h"      // ハブのLED制御
#include "spike/hub/button.h"     // ハブのボタン入力
#include "syssvc/serial.h"        // シリアル通信
#include "kernel_cfg.h"           // 周期ハンドラなどの設定

// ──────────────────────────────
// グローバル変数
// ──────────────────────────────
float ang_v[3] = {0};       // 角度（オフセット補正後）
float imu_offset[3] = {0};  // オフセット値（初期ずれ補正用）

// ──────────────────────────────
// 関数プロトタイプ宣言
// ──────────────────────────────
void imu_setup(float offset[3]);
void gyro_monitor(intptr_t exinf);

// ──────────────────────────────
// メイン関数（RTOSが最初に実行する）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    char msg[128];

    serial_opn_por(SIO_USB_PORTID);    // USBシリアル通信を開く
    serial_wri_dat(SIO_USB_PORTID, "Program Start\n", 14);

    imu_setup(imu_offset);             // IMU初期化とオフセット計算
    sprintf(msg, "Offset X: %.3f Y: %.3f Z: %.3f\n",
            imu_offset[0], imu_offset[1], imu_offset[2]);
    serial_wri_dat(SIO_USB_PORTID, msg, sizeof(msg));

    // 左ボタンが押されるまで待機（LEDは緑に点灯）
    hub_button_t pressed;
    while (!(pressed & HUB_BUTTON_LEFT)) {
        hub_button_is_pressed(&pressed);
        hub_light_on_color(PBIO_COLOR_GREEN);
    }

    sta_cyc(CYC_HDR);  // 周期ハンドラ開始（IMU監視）

    int count = 0;
    while (1) {
        // 現在の角度をシリアル出力
        sprintf(msg, "count:%d  X:%.2f  Y:%.2f  Z:%.2f\n",
                count, ang_v[0], ang_v[1], ang_v[2]);
        serial_wri_dat(SIO_USB_PORTID, msg, sizeof(msg));

        // 中央ボタンでIMUを再初期化
        hub_button_is_pressed(&pressed);
        if (pressed == HUB_BUTTON_CENTER) {
            hub_imu_init();
            ang_v[0] = ang_v[1] = ang_v[2] = 0;
            dly_tsk(500000); // 0.5秒待機
        }

        dly_tsk(1000000); // 1秒ごとに出力
        count++;
    }

    stp_cyc(CYC_HDR);  // 周期ハンドラ停止（終了時用）
    exit(0);
}

// ──────────────────────────────
// 周期ハンドラ：IMUの角速度を読み取り、角度を計算
// ──────────────────────────────
void gyro_monitor(intptr_t exinf)
{
    float ang_raw[3];
    hub_imu_get_angular_velocity(ang_raw);  // 角速度を取得

    // 角速度を時間積分して角度に変換（Δt = 0.001秒）
    ang_v[0] += (ang_raw[0] - imu_offset[0]) * 0.001;
    ang_v[1] += (ang_raw[1] - imu_offset[1]) * 0.001;
    ang_v[2] += (ang_raw[2] - imu_offset[2]) * 0.001;
}

// ──────────────────────────────
// IMU初期化とオフセット計算
// ──────────────────────────────
void imu_setup(float offset[3])
{
    hub_light_on_color(PBIO_COLOR_ORANGE);  // オレンジ点灯：初期化中
    hub_imu_init();                         // IMU初期化

    float ang_raw[3] = {0};
    offset[0] = offset[1] = offset[2] = 0;

    // 1秒間（1000回）角速度を読み取って平均をとる
    for (int i = 0; i < 1000; i++) {
        hub_imu_get_angular_velocity(ang_raw);
        offset[0] += ang_raw[0];
        offset[1] += ang_raw[1];
        offset[2] += ang_raw[2];
        dly_tsk(1000); // 1ミリ秒待機
    }

    // 平均値（オフセット）を計算
    offset[0] /= 1000;
    offset[1] /= 1000;
    offset[2] /= 1000;

    hub_light_on_color(PBIO_COLOR_WHITE); // 白点灯：初期化完了
}
