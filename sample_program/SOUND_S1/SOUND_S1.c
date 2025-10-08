
#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <SOUND_S1.h>

#include "spike/hub/battery.h"
#include "spike/hub/button.h"
#include "spike/hub/display.h"
#include "spike/hub/imu.h"
#include "spike/hub/light.h"
#include "spike/hub/speaker.h"
#include "spike/pup/colorsensor.h"
#include "spike/pup/forcesensor.h"
#include "spike/pup/motor.h"
#include "spike/pup/ultrasonicsensor.h"

pup_motor_t *motorA;             // モータAを使う変数
pup_motor_t *motorB;             // モータBを使う変数
pup_device_t *ColorSensor;       // カラーセンサーを使う変数
pup_device_t *ForceSensor;       // フォースセンサーを使う変数
pup_device_t *UltraSonicSensor;  // 距離センサーを使う変数

// 音を再生する関数
void play_sound() {
    int32_t quarter = 500;
    hub_speaker_play_tone(NOTE_C4, quarter);
}

void Main(intptr_t exinf) {
    uint64_t count = 0;
    syslog(LOG_NOTICE, "Sample program started.", 0);
    // 音量を100%に設定
    hub_speaker_set_volume(100);

    // 現在のバッテリー電圧を測定して表示
    uint16_t battery = hub_battery_get_voltage();  // ()を追加して関数として呼び出す
    hub_display_number(battery);                   // バッテリー電圧をディスプレイに表示

    // サウンドを再生
    play_sound();

    // 3秒待機
    dly_tsk(3000000);

    // finish program
    exit(0);
}
