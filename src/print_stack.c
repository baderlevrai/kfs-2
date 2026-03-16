#include <kernel.h>

extern char stack_top; // from boot.s

void print_stack(void)
{
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	while (esp != (uint32_t)&stack_top)
	{
		printk("0x%p | %p\n", (void *)esp, *(char *)esp);
		esp++;
	}
}