.global _key
.global _kbd_scan_ass

	.text
	_kbd_scan_ass:
	inb $0x60, %al //al é o valor que foi lido do kbd
	andw $0x00FF, %ax // ax = 0x00al
	movw %ax, _key // a key = 0x00al

	mov $2147483, %ecx //tempo de espera
	ciclo: loop ciclo

	andw $0x00E0, %ax // ax= ax & 0x00E0
	cmpw $0x00E0, %ax //se ax = 0x00E0, então a tecla é de 2 bytes
	je two_bytes
	movl $0, %eax //retorna 0 se a tecla é de 1 byte
	jmp fim
	two_bytes: movl $1, %eax //retorna 1 se a tecla é de 2 bytes
	fim:		ret
