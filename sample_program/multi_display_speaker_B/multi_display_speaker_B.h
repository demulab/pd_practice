/* app.h — 必要最小限のプロトタイプだけ用意（修正/新規） */
#ifndef APP_H
#define APP_H

#include <kernel.h>   /* intptr_t などの定義用（または <stdint.h> でも可） */

#ifdef __cplusplus
extern "C" {
#endif

void main_task(intptr_t exinf);
void sub_task(intptr_t exinf);
void test_spike_cychdr(intptr_t exinf);  /* ← これが新しい周期ハンドラ名 */

#ifdef __cplusplus
}
#endif
#endif /* APP_H */
