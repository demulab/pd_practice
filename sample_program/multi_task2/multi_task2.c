/*------------------------------------------------------------
 *  2つのタスク (MAIN_TASK と SUB_TASK) が
 *  セマフォを使って交互に動作するサンプルプログラム
 *-----------------------------------------------------------*/
#include <kernel.h>              // RTOSの基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // ログ出力
#include <multi_task2.h>
#include "spike/hub/display.h"   // ディスプレイ表示
#include "spike/hub/speaker.h"   // 音を鳴らす機能
#include "spike/hub/battery.h"   // バッテリー情報

#include <t_stdlib.h>
#include "kernel_cfg.h"

/* 実験時は 100 にして確認→必要なら 10000 に上げる */
#define COUNT       100000

/* ログ洪水を避けつつタスク切替を見やすくする軽い待ち(ミリ秒) */
#define MAIN_DELAY_MS   5
#define SUB_DELAY_MS    5

/*------------------------------------------------------------
 *  2つのタスク (MAIN_TASK と SUB_TASK) が
 *  セマフォを使って交互に動作するデモプログラム
 *-----------------------------------------------------------*/

void Main(intptr_t exinf)
{
    int i = 0;

    /* プログラム開始メッセージを出力 */
    syslog(LOG_NOTICE, "Start multi_task1");

    /* SUB_TASK を起動する。
       ただし、すぐには同時実行されず、
       セマフォによって実行順序が制御される。 */
    syslog(LOG_NOTICE, "MAIN_TASK: start, activating SUB_TASK.");
    act_tsk(SUB_TASK);    // SUB_TASK を起動

    /* COUNT 回だけ MAIN_TASK と SUB_TASK が交互に動作するループ */
    for (i = 0; i <= COUNT; i++) {

        /* --- MAIN_TASK の処理を始めるためにセマフォを待つ --- */
        wai_sem(SEM_MAIN);   // SEM_MAIN がシグナルされるまで待機

        /* LCD は小さいため、現在のカウント値を syslog で出力 */
        syslog(LOG_NOTICE, "MAIN TASK = %d", i);

        /* 表示が見やすいように少し待つ（CPUを他タスクに譲る） */
        tslp_tsk(MAIN_DELAY_MS);

        /* --- SUB_TASK に実行権を渡す --- */
        sig_sem(SEM_SUB);    // SUB_TASK 側の待機セマフォを解放
    }

    /* ループ終了後、MAIN_TASK の終了をログに出す */
    syslog(LOG_NOTICE, "MAIN_TASK: end.");

    /* タスクを終了（自タスク削除） */
    ext_tsk();
}

/*------------------------------------------------------------
 *  SUB_TASK: MAIN_TASK と交互に動作する補助タスク
 *-----------------------------------------------------------*/
void sub_task(intptr_t exinf)
{
    int i;

    /* SUB_TASK の開始メッセージ */
    syslog(LOG_NOTICE, "SUB_TASK: start.");

    for (i = 0; i <= COUNT; i++) {

        /* --- MAIN_TASK から実行権を受け取る（バトンを受け取る） --- */
        wai_sem(SEM_SUB);    // SEM_SUB がシグナルされるまで待機

        /* SUB_TASK 側のカウント値をログ出力 */
        syslog(LOG_NOTICE, "SUB  TASK = %d", i);

        /* 見やすいように少し待機（CPUを譲る） */
        tslp_tsk(SUB_DELAY_MS);

        /* --- 次のループでは MAIN_TASK が先に進むようにバトンを返す --- */
        sig_sem(SEM_MAIN);   // MAIN_TASK 側のセマフォを解放
    }

    /* SUB_TASK の終了ログを出力してタスク終了 */
    syslog(LOG_NOTICE, "SUB_TASK: end.");
    ext_tsk();
}
