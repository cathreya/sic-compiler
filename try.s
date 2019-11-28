	.text
	.file	"main"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	movq	$5, -32(%rbp)
	movq	$0, -24(%rbp)
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_8:                                # %after_loop5
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$.L__unnamed_1, %edi
	movl	$10, %esi
	xorl	%eax, %eax
	callq	printf
	incq	-24(%rbp)
.LBB0_1:                                # %loop_header
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movq	-32(%rbp), %rsi
	movl	$2, %edi
	callq	pow
	cmpq	%rax, -24(%rbp)
	jge	.LBB0_7
# %bb.2:                                # %loop_body
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %r14
	movq	%r14, %rsp
	movq	$0, -16(%rax)
	jmp	.LBB0_3
	.p2align	4, 0x90
.LBB0_6:                                # %after
                                        #   in Loop: Header=BB0_3 Depth=2
	incq	(%r14)
.LBB0_3:                                # %loop_header6
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	(%r14), %rax
	cmpq	-32(%rbp), %rax
	jge	.LBB0_8
# %bb.4:                                # %loop_body4
                                        #   in Loop: Header=BB0_3 Depth=2
	movq	%rsp, %rbx
	leaq	-16(%rbx), %rsp
	movq	$0, -16(%rbx)
	movq	(%r14), %rsi
	movl	$2, %edi
	callq	pow
	movq	%rax, %rcx
	movq	-24(%rbp), %rax
	cqto
	idivq	%rcx
	movq	%rax, -16(%rbx)
	movq	%rax, %rcx
	shrq	$63, %rcx
	addq	%rax, %rcx
	andq	$-2, %rcx
	subq	%rcx, %rax
	cmpq	$1, %rax
	jne	.LBB0_6
# %bb.5:                                # %then
                                        #   in Loop: Header=BB0_3 Depth=2
	movq	(%r14), %rsi
	movl	$.L__unnamed_2, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$.L__unnamed_1, %edi
	movl	$32, %esi
	xorl	%eax, %eax
	callq	printf
	jmp	.LBB0_6
.LBB0_7:                                # %after_loop
	xorl	%eax, %eax
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0x90         # -- Begin function pow
	.type	pow,@function
pow:                                    # @pow
	.cfi_startproc
# %bb.0:                                # %body
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movq	$1, -32(%rsp)
	movq	$0, -24(%rsp)
	jmp	.LBB1_1
	.p2align	4, 0x90
.LBB1_2:                                # %loop_body
                                        #   in Loop: Header=BB1_1 Depth=1
	movq	-32(%rsp), %rax
	imulq	-8(%rsp), %rax
	movq	%rax, -32(%rsp)
	incq	-24(%rsp)
.LBB1_1:                                # %loop_header
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rsp), %rax
	cmpq	-16(%rsp), %rax
	jl	.LBB1_2
# %bb.3:                                # %after_loop
	movq	-32(%rsp), %rax
	retq
.Lfunc_end1:
	.size	pow, .Lfunc_end1-pow
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_2,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_2:
	.asciz	"%d"
	.size	.L__unnamed_2, 3

	.type	.L__unnamed_1,@object   # @1
.L__unnamed_1:
	.asciz	"%c"
	.size	.L__unnamed_1, 3


	.section	".note.GNU-stack","",@progbits
