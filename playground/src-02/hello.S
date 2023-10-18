.data

msg:
	.ascii "Hello world ASM-x86\n"
	.set len, . - msg

.text

.global _start
_start:	
	call print
	mov $1, %eax
	xor %ebx, %ebx
	int $0x80

print:
	mov $4, %eax
	mov $1, %ebx
	mov $msg, %ecx
	mov $len, %edx
	int $0x80
	ret


