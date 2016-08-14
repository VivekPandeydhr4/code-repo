	.file	"prac.c"
	.section	.rodata
.LC0:
	.string	"%c  -  %c, %c  -  %c\n"
.LC1:
	.string	"%d - %d, %d - %d\n"
.LC2:
	.string	"Size = %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movb	$122, -118(%rbp)
	movb	$65, -117(%rbp)
	leaq	-112(%rbp), %rdx
	movl	$0, %eax
	movl	$12, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	%rdi, %rdx
	movl	%eax, (%rdx)
	addq	$4, %rdx
	movl	$25, -116(%rbp)
	movl	$122, %r8d
	movl	$97, %ecx
	movl	$90, %edx
	movl	$65, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$122, %r8d
	movl	$97, %ecx
	movl	$90, %edx
	movl	$65, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-116(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$10, %edi
	call	putchar
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
