
#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <PID.h>

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
    uint64_t count = 0;
    syslog(LOG_NOTICE, "Sample program started.", 0);
    while (true) {
        // wait 1s
        dly_tsk(1000000);

        syslog(LOG_NOTICE, "count: %ld", count);
        count++;
    }
    // finish program
    exit(0);
}
