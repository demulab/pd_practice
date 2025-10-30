/*------------------------------------------------------------
 *  2つのタスク (MAIN_TASK と SUB_TASK) が
 *  セマフォを使って順番に動作するサンプルプログラム
 *  - 先に MAIN_TASK (Main) が動く
 *  - Main 完了後に SUB_TASK (sub_task) が動く
 *-----------------------------------------------------------*/
#include <kernel.h>              // RTOSの基本機能
#include <stdlib.h>              // exit() を使うため
#include <t_syslog.h>            // ログ出力
#include <multi_task1_A.h>
#include "spike/hub/display.h"   // ディスプレイ表示
#include "spike/hub/speaker.h"   // 音を鳴らす機能
#include "spike/hub/battery.h"   // バッテリー情報

#include <t_stdlib.h>
#include "kernel_cfg.h"

/* 実験時は 100 にして確認→必要なら 10000 に上げる */
#define COUNT       10000

/* ログ洪水を避けつつタスク切替を見やすくする軽い待ち(ミリ秒) */
#define MAIN_DELAY_MS   5
#define SUB_DELAY_MS    5

/*------------------------------------------------------------
 *  MAIN_TASK:
 *   - 先に実行されるタスク
 *   - カウント値をログに出す
 *   - 全部終わったら SUB_TASK を起動して終了する
 *-----------------------------------------------------------*/
void Main(intptr_t exinf)
{
    int i = 0;

    /* プログラム開始メッセージを出力 */
    syslog(LOG_NOTICE, "Start multi_task1");

    syslog(LOG_NOTICE, "MAIN_TASK: start");

    /* COUNT 回だけ MAIN_TASK がカウントを出力するループ */
    for (i = 0; i <= COUNT; i++) {

        /* MAIN_TASK 側のカウント値を syslog で出力 */
        syslog(LOG_NOTICE, "MAIN TASK = %d", i);

        /* 表示が見やすいように少し待つ（CPUを他タスクに譲る） */
        tslp_tsk(MAIN_DELAY_MS);
    }

    /* ループ終了後、MAIN_TASK の終了をログに出す */
    syslog(LOG_NOTICE, "MAIN_TASK: end.");

    /* ここで SUB_TASK が動けるようにセマフォを解放し、起動する */
    sig_sem(SEM_SUB);     // SUB_TASK 側が待っているセマフォを解放
    act_tsk(SUB_TASK);    // SUB_TASK を起動

    /* MAIN_TASK はここで終了 */
    ext_tsk();
}

/*------------------------------------------------------------
 *  SUB_TASK:
 *   - MAIN_TASK が終わった後に起動されるタスク
 *   - MAIN_TASK からの合図(SEM_SUB)を受けてから動き始める
 *   - カウント値をログに出す
 *-----------------------------------------------------------*/
void sub_task(intptr_t exinf)
{
    int i;

    /* MAIN_TASK 完了の合図を待つ */
    wai_sem(SEM_SUB);    // Main が sig_sem(SEM_SUB) するまでブロック

    /* SUB_TASK の開始メッセージ */
    syslog(LOG_NOTICE, "SUB_TASK: start.");

    for (i = 0; i <= COUNT; i++) {

        /* SUB_TASK 側のカウント値をログ出力 */
        syslog(LOG_NOTICE, "SUB  TASK = %d", i);

        /* 見やすいように少し待機（CPUを譲る） */
        tslp_tsk(SUB_DELAY_MS);
    }

    /* SUB_TASK の終了ログを出力してタスク終了 */
    syslog(LOG_NOTICE, "SUB_TASK: end.");
    ext_tsk();
}