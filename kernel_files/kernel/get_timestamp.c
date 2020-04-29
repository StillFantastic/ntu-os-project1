#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage void sys_get_timestamp(struct timespec *ts) {
  getnstimeofday(ts);
}
