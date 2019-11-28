	.text
	.file	"main"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	$5, 16(%rsp)
	movq	$2, 8(%rsp)
	movl	$5, %edi
	movl	$2, %esi
	callq	g
	movq	%rax, %rcx
	movq	%rcx, (%rsp)
	movl	$.L__unnamed_1, %edi
	xorl	%eax, %eax
	movq	%rcx, %rsi
	callq	printf
	xorl	%eax, %eax
	addq	$24, %rsp
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
	.p2align	4, 0x90         # -- Begin function g
	.type	g,@function
g:                                      # @g
	.cfi_startproc
# %bb.0:                                # %body
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, 32(%rsp)
	movq	%rsi, 24(%rsp)
	movq	$0, 16(%rsp)
	movq	$0, 8(%rsp)
	jmp	.LBB2_1
	.p2align	4, 0x90
.LBB2_2:                                # %loop_body
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	8(%rsp), %rdi
	movq	24(%rsp), %rsi
	callq	pow
	addq	%rax, 16(%rsp)
	incq	8(%rsp)
.LBB2_1:                                # %loop_header
                                        # =>This Inner Loop Header: Depth=1
	movq	8(%rsp), %rax
	cmpq	32(%rsp), %rax
	jl	.LBB2_2
# %bb.3:                                # %after_loop
	movq	16(%rsp), %rax
	addq	$40, %rsp
	retq
.Lfunc_end2:
	.size	g, .Lfunc_end2-g
	.cfi_endproc
                                        # -- End function
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"%d"
	.size	.L__unnamed_1, 3

	.type	.L__unnamed_2,@object   # @1
.L__unnamed_2:
	.asciz	"%c"
	.size	.L__unnamed_2, 3


	.section	".note.GNU-stack","",@progbits
