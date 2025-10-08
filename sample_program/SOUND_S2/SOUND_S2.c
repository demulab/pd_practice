
#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <SOUND_S2.h>

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



void play_sound(){
  int32_t quarter = 250;
  int32_t half = 500;
  int32_t full = 1000;
  hub_speaker_play_tone(NOTE_C4, full);    //ド
  hub_speaker_play_tone(NOTE_G4, full);    //ソ
  hub_speaker_play_tone(NOTE_F4, quarter); //ファ
  hub_speaker_play_tone(NOTE_E4, quarter); //ミ
  hub_speaker_play_tone(NOTE_D4, quarter); //レ
  hub_speaker_play_tone(NOTE_C5, full);    //ド高
  hub_speaker_play_tone(NOTE_G4, half);    //ソ
  hub_speaker_play_tone(NOTE_F4, quarter); //ファ
  hub_speaker_play_tone(NOTE_E4, quarter); //ミ
  hub_speaker_play_tone(NOTE_D4, quarter); //レ
  hub_speaker_play_tone(NOTE_C5, full);    //ド高
  hub_speaker_play_tone(NOTE_G4, half);    //ソ
  hub_speaker_play_tone(NOTE_F4, quarter); //ファ
  hub_speaker_play_tone(NOTE_E4, quarter); //ミ
  hub_speaker_play_tone(NOTE_F4, quarter); //ファ
  hub_speaker_play_tone(NOTE_D4, full);    //レ


}

void Main(intptr_t exinf) {
    uint64_t count = 0;
    syslog(LOG_NOTICE, "Sample program started.", 0);
  
  hub_speaker_set_volume(100);

  uint16_t battery = hub_battery_get_voltage();
  hub_display_number(battery);

  play_sound();

  //3秒待ちます
  dly_tsk(3000000);
    // finish program
    exit(0);
}
