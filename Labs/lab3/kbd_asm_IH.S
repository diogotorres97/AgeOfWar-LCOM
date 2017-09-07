#include	"i8042.h"

.global _kbd_asm_IH

.data
_OK: .byte 0

.text
_kbd_asm_IH:
	push %ebx
	push %esi
	push %edi
	push %ebp
	xor 	%eax, %eax //limpa o registo eax
	xor 	%ebx, %ebx
	movl $TRIES, %ecx //numero de tentativas

ciclo:

	inb $STAT_REG
	movb %al,%bl
	andb $OBF, %bl
	jz c1
	xor %ebx, %ebx
	movb %al, %bl
	xor %eax,%eax
	xor $PARITY, %al
	xor $TIMEOUT, %al
	cmpb %bl, %al
	jz error
	xor %eax,%eax
	inb $OUT_BUF, %al //al fica com o valor lido do keyboard

	jmp fim

c1:	loop ciclo

error: movb $-1, %al
fim:
pop %ebp
pop %edi
pop %esi
pop %ebx
ret



