#include"test3.h"
#include"keyboard.h"

int kbd_scan_ass(int *apt){
		push %ebp
		mov %esp, %ebp
		sub $8, %esp
		mov -4(%ebp), %eax
		mov %eax, 0
		leave
		IN 0x60, %eax
		mov key_register, %ax
		*apt = (unsigned int) key_register;
		//tickdelay(micros_to_ticks(DELAY_US));


		mov 20000, %ecx
		loop salto
		salto: sub %ecx, 1


		mov %dx, 0xE0
		and %ax, %dx
		cmp %ax, %dx
		je two_bytes
		mov %eax, 0
		ret
		two_bytes: mov %eax, 1
				   ret
}
