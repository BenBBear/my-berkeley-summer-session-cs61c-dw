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

LABEL0: .word 0
LABEL1: .asciiz "helloword"
LABEL2: .word 0
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,LABEL2
	lw $v0,0($v1)
	push $v1
	li $v0,1
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
LABEL3:
	pushaa
	la $v1,LABEL2
	lw $v0,0($v1)
	push $v0
	li $v0,10
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,LABEL4
	pushaa
	la $v1,LABEL2
	lw $v0,0($v1)
	push $v1
	pushaa
	la $v1,LABEL2
	lw $v0,0($v1)
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	la $v0,LABEL1
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	j LABEL3
LABEL4:
	popaa
	li $v0 10
	syscall
