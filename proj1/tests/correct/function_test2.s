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
LABEL1: .asciiz "hello"
LABEL2: .asciiz "world"
LABEL3: .asciiz " "
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v1
	li $v0,2
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	move $v0,$zero
	li $v0,9
	push $v0
	jal hello
	pop $zero
	li $v0 10
	syscall
hello:
	push $ra
	pushaa
	add $v1,$sp,16
	lw $v0,0($v1)
	push $v1
	la $v0,LABEL1
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	add $v1,$sp,12
	lw $v0,0($v1)
	push $v1
	la $v0,LABEL2
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	add $v1,$sp,16
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL3
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	add $v1,$sp,12
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pop $ra
	jr $ra
