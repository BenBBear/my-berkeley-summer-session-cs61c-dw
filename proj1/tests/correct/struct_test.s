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

LABEL0: .asciiz "hello"
LABEL1: .asciiz "world"
LABEL2: .word 0 0 0 0 
LABEL3: .asciiz "hello"
LABEL4: .asciiz "world"
LABEL5: .word 0 0 0 0 
LABEL6: .word 0
LABEL7: .word 0
	.text
	.globl main
	j  main


	main:
	pushaa
	la $a0,LABEL2
	li $v0,1
	sw $v0,0($a0)
	li $v0,3
	sw $v0,4($a0)
	la $v0,LABEL0
	sw $v0,8($a0)
	la $v0,LABEL1
	sw $v0,12($a0)
	move $v0,$a0
	popaa
	pushaa
	la $v1,LABEL6
	lw $v0,0($v1)
	push $v1
	pushaa
	la $a0,LABEL5
	li $v0,2
	sw $v0,0($a0)
	li $v0,4
	sw $v0,4($a0)
	la $v0,LABEL3
	sw $v0,8($a0)
	la $v0,LABEL4
	sw $v0,12($a0)
	move $v0,$a0
	popaa
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	pushaa
	la $v1,LABEL6
	lw $v0,0($v1)
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL6
	lw $v0,0($v1)
	push $v0
	li $v0,1
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL6
	lw $v0,0($v1)
	push $v0
	li $v0,2
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,4
	syscall
	move $v0,$zero
	popaa
	pushaa
	pushaa
	la $v1,LABEL6
	lw $v0,0($v1)
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	push $v1
	li $v0,10
	move $a1,$v0
	pop $a0
	sw $a1,0($a0)
	move $v0,$a1
	popaa
	pushaa
	pushaa
	la $v1,LABEL6
	lw $v0,0($v1)
	push $v0
	li $v0,0
	move $a1,$v0
	pop $a0
	mul $a1,$a1,4
	add $a1,$a1,$a0
	lw $v0,0($a1)
	move $v1,$a1
	popaa
	move $a0,$v0
	li $v0,1
	syscall
	move $v0,$zero
	popaa
	li $v0 10
	syscall
