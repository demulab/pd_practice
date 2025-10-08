#include <kernel.h>
#include <pbio/color.h>
#include <spike/hub/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_syslog.h>
#include <button_S1.h>

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

void Main(intptr_t exinf)
{
    syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", 0);

    hub_button_t pressed;
    static int pre_command = -1; // 初期値を無効な状態に設定
    int command = 0;

    while (1)
    {
        hub_button_is_pressed(&pressed);

        // ボタンの状態を判定してコマンド値を計算
        if ((pressed & HUB_BUTTON_RIGHT) == HUB_BUTTON_RIGHT)
        {
            command += 1;
        }
        if ((pressed & HUB_BUTTON_LEFT) == HUB_BUTTON_LEFT)
        {
            command += 2;
        }
        if ((pressed & HUB_BUTTON_CENTER) == HUB_BUTTON_CENTER)
        {
            command += 4;
        }
        if ((pressed & HUB_BUTTON_BT) == HUB_BUTTON_BT) // Bluetoothボタン
        {
            command += 8;
        }

        // コマンドが変更された場合のみ処理
        if (command != pre_command)
        {
            switch (command)
            {
            case 1:
                syslog(LOG_NOTICE, "R");
                hub_display_text("R", 1000, 0);
                break;
            case 2:
                syslog(LOG_NOTICE, "L");
                hub_display_text("L", 1000, 0);
                break;
            case 3:
                syslog(LOG_NOTICE, "R+L");
                hub_display_text_scroll(" R+L", 70);
                break;
            case 4:
                syslog(LOG_NOTICE, "C");
                hub_display_text("C", 1000, 0);
                break;
            case 5:
                syslog(LOG_NOTICE, "R+C");
                hub_display_text_scroll(" R+C", 70);
                break;
            case 6:
                syslog(LOG_NOTICE, "L+C");
                hub_display_text_scroll(" L+C", 70);
                break;
            case 7:
                syslog(LOG_NOTICE, "R+L+C");
                hub_display_text_scroll(" R+L+C", 70);
                break;
            case 8:
                syslog(LOG_NOTICE, "B");
                hub_display_text("B", 1000, 0);
                break;
            case 9:
                syslog(LOG_NOTICE, "R+B");
                hub_display_text_scroll(" R+B", 70);
                break;
            case 10:
                syslog(LOG_NOTICE, "L+B");
                hub_display_text_scroll(" L+B", 70);
                break;
            case 11:
                syslog(LOG_NOTICE, "R+L+B");
                hub_display_text_scroll(" R+L+B", 70);
                break;
            case 12:
                syslog(LOG_NOTICE, "C+B");
                hub_display_text_scroll(" C+B", 70);
                break;
            case 13:
                syslog(LOG_NOTICE, "R+C+B");
                hub_display_text_scroll(" R+C+B", 70);
                break;
            case 14:
                syslog(LOG_NOTICE, "L+C+B");
                hub_display_text_scroll(" L+C+B", 70);
                break;
            case 15:
                syslog(LOG_NOTICE, "ALL");
                hub_display_text_scroll(" ALL", 70);
                break;
            default:
                break;
            }

            pre_command = command; // コマンドを更新
        }

        command = 0; // コマンドをリセット
    }
}
