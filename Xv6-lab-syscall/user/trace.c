#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  /*
  用户呼叫我们提供的系统调用接口 int trace(int)
  这个接口的实现由perl脚本生成的汇编语言实现, 将SYS_trace的代号放入a7寄存器, 由ecall硬件支持由用户态转入内核态
  控制转到系统调用的通用入口 void syscall(void) 手上.
  它由a7寄存器读出需要被调用的系统调用是第几个, 从uint64 (*syscalls[])(void)这个函数指针数组跳转到那个具体的系统调用函数实现上.
  将返回值放在a0寄存器里
  我们从第二步的ecall里退出来了, 汇编指令ret使得用户侧系统调用接口返回
  */
  int i;
  char *nargv[MAXARG];

  if (argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9'))
  {
    fprintf(2, "Usage: %s mask command\n", argv[0]);
    exit(1);
  }

  if (trace(atoi(argv[1])) < 0)
  {
    fprintf(2, "%s: trace failed\n", argv[0]);
    exit(1);
  }

  for (i = 2; i < argc && i < MAXARG; i++)
  {
    nargv[i - 2] = argv[i];
  }
  exec(nargv[0], nargv);
  exit(0);
}
