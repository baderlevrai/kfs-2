#include <kernel.h>

extern char stack_top; // from boot.s

void print_stack(void)
{
	uint32_t esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	while (esp < (uint32_t)&stack_top)
	{
		unsigned char *ptr = (unsigned char *)esp;
		printk("0x%p | ", (void *)esp);
		for (int i = 0; i < 16 ; i++) {
			if ((uint32_t)(ptr + i) < (uint32_t)&stack_top) {
				if (*(ptr + i) / 16 == 0)
					printk("0");
				printk("%p ", *(ptr + i));
			}
		}
		terminal_wchar('\n');
		esp = esp + 16;
	}
}