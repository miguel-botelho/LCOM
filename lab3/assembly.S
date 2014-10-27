//.global _key
//.global _kbd_scan_ass


	//.text
	//_kbd_scan_ass:

		//movl $0, %ebx
		//movl $0, %eax
		//inb $0x60, %al  //ebx é o valor que foi lido do kbd
		//andw $0x00FF, %ax
		//mov %ax, _key //cast para que apenas obtenha os ultimos 8 bits para key, variavel global

		//movb $0xE0, %dl //dl = 0xE0, para o caso de 2 bytes
		//andb %dl, %al  //se bx, a key, é igual a 0xE0, para
		//cmpb %dl, %al   //o IF :p
		//je two_bytes
		//movl $0, %eax
		//jmp fim //retorna 0 se a tecla for de 1 byte
		//two_bytes: movl $1, %eax
		//fim:	   ret //retorna 1 se a tecla for de 2 bytes

.global _key
.global _kbd_scan_ass

	.text
	_kbd_scan_ass:
	inb $0x60, %al
	andw $0x00FF, %ax
	movw %ax, _key

	mov $2147483, %ecx
	ciclo: loop ciclo

	andw $0x00E0, %ax
	cmpw $0x00E0, %ax
	je two_bytes
	movl $0, %eax
	jmp fim
	two_bytes: movl $1, %eax
	fim:		ret
