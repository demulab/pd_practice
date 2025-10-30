/* programs/multi_task1/app.h */

#ifndef TASK_PORTID
#define TASK_PORTID     1           /* 文字入力するシリアルポートID */
#endif /* TASK_PORTID */

#ifndef TOPPERS_MACRO_ONLY
extern void main_task(intptr_t exinf);
extern void sub_task(intptr_t exinf);
#endif
