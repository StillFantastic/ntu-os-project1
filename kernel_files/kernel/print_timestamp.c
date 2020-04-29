#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage void sys_print_timestamp(int pid, long s1, long s2, long e1, long e2) {
  printk(KERN_INFO "[Project1] %d %ld.%09ld %ld.%09ld\n", pid, s1, s2, e1, e2);
}
