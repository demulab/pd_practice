/* programs/multi_task1/app.c
 * SPIKE-RT: syslog を USB CDC(TeraTerm) へ出力。
 * 帯域・負荷を下げるためログ間引きと待ち時間を追加。
 */
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>

#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"

#include <stdio.h>

/* ───────── 設定 ───────── */
/* 実験時は 100、必要なら 10000 に上げる */
#define COUNT           100

/* ログ洪水を避けつつタスク切替を見やすくする軽い待ち(ミリ秒) */
#define MAIN_DELAY_MS   50
#define SUB_DELAY_MS    50

/* ログ間引き：N回に1回だけログを出す（USB CDC の負荷軽減） */
#define LOG_EVERY_N     10

/* Spike-RT で USB CDC(TERATERM) に出すためのポートID
 * 環境により SIO_USB_PORTID が未定義の場合があるのでフォールバック */
#ifndef SIO_USB_PORTID
#define SIO_USB_PORTID  1
#endif



/* ───────── 前方宣言 ───────── */
static void setup_console_logging(void);

/* ───────── main_task ───────── */
void main_task(intptr_t exinf)
{
    int i;

    /* USBシリアルを開き、syslog出力を有効化（最初に一度だけ） */
    setup_console_logging();

    syslog_0(LOG_NOTICE, "MAIN_TASK: start, activating SUB_TASK.");
    act_tsk(SUB_TASK);

    for (i = 0; i <= COUNT; i++) {
        /* --- ここで MAIN が先に進む権利を取得 --- */
        wai_sem(SEM_MAIN);

        /* ログを間引いて出力（USB帯域の節約） */
        if ((i % LOG_EVERY_N) == 0) {
            syslog_1(LOG_NOTICE, "MAIN TASK = %d", i);
        }

        /* 見やすさのために少しだけ待つ（CPUを明示的に譲る） */
        tslp_tsk(MAIN_DELAY_MS);

        /* --- SUB に実行権を渡す（SUB がこの iteration を続行）--- */
        sig_sem(SEM_SUB);
    }

    syslog_0(LOG_NOTICE, "MAIN_TASK: end.");
    ext_tsk();
}

/* ───────── sub_task ───────── */
void sub_task(intptr_t exinf)
{
    int i;

    syslog_0(LOG_NOTICE, "SUB_TASK: start.");

    for (i = 0; i <= COUNT; i++) {
        /* --- MAIN からバトンを受け取る --- */
        wai_sem(SEM_SUB);

        if ((i % LOG_EVERY_N) == 0) {
            syslog_1(LOG_NOTICE, "SUB  TASK = %d", i);
        }

        tslp_tsk(SUB_DELAY_MS);

        /* --- 次のループで MAIN に先行権を返す --- */
        sig_sem(SEM_MAIN);
    }

    syslog_0(LOG_NOTICE, "SUB_TASK: end.");
    ext_tsk();
}

/* ───────── ログ出力初期化 ─────────
 *  - USB CDC を開く
 *  - syslog のマスク設定（即時出力を控えめに、バッファ経由は NOTICE まで）
 */
static void setup_console_logging(void)
{
    /* USB CDC(TERATERM) を開く。既に開かれていても問題なし */
    serial_opn_por(SIO_USB_PORTID);

    /* デバイスの準備が整うまで、ほんの少し待つと安定することが多い */
    tslp_tsk(10);

    /* 第1引数: 低レベル(即時)出力の優先度マスク
       第2引数: logtask(バッファ経由)出力の優先度マスク
       → 即時は WARNING まで、バッファ経由は NOTICE まで通す */
    syslog_msk_log(LOG_UPTO(LOG_WARNING), LOG_UPTO(LOG_NOTICE));

    syslog_0(LOG_NOTICE, "===== multi_task1: syslog -> USB CDC (throttled) =====");
    syslog_0(LOG_NOTICE, "Masks: immediate<=WARNING, buffered<=NOTICE; LOG_EVERY_N=10.");
}
