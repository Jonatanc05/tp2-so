#include "types.h"
#include "user.h"

int stdout = 1;
int stderr = 2;

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(2, "Usage: virt2real <address (decimal)>\n");
    exit();
  }

  char* addr_str = argv[1];
  int addr_int = atoi(addr_str);
  char* va = (char*) addr_int;

  char* pa = virt2real(va);

  printf(stdout, "Endereco virtual %d (ou 0x%x) mapeia para o endereco fisico %d (ou 0x%x)\n", va, va, pa, pa);
  exit();
}

