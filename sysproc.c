#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_date(void)
{
  char *ptr;
  argptr(0, &ptr, sizeof(struct rtcdate*));
  struct rtcdate* output = (struct rtcdate*)ptr;
  cmostime(output);
  return 0;
}

extern pte_t* walkpgdir(pde_t* dir, const void* va, int alloc);
int sys_virt2real(void)
{
  char *va;
  argptr(0, &va, sizeof(char*));
  pte_t* pte = walkpgdir(myproc()->pgdir, va, 0);
  return PTE_ADDR(*pte) | ((uint)va & 0xFFF);
}

int
sys_forkcow(void)
{
  return forkcow();
}

extern int num_pages();
int sys_num_pages(void)
{
  return num_pages();
}

int sys_corretor(void)
{
  return 0;
}
