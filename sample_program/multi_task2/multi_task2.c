/* programs/multi_task1/app.c */
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>

#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include <stdio.h>

/* 実験時は 100 にして確認→必要なら 10000 に上げる */
#define COUNT       100

/* ログ洪水を避けつつタスク切替を見やすくする軽い待ち(ミリ秒) */
#define MAIN_DELAY_MS   5
#define SUB_DELAY_MS    5

void main_task(intptr_t exinf)
{
    int i;

    /* SUB_TASK を起動（同時に動き始めるが、初期セマフォで順序は保証される） */
    syslog_0(LOG_NOTICE, "MAIN_TASK: start, activating SUB_TASK.");
    act_tsk(SUB_TASK);

    for (i = 0; i <= COUNT; i++) {
        /* --- ここで MAIN が先に進む権利を取得 --- */
        wai_sem(SEM_MAIN);

        /* LCD は 5x5 で数表示に不向きのため、カウントは syslog に出す */
        syslog_1(LOG_NOTICE, "MAIN TASK = %d", i);

        /* 見やすさのために少しだけ待つ（CPUを明示的に譲る） */
        tslp_tsk(MAIN_DELAY_MS);

        /* --- SUB に実行権を渡す（SUB がこの iteration を続行）--- */
        sig_sem(SEM_SUB);
    }

    syslog_0(LOG_NOTICE, "MAIN_TASK: end.");
    ext_tsk();
}

void sub_task(intptr_t exinf)
{
    int i;

    syslog_0(LOG_NOTICE, "SUB_TASK: start.");

    for (i = 0; i <= COUNT; i++) {
        /* --- MAIN からバトンを受け取る --- */
        wai_sem(SEM_SUB);

        syslog_1(LOG_NOTICE, "SUB  TASK = %d", i);

        tslp_tsk(SUB_DELAY_MS);

        /* --- 次のループで MAIN に先行権を返す --- */
        sig_sem(SEM_MAIN);
    }

    syslog_0(LOG_NOTICE, "SUB_TASK: end.");
    ext_tsk();
}
