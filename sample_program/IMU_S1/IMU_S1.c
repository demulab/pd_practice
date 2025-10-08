#include <stdlib.h>
#include <kernel.h>

#include <spike/hub/system.h>

#include <IMU_S1.h>

#include "spike/pup/motor.h"
#include "spike/pup/colorsensor.h"
#include "spike/pup/forcesensor.h"
#include "spike/pup/ultrasonicsensor.h"

#include "spike/hub/battery.h"
#include "spike/hub/button.h"
#include "spike/hub/display.h"
#include "spike/hub/imu.h"
#include "spike/hub/light.h"
#include "spike/hub/speaker.h"

#include <pbio/color.h>

#include "kernel_cfg.h"
#include "syssvc/serial.h"

// IMU用の配列 0:ロール(x) 1:ピッチ(y) 2:ヨー(z)
float ang_v[3] = {0}; // 角度(角位置)
float imu_offset[3] = {0}; // 角度オフセット

float ang_debug[3] = {0}; // 角度(角位置) (デバッグ用)

void Main(intptr_t exinf)
{
  // ここからプログラムを書く
  char msg[128] = "Program Start\n";
  char str[256] = {' '};

  serial_opn_por(SIO_USB_PORTID); // USBシリアル通信の開通
  serial_wri_dat(SIO_USB_PORTID, msg, sizeof(msg)); // "Program Start"を送信

  imu_setup(imu_offset); // IMU初期化・オフセット同定
  // オフセット算出結果表示
  sprintf(msg,"off_X: %f off_Y: %f off_Z: %f\n", imu_offset[0], imu_offset[1], imu_offset[2]);
  serial_wri_dat(SIO_USB_PORTID, msg, sizeof(msg));

  // 左ボタンが押されるまで待機 (LED: 緑)
  hub_button_t pressed;
  while(!(pressed&HUB_BUTTON_LEFT)){
    hub_button_is_pressed(&pressed);
    hub_light_on_color(PBIO_COLOR_GREEN);
  }

  sta_cyc(CYC_HDR); // ジャイロセンサ監視開始

  int count = 0; //カウンタ変数宣言・初期化

  while(1){
    // 角度情報を文字列に
    sprintf(str,"count:%d,X:%f, Y:%f, Z:%f\n", count,ang_debug[0], ang_debug[1], ang_debug[2]);
    serial_wri_dat(SIO_USB_PORTID, str, sizeof(str)); // シリアル通信で角度を表示

    // 真ん中ボタンが押された時にIMU初期化
    hub_button_is_pressed(&pressed);
    if(pressed==HUB_BUTTON_CENTER){
      hub_imu_init();
      ang_v[0] = 0;
      ang_v[1] = 0;
      ang_v[2] = 0;
      dly_tsk(500*1000);
    }

    dly_tsk(1*500*1000); // 1s待機
    count++; // カウントアップ
  }

  stp_cyc(CYC_HDR); // ジャイロセンサ監視終了

  exit(0);
}

void gyro_monitor(intptr_t exinf)
{
  // IMU角加速度 格納用配列
  float ang_raw[3];
  hub_imu_get_angular_velocity(ang_raw);

  // オフセット無し
  ang_debug[0] += ang_raw[0] * 0.001;
  ang_debug[1] += ang_raw[1] * 0.001;
  ang_debug[2] += ang_raw[2] * 0.001;

  // オフセット有り
  ang_v[0] += (ang_raw[0] - imu_offset[0]) * 0.001;
  ang_v[1] += (ang_raw[1] - imu_offset[1]) * 0.001;
  ang_v[2] += (ang_raw[2] - imu_offset[2]) * 0.001;
}

void imu_setup(float offset[3]){
  dly_tsk(3*1000*1000); // 3s待機
  
  hub_light_on_color(PBIO_COLOR_ORANGE); // LED: オレンジ

  hub_imu_init(); // IMUの初期化

  float ang_raw[3]; // IMU角加速度 raw値 格納用配列

  // オフセット同定 (1秒間で1000回測定して平均取る)
  for(int i=0; i<1000; i++){
    hub_imu_get_angular_velocity(ang_raw); //角加速度取得
    offset[0] += ang_raw[0];
    offset[1] += ang_raw[1];
    offset[2] += ang_raw[2];
    dly_tsk(1*1000); // 1ms待機
  }

  // オフセットをサンプル取得回数で割る
  offset[0] /= 1000;
  offset[1] /= 1000;
  offset[2] /= 1000;
}

