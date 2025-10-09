#include <kernel.h>              // RTOS（リアルタイムOS）の基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // シリアルモニタにメッセージを出す
#include <button_S1.h>
#include "spike/hub/button.h"    // ボタン入力
#include "spike/hub/display.h"   // LEDディスプレイ表示

// ──────────────────────────────
// Main関数（RTOSが最初に実行される）
// ──────────────────────────────
void Main(intptr_t exinf)
{
    syslog(LOG_NOTICE, "Button test started.");

    hub_button_t pressed;       // ボタンの状態を格納
    int last_command = -1;      // 前回のボタン状態（初期値は無効）
    int command = 0;            // 現在のボタン状態を数値で表す

    while (1)
    {
        // ボタン状態の取得
        hub_button_is_pressed(&pressed);
        command = 0;

        // 各ボタンが押されているかをビットで判定
        if (pressed & HUB_BUTTON_RIGHT)  command += 1;
        if (pressed & HUB_BUTTON_LEFT)   command += 2;
        if (pressed & HUB_BUTTON_CENTER) command += 4;
        if (pressed & HUB_BUTTON_BT)     command += 8; // Bluetoothボタン

        // 前回と異なる入力があったときのみ処理
        if (command != last_command)
        {
            switch (command)
            {
                case 0:  hub_display_text(" ", 500, 0); syslog(LOG_NOTICE, "No button"); break;
                case 1:  hub_display_text("R", 1000, 0); syslog(LOG_NOTICE, "Right"); break;
                case 2:  hub_display_text("L", 1000, 0); syslog(LOG_NOTICE, "Left"); break;
                case 3:  hub_display_text_scroll("R+L", 70); syslog(LOG_NOTICE, "Right+Left"); break;
                case 4:  hub_display_text("C", 1000, 0); syslog(LOG_NOTICE, "Center"); break;
                case 5:  hub_display_text_scroll("R+C", 70); syslog(LOG_NOTICE, "Right+Center"); break;
                case 6:  hub_display_text_scroll("L+C", 70); syslog(LOG_NOTICE, "Left+Center"); break;
                case 7:  hub_display_text_scroll("R+L+C", 70); syslog(LOG_NOTICE, "Right+Left+Center"); break;
                case 8:  hub_display_text("B", 1000, 0); syslog(LOG_NOTICE, "Bluetooth"); break;
                case 9:  hub_display_text_scroll("R+B", 70); syslog(LOG_NOTICE, "Right+Bluetooth"); break;
                case 10: hub_display_text_scroll("L+B", 70); syslog(LOG_NOTICE, "Left+Bluetooth"); break;
                case 11: hub_display_text_scroll("R+L+B", 70); syslog(LOG_NOTICE, "Right+Left+Bluetooth"); break;
                case 12: hub_display_text_scroll("C+B", 70); syslog(LOG_NOTICE, "Center+Bluetooth"); break;
                case 13: hub_display_text_scroll("R+C+B", 70); syslog(LOG_NOTICE, "Right+Center+Bluetooth"); break;
                case 14: hub_display_text_scroll("L+C+B", 70); syslog(LOG_NOTICE, "Left+Center+Bluetooth"); break;
                case 15: hub_display_text_scroll("ALL", 70); syslog(LOG_NOTICE, "All Buttons"); break;
                default: break;
            }

            // 現在の状態を記録（変化があったときのみ）
            last_command = command;
        }

        // 0.1秒待機（CPU負荷を軽減）
        dly_tsk(100000);
    }
}
