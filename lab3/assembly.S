#include"test3.h"
#include"keyboard.h"

	.global _kbd_scan_ass

	.text
	_kbd_scan_ass:

		movl %ebx, 0
		movl %eax, 0
		IN 0x60, %ebx
		movw key, %bx


		mov %ecx, 20000
		salto: sub %ecx, 1  //TickDelay :D
		loop salto

		mov %dx, 0xE0
		and %bx, %dx //bx = 0xED ?
		cmp %bx, %dx  //o IF :p
		je two_bytes
		mov %eax, 0
		ret
		two_bytes: mov %eax, 1
				   ret
