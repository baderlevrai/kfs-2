MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS) ; checksum of above, to prove we are multiboot
                                ; CHECKSUM + MAGIC + MBFLAGS should be Zero (0)

section .multiboot
    align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

section .bss
    align 16
    global stack_bottom
	stack_bottom:
    resb 16384
    global stack_top
	stack_top:

section .text
global _start
extern kernel_main
extern GDT

_start:
	mov esi, GDT
	mov edi, 0x00000800
	mov ecx, 56			; 7 seg * 8 bytes
	rep movsb

	lgdt [dword gdtr]
	jmp launch_protected_mode

launch_protected_mode:
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp dword 0x08:flush_segments


[bits 32]
flush_segments:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ax, 0x18
	mov ss, ax
	mov esp, stack_top

	call kernel_main

	cli
	hlt
	jmp $

section .data
gdtr:
	dw 55			; limit
	dd 0x00000800	; base
