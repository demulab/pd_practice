#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

/*
 *  タスクの優先度の定義
 */
#define MAIN_PRIORITY	5		/* メインタスクの優先度 */

// 以下を追加
#define HIGH_PRIORITY	9		/* 並行実行されるタスクの優先度 */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

/*
 * Definitions of Port ID for Serial Adapter
 */
#define SIO_USART_F_PORTID    1
#define SIO_USB_PORTID        2
#define SIO_BLUETOOTH_PORTID  3
#define SIO_TEST_PORTID       4

#ifndef STACK_SIZE
#define	STACK_SIZE		4096		/* タスクのスタックサイズ */
#endif /* STACK_SIZE */

/*
 *  関数のプロトタイプ宣言
 */
#ifndef TOPPERS_MACRO_ONLY

extern void Main(intptr_t exinf);
extern void gyro_monitor(intptr_t exinf);
void imu_setup();

#endif /* TOPPERS_MACRO_ONLY */