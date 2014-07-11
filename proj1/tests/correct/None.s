.macro push (%arg)
add $sp,$sp,-4
sw %arg,0($sp)
.end_macro

.macro pop (%arg)
lw %arg,0($sp)
add $sp,$sp,4
.end_macro

.macro pushaa ()
push $a0
push $a1
.end_macro
.macro popaa ()
pop $a1
pop $a0
.end_macro
.data

LABEL0: .asciiz "\n"
	.text
	.globl main
	j  main


	main:
	pushaa
	li $v0,0
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	pushaa
	la $v0,LABEL0
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	pushaa
	pushaa
	li $v0,0
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	seq $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	li $v0 10
	syscall
