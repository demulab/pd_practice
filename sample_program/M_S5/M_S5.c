
#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <M_S5.h>

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

void Main(intptr_t exinf) {
  motorA = pup_motor_init(PBIO_PORT_ID_A, PUP_DIRECTION_COUNTERCLOCKWISE);
  motorB = pup_motor_init(PBIO_PORT_ID_B, PUP_DIRECTION_CLOCKWISE);

  dly_tsk(1000000);

  pup_motor_set_speed(motorA, 500);
  pup_motor_set_speed(motorB, 500);

  dly_tsk(1000000);
    
  pup_motor_stop(motorA);
  pup_motor_stop(motorB);

  dly_tsk(850000);

  pup_motor_set_speed(motorA, 500);
  dly_tsk(1000000);
  
  
  pup_motor_stop(motorA);
  pup_motor_stop(motorB);


  exit(0);
}
