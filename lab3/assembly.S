#include"test3.h"
#include"keyboard.h"

	.text
	_kbd_scan_ass:
		push %ebp
		mov %esp, %ebp
		sub $8, %esp
		mov -4(%ebp), %eax  //variavel local :DD
		mov %eax, 0
		leave
		IN 0x60, %eax

		mov 20000, %ecx
		salto: sub %ecx, 1  //TickDelay :D
		loop salto

		mov %dx, 0xE0
		and %ax, %dx
		cmp %ax, %dx  //o IF :p
		je two_bytes
		mov %eax, 0
		ret
		two_bytes: mov %eax, 1
				   ret
