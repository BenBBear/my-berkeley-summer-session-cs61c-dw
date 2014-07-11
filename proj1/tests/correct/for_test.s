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

LABEL0: .asciiz "helloworld"
LABEL1: .asciiz "\n"
LABEL2: .word 0
LABEL3: .word 0
LABEL4: .word 0
LABEL5: .asciiz "helloworld"
LABEL6: .asciiz "\n"
LABEL7: .word 0
LABEL8: .asciiz "helloworld"
	.text
	.globl main
	j  main


	main:
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	push $v1
	li $v0,3
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
LABEL9:
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	push $v0
	li $v0,10
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,LABEL10
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	push $v1
	pushaa
	la $v1,LABEL7
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
	la $v0,LABEL0
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	pushaa
	la $v0,LABEL1
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	j LABEL9
LABEL10:
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	push $v1
	li $v0,1
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
LABEL11:
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	push $v0
	li $v0,3
	move $a1,$v0
	pop $a0
	slt $v0,$a0,$a1
	popaa
	beq $v0,$zero,LABEL12
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	push $v1
	pushaa
	la $v1,LABEL7
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
	la $v0,LABEL5
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	pushaa
	la $v1,LABEL7
	lw $v0,0($v1)
	move $a0,$v0
	li $v0,1
	syscall
	popaa
	pushaa
	la $v0,LABEL6
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	j LABEL11
LABEL12:
LABEL13:
	beq $v0,$zero,LABEL14
	pushaa
	la $v0,LABEL8
	move $a0,$v0
	li $v0,4
	syscall
	popaa
	j LABEL13
LABEL14:
	li $v0 10
	syscall
