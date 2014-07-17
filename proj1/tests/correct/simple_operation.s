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
LABEL1: .word 0
LABEL2: .asciiz "\n"
LABEL3: .asciiz "\n"
LABEL4: .asciiz "\n"
LABEL5: .asciiz "\n"
LABEL6: .asciiz "\n"
LABEL7: .asciiz "\n"
LABEL8: .asciiz "\n"
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v1
	li $v0,14
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	la $v1,LABEL1
	lw $v0,0($v1)
	push $v1
	li $v0,2
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	la $v1,LABEL1
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	add $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL2
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	la $v1,LABEL1
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	sub $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
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
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	la $v1,LABEL1
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	mul $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL4
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	la $v1,LABEL1
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	div $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL5
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL1
	lw $v0,0($v1)
	push $v0
	la $v1,LABEL0
	lw $v0,0($v1)
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL6
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	li $v0,14
	move $a1,$v0
	pop $a0
	seq $v0,$a0,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL7
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	li $v0,3
	move $a1,$v0
	pop $a0
	move $v0,$zero
	beq $a0,$zero,LABEL9
	beq $a1,$zero,LABEL9
	li $v0,1
LABEL9:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	la $v0,LABEL8
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL0
	lw $v0,0($v1)
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	li $v0,1
	bne $a0,$zero,LABEL10
	bne $a1,$zero,LABEL10
	move $v0,$zero
LABEL10:
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	li $v0 10
	syscall
