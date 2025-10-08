
#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <TS_S3.h>

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
    ForceSensor = pup_force_sensor_get_device(PBIO_PORT_ID_D);  
    syslog(LOG_NOTICE, "TS_S3 program started.", 0);
    while (1) 
    {  
        float fouce = pup_force_sensor_force(ForceSensor);
        char fouce_str[32];
        snprintf(fouce_str, sizeof(fouce_str), "%.2f", fouce);  // 小数点以下2桁まで表示
        syslog(LOG_NOTICE, "fouce: %s", fouce_str);
        dly_tsk(50000);
    }
    // finish program
    exit(0);
}
