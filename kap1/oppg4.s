	.file	"oppg4.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L2
	addl	$1, -4(%rbp)
.L2:
	movl	$0, %eax
	popq	%rbp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
